#include "Zolw.h"
#include "Swiat.h"
#include <time.h>

Zolw::Zolw(Swiat & swiat, int x, int y) : Zwierze(swiat, x, y, 1, 2, "Zolw", 'Z')
{
	this->swiat.zmienMape('Z', x, y);
}


void Zolw::akcja() {
	this->wiek++;

	srand(time(NULL));
	int szansa = rand() % 4;
	int kierunek = (int)(4.0 * (rand() / (RAND_MAX + 1.0)));
	if (szansa == 1)
		this->idz(kierunek);
	this->rodzenie++;
	this->rysowanie();
}


Zolw::~Zolw()
{
}
