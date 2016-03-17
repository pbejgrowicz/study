#include <time.h>
#include "Lis.h"
#include "Swiat.h"

Lis::Lis(Swiat & swiat, int x, int y) : Zwierze(swiat, x, y, 7, 3, "Lis", 'L')
{
	this->swiat.zmienMape('L', x, y);
}


Lis::~Lis()
{
}
