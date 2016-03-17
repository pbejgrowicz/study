#pragma once
#include "Zwierze.h"
class Zolw :
	public Zwierze
{
public:
	Zolw(Swiat & swiat, int x, int y);
	~Zolw();
	void akcja();
};

