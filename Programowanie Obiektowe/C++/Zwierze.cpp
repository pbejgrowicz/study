#include <cmath>
#include <time.h>
#include <iostream>
#include <Windows.h>
#include <string>
#include "Zwierze.h"
#include "Swiat.h"

using namespace std;

enum kierunekRuchu {
	GORA = 0, PRAWO = 1, DOL = 2, LEWO = 3
};

Zwierze::Zwierze(Swiat & swiat, int _x, int _y, int inicjatywa, int sila, char * typ, char znak) : Organizm(swiat, _x, _y, inicjatywa, sila, typ, znak) {};

Zwierze::~Zwierze()
{
}

void Zwierze::idz(int n) {
	if (this->smierc == 1) return;
	int newX = x;
	int newY = y;
	int antySzansa = rand() % 2; // losowanie szansy na ucieczke przez Antylope

	this->swiat.zmienMape(' ', this->x, this->y);

	switch ((kierunekRuchu)n) {
	case GORA: if (newY > 0) newY--; break;
	case LEWO: if (newX > 0) newX--; break;
	case DOL: if (newY < this->swiat.wymiar - 1) newY++; break;
	case PRAWO: if (newX < this->swiat.wymiar - 1) newX++; break;
	default: break;
	}

	Organizm * obcy = this->swiat.sprawdzPole(newX, newY);
	if (obcy == NULL)
	{
		(*this).x = newX;
		(*this).y = newY;
	}

	else
	{
		if (this->podajTyp() == "Lis" && obcy != NULL) // lis nigdy nie przechodzi na zajmowane pole
		{
			return;
		}
		if ((this->podajTyp() == "Czlowiek" && swiat.czyAktywnaUmiejtnosc == true) ||
			(obcy->podajTyp() == "Czlowiek" && swiat.czyAktywnaUmiejtnosc == true)) // niesmiertelnosc czlowieka
		{
			return;
		}
		if (obcy->podajTyp() == "Zolw" && this->sila < 5) // zolw odpiera ataki wrogow o sile < 5
		{
			return;
		}
		if (obcy->podajTyp() == "Guarana") // zolw odpiera ataki wrogow o sile < 5
		{
			this->sila += 3;
			this->kolizja(obcy, newX, newY);
		}
		if ((obcy->podajTyp() == "Antylopa" || this->podajTyp() == "Antylopa") && antySzansa == 1) // 50% szansy na ucieczke z walki przez antylope
			return;
		else
			this->kolizja(obcy, newX, newY);
	}
}

void Zwierze::akcja() {
	this->wiek++;

	int kierunek = (int)(4.0 * (rand() / (RAND_MAX + 1.0)));
	this->idz(kierunek);

	this->rodzenie++;
	this->rysowanie();

}

void Zwierze::rysowanie() {
	this->swiat.zmienMape(this->znak, this->x, this->y);
}

void Zwierze::kolizja(Organizm * obcy, int newX, int newY) {
	if (typeid(*this).name() == typeid(*obcy).name()) {   // jezeli ten sam typ obiektu to zachodzi rozmnazanie
		if ((this->rodzenie > 10) && (obcy->podaj(RODZENIE) > 10)) {
			this->rozmnazaj(newX, newY);
			this->swiat.komentarz += "Narodzil sie nowy ";
			this->swiat.komentarz += (this->podajTyp());
			this->swiat.komentarz += "\n";
		}
		obcy->ustaw(RODZENIE, 0, ' ');
	}
	else {  // atakowanie zwierzat
		if (this->atakuj(*obcy))
		{
			this->swiat.komentarz += this->typ;
			if (obcy->podajZnak() == 't' || obcy->podajZnak() == 'm' || obcy->podajZnak() == 'j' || obcy->podajZnak() == 'g') this->swiat.komentarz += " zjadl ";
			else this->swiat.komentarz += " zabil ";
			this->swiat.komentarz += (obcy->podajTyp());
			if (obcy->podajZnak() == 'j') this->swiat.komentarz += " i nie zyje";
			this->swiat.komentarz += "\n";
			obcy->ustaw(ZNAK, 0, ' ');
			(*this).x = newX;
			(*this).y = newY;
		}
		else {
			if (obcy->podajZnak() == 'j')
			{
				this->swiat.komentarz += this->podajTyp();
				this->swiat.komentarz += " zjadl wilcze jagody i nie zyje.\n";
			}
			else
			{
				this->swiat.komentarz += this->typ;
				this->swiat.komentarz += " przegral z ";
				this->swiat.komentarz += (obcy->podajTyp());
				this->swiat.komentarz += "\n";
			}
		}
	}
}

bool Zwierze::atakuj(Organizm & obcy) {
	int silaObcego = obcy.podaj(SILA);
	if (silaObcego <= this->sila) 
	{
		obcy.ustaw(SMIERC, 1, ' ');
		obcy.ustaw(ZNAK, 0, ' ');
		if (obcy.podajTyp() == "Wilcze jagody") {
			this->ustaw(SMIERC, 1, ' ');
			this->ustaw(ZNAK, 0, ' ');
		}
		return 1;
	}
	else {
		this->ustaw(SMIERC, 1, ' ');
		this->ustaw(ZNAK, 0, ' ');
		return 0;

	}
}

void Zwierze::rozmnazaj(int x, int y) {
	int new_x = this->x + (rand() % 2) - 1;
	int new_y = this->y + (rand() % 2) - 1;
	if (new_x <= 0) new_x = 0;
	if (new_y <= 0) new_y = 0;
	if (new_x >= this->swiat.wymiar) new_x = this->swiat.wymiar - 1;
	if (new_y >= this->swiat.wymiar) new_y = this->swiat.wymiar - 1;
	if (this->swiat.sprawdzPole(x, y) != NULL && this->wiek > 0) {
		typOrganizmu typ;
		if (!strcmp(typeid(*this).name(), "class Wilk")) typ = WILK;
		else if (!strcmp(typeid(*this).name(), "class Antylopa")) typ = ANTYLOPA;
		else if (!strcmp(typeid(*this).name(), "class Owca")) typ = OWCA;
		else if (!strcmp(typeid(*this).name(), "class Zolw")) typ = ZOLW;
		else if (!strcmp(typeid(*this).name(), "class Lis")) typ = LIS;
		else return;
		this->swiat.dodajOrganizm(typ, new_x, new_y);
	}
	this->rodzenie = 0;
}

bool Zwierze::operator<(Organizm * drugi) {
	if (Zwierze * a = dynamic_cast<Zwierze *>(drugi)) {
		if (this->inicjatywa == a->podaj(INICJATYWA)) return wiek < a->podaj(WIEK);
		else return inicjatywa < a->podaj(INICJATYWA);
	}
	else return wiek < drugi->podaj(WIEK);
}