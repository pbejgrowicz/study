#include "Czlowiek.h"
#include "Swiat.h"

Czlowiek::Czlowiek(Swiat & swiat, int x, int y) : Zwierze(swiat, x, y, 4, 5, "Czlowiek", '@')
{
	this->ileRund = 0;
	this->ileRundBezUmiejetnosci = 0;
	this->swiat.zmienMape('@', x, y);
}


Czlowiek::~Czlowiek()
{
}


void Czlowiek::akcja()
{
	if (swiat.czyAktywnaUmiejtnosc == true && ileRund == 0 && ileRundBezUmiejetnosci == 0) // jezeli licznik rund wyzerwowany mozna rozpoaczac super umiejetnosc
	{
		this->ileRund = 6;
		this->ileRundBezUmiejetnosci = 11;
	}
	if (this->ileRundBezUmiejetnosci > 0 && ileRund == 0) //sprawdzenie czy byla umiejtnosc uzywana ostatnio
		swiat.czyAktywnaUmiejtnosc = false;
	this->wiek++;
	this->idz(swiat.kierunekHuman);
	this->rysowanie();
	if (swiat.czyAktywnaUmiejtnosc == true) // jezeli umiejetnosc aktywna to zmniejszamy 
		this->ileRund--;
	if (this->ileRundBezUmiejetnosci > 0) // czas do nastepnego uzycia umiejtnosci
		this->ileRundBezUmiejetnosci--;  
	if (swiat.czyAktywnaUmiejtnosc == true && ileRund == 0) //wylaczenie umiejetnosci po 5 rundach
		swiat.czyAktywnaUmiejtnosc = false;

}