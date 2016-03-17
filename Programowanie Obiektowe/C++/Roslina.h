#pragma once
#include "Organizm.h"
class Roslina :
	public Organizm
{
protected:
	Roslina(Swiat & swiat, int x, int y, int sila, char * typ, char znak);
	~Roslina();
	virtual void akcja();
	void kolizja(Organizm * obcy, int new_x, int new_y);
	void rysowanie();
private:
	void rozmnazaj(int x, int y);
};

