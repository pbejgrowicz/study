#include "Mlecz.h"
#include "Swiat.h"

Mlecz::Mlecz(Swiat & swiat, int x, int y) : Roslina(swiat, x, y, 0, "Mlecz", 'm') {
	this->swiat.zmienMape('m', x, y);
};

Mlecz::~Mlecz()
{
}
