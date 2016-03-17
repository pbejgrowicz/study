#include "Guarana.h"
#include "Swiat.h"

Guarana::Guarana(Swiat & swiat, int x, int y) : Roslina(swiat, x, y, 0, "Guarana", 'g')
{
	this->rysowanie();
}


Guarana::~Guarana()
{
}
