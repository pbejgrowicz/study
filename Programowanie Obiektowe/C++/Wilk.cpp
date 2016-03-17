#include "Wilk.h"
#include "Swiat.h"


Wilk::Wilk(Swiat & swiat, int x, int y) : Zwierze(swiat, x, y, 5, 9, "Wilk", 'W')
{
	this->swiat.zmienMape('W', x, y);
}


Wilk::~Wilk()
{
}
