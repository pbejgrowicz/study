#pragma once
#include "Organizm.h"
class Zwierze :
	public Organizm
{
protected:
	Zwierze(Swiat & swiat, int x, int y, int inicjatywa, int sila, char * typ, char znak);
	~Zwierze();
	void akcja();
	void kolizja(Organizm * obcy, int new_x, int new_y);
	void rysowanie();
	bool operator<(Organizm * obcy);
	void idz(int n);
	virtual bool atakuj(Organizm & obcy);
	void rozmnazaj(int x, int y);

};

