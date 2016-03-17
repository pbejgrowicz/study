#include "Antylopa.h"
#include "Swiat.h"
#include <time.h>

Antylopa::Antylopa(Swiat & swiat, int x, int y) : Zwierze(swiat,x,y,4,4,"Antylopa",'A')
{
	this->swiat.zmienMape('A', x, y);
}


void Antylopa::akcja() {
	this->wiek++;
	int ile = 2;
	while (ile--) //petla 2 ruchow dla Antylopy
	{
		int kierunek = (int)(4.0 * (rand() / (RAND_MAX + 1.0)));
		this->idz(kierunek);
		this->rodzenie++;
		this->rysowanie();
	}
}



Antylopa::~Antylopa()
{
}
