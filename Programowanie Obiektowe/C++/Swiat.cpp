#include <iostream>
#include <algorithm>
#include <time.h>
#include <cmath>
#include <string>
#include "Swiat.h"
#include <fstream>

using namespace std;

//domyslny konstruktor Swiata
Swiat::Swiat()
{
	wymiar = 20;
	char ** mapa = new char *[20];
	for (int i = 0; i < 20; i++) {
		mapa[i] = new char[20];
		for (int j = 0; j < 20; j++) {
			mapa[i][j] = ' ';
		}
	}
	this->wypelnij(2);
}

//konstkuktor swiata z podanym n
Swiat::Swiat(int n) throw(string) : komentarz("")
{
	wymiar = n;
	if (wymiar > 100)
	{
		string wyjatek = "niepoprawny rozmiar wymiaru\n";
		throw wyjatek;
	}
	char ** mapa = new char *[n];
	for (int i = 0; i < n; i++) {
		mapa[i] = new char[n];
		for (int j = 0; j < n; j++) {
			mapa[i][j] = ' ';
		}
	}
	this->mapa = mapa;
	this->wypelnij((n / 5) + 1);
}

Swiat::~Swiat()
{
	delete[] mapa;
}

void Swiat::rysujSwiat() {
	cout << endl;
	for (int i = 0; i < wymiar; i++) {
		for (int j = 0; j < wymiar; j++) {
			cout << this->mapa[i][j];
		}
		cout << endl;
	}
}

void Swiat::komentuj() {
	cout << this->komentarz;
	this->komentarz = "";
}

void Swiat::wypelnij(int n) {
	this->dodajOrganizm((typOrganizmu)9, 0, 0); // dodaje czlowieka
	this->sortujOrganizmy();
	srand(time(NULL));
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < n; j++) {
			int new_x = rand() % (this->wymiar);
			int new_y = rand() % (this->wymiar);
			while (sprawdzPole(new_x, new_y) != NULL){
				new_x = rand() % (this->wymiar);
				new_y = rand() % (this->wymiar);
			}
			this->dodajOrganizm((typOrganizmu)i, new_x, new_y);
			this->sortujOrganizmy();
		}
	}
}

//oblsuga tury
void Swiat::wykonajTure() {
	this->usunOrganizm(); //usuwa organizmy ktory nie zyja
	for (int i = 0; i < organizmy.size(); i++) {
		organizmy[i]->akcja();
	}
	this->rysujSwiat();
	this->komentuj();
}

void Swiat::sortujOrganizmy() {
	sort(this->organizmy.begin(), this->organizmy.end());
}

Organizm * Swiat::sprawdzPole(int x, int y) {
	for (int i = 0; i < organizmy.size(); i++) {
		if (x == organizmy[i]->podaj(X) && y == organizmy[i]->podaj(Y)) {
			return organizmy[i];
		}
	}
	return NULL;
}

void Swiat::usunOrganizm() {
	for (int i = organizmy.size() - 1; i > 0; i--) {
		if (organizmy[i]->podaj(SMIERC) == 1) {
			this->zmienMape(' ', organizmy[i]->podaj(X), organizmy[i]->podaj(Y));
			delete organizmy[i];
			organizmy.erase(organizmy.begin() + i);
		}
	}
}

void Swiat::dodajOrganizm(typOrganizmu typ, int x, int y) {
	Swiat & swiat = *this;
	Organizm * temp;
	switch (typ) {
	case MLECZ:  temp = new Mlecz(swiat, x, y); break;
	case ANTYLOPA: temp = new Antylopa(swiat, x, y); break;
	case JAGODA:  temp = new Jagoda(swiat, x, y); break;
	case ZOLW:  temp = new Zolw(swiat, x, y); break;
	case OWCA:  temp = new Owca(swiat, x, y); break;
	case LIS:  temp = new Lis(swiat, x, y); break;
	case TRAWA: temp = new Trawa(swiat, x, y); break;
	case WILK: temp = new Wilk(swiat, x, y); break;
	case GUARANA: temp = new Guarana(swiat, x, y); break;
	case CZLOWIEK: temp = new Czlowiek(swiat, x, y); break;
	default: return; break;
	}

	organizmy.push_back(temp);
};

void Swiat::zmienMape(char znak, int x, int y) {
	mapa[x][y] = znak;
}

void Swiat::zapisz()
{
	fstream plik;
	plik.open("plik.txt", ios::out);
	for (int i = 0; i < organizmy.size(); i++)
	{
		if (organizmy[i]->podajZnak() != ' ')
		{
			plik << organizmy[i]->podajZnak(); plik << " ";
			plik << organizmy[i]->podaj(X); plik << " ";
			plik << organizmy[i]->podaj(Y); plik << " ";
			plik << organizmy[i]->podaj(SILA); plik << " ";
			plik << organizmy[i]->podaj(WIEK); plik << " ";
			plik << "\n";
		}
	}
	plik.close();
}

void Swiat::odczyt()
{
	Swiat & swiat = *this;
	this->zmienMape(' ', organizmy[0]->podaj(X), organizmy[0]->podaj(Y));
	delete organizmy[0];
	organizmy.erase(organizmy.begin());
	for (int i = organizmy.size() - 1; i > 0; i--)
	{
		this->zmienMape(' ', organizmy[i]->podaj(X), organizmy[i]->podaj(Y));
		organizmy[i]->ustaw(ZNAK, 0, ' ');
		delete organizmy[i];
		organizmy.erase(organizmy.begin() + i);
	}
	fstream plik;
	char typ;
	int x, y, sila, wiek;
	plik.open("plik.txt", ios::in);
	while (!plik.eof())
	{
		Organizm *temp = NULL;
		plik >> typ >> x >> y >> sila >> wiek;
		if (typ == '@')
			temp = new Czlowiek(swiat, x, y);
		if (typ == 'm')
			temp = new Mlecz(swiat, x, y);
		if (typ == 'A')
			temp = new Antylopa(swiat, x, y);
		if (typ == 'j')
			temp = new Jagoda(swiat, x, y);
		if (typ == 'Z')
			temp = new Zolw(swiat, x, y);
		if (typ == 'O')
			temp = new Owca(swiat, x, y);
		if (typ == 'L')
			temp = new Lis(swiat, x, y);
		if (typ == 't')
			temp = new Trawa(swiat, x, y);
		if (typ == 'W')
			temp = new Wilk(swiat, x, y);
		if (typ == 'g')
			temp = new Guarana(swiat, x, y);
		temp->ustaw(SILA, sila, ' ');
		temp->ustaw(WIEK, wiek, ' ');
		organizmy.push_back(temp);
	}
	plik.close();
}
