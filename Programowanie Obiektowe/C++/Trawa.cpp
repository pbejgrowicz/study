#include "Trawa.h"
#include "Swiat.h"

Trawa::Trawa(Swiat & swiat, int x, int y) : Roslina(swiat, x, y, 0, "Trawa", 't')
{
	this->rysowanie();
}


Trawa::~Trawa()
{
}
