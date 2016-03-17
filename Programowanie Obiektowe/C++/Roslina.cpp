#include <time.h>
#include <iostream>
#include "Roslina.h"
#include "Swiat.h"

Roslina::Roslina(Swiat & swiat, int x, int y, int sila, char * typ, char znak) : Organizm(swiat, x, y, 0, sila, typ, znak)
{
}

Roslina::~Roslina() {

}

void Roslina::akcja() {
	if (this->smierc == 1) return;
	if (this->podajTyp() == "Mlecz") //potrojna proba rozmnazania przez mlecz
		for (int i = 0; i < 3; i++)
			this->rozmnazaj(this->x, this->y);
	else
		this->rozmnazaj(this->x, this->y);
	this->wiek++;
}

void Roslina::kolizja(Organizm * obcy, int new_x, int new_y) {

}

void Roslina::rysowanie() {
	this->swiat.zmienMape(this->znak, this->x, this->y);
}

void Roslina::rozmnazaj(int x, int y) {
	int szansa = rand() % 100;
	if (szansa > 10) return; // zeby rosliny sie za bardzo nie rozmnazaly
	int new_x = this->x + (rand() % 2) - 1;
	int new_y = this->y + (rand() % 2) - 1;
	if (new_x <= 0) new_x = 0;
	if (new_y <= 0) new_y = 0;
	if (new_x >= this->swiat.wymiar) new_x = this->swiat.wymiar - 1;
	if (new_y >= this->swiat.wymiar) new_y = this->swiat.wymiar - 1;
	if (this->swiat.sprawdzPole(x, y) != NULL && (this->wiek > 0) && this->swiat.sprawdzPole(new_x, new_y) == NULL) {  //sprawdzenie wolnego pola
		typOrganizmu typ;
		if (!strcmp(typeid(*this).name(), "class Jagoda")) typ = JAGODA;
		else if (!strcmp(typeid(*this).name(), "class Mlecz")) typ = MLECZ;
		else if (!strcmp(typeid(*this).name(), "class Trawa")) typ = TRAWA;
		else if (!strcmp(typeid(*this).name(), "class Guarana")) typ = GUARANA;
		else return;
		this->swiat.dodajOrganizm(typ, new_x, new_y);
		this->swiat.komentarz += "Narodzil sie nowy ";
		this->swiat.komentarz += (this->podajTyp());
		this->swiat.komentarz += "\n";
	}
}