#pragma once
#include "Mlecz.h"
#include "Czlowiek.h"
#include "Guarana.h"
#include "Antylopa.h"
#include "Jagoda.h"
#include "Zolw.h"
#include "Owca.h"
#include "Lis.h"
#include "Trawa.h"
#include "Wilk.h"
#include "Zwierze.h"
#include <vector>
#include <memory>

using namespace std;

enum typOrganizmu {
	MLECZ=0, ANTYLOPA, JAGODA, ZOLW, OWCA, LIS, TRAWA, WILK, GUARANA, CZLOWIEK
};

class Swiat
{
public:
	string komentarz;
	int kierunekHuman;
	bool czyAktywnaUmiejtnosc;
	int wymiar;
	Swiat();
	Swiat(int n);
	~Swiat();
	void wykonajTure();
	void rysujSwiat();
	Organizm *  sprawdzPole(int x, int y);
	void usunOrganizm();
	void dodajOrganizm(typOrganizmu typ, int x, int y);
	void zmienMape(char co, int x, int y);
	void wypelnij(int n);
	void zapisz();
	void odczyt();
private:
	char ** mapa;
	std::vector <Organizm *> organizmy;
	void sortujOrganizmy();
	void komentuj();
	void czysc();
};