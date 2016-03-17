#pragma once
#include "Zwierze.h"
class Czlowiek :
	public Zwierze
{
public:
	int ileRund;
	int ileRundBezUmiejetnosci;
	Czlowiek(Swiat & swiat, int x, int y);
	~Czlowiek();
	void akcja();
};

