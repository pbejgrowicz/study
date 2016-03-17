#include "Jagoda.h"
#include "Swiat.h"

Jagoda::Jagoda(Swiat & swiat, int x, int y) : Roslina(swiat, x, y, 99, "Wilcze jagody", 'j') {
	this->swiat.zmienMape('j', x, y);
};

Jagoda::~Jagoda()
{
}
