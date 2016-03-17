#include "Owca.h"
#include "Swiat.h"

Owca::Owca(Swiat & swiat, int x, int y) : Zwierze(swiat, x, y, 4, 4, "Owca", 'O')
{
	this->swiat.zmienMape('O', x, y);
}


Owca::~Owca()
{
}
