#include "Organizm.h"
#include "Swiat.h"

Organizm::Organizm(Swiat & swiat, int x, int y, int inicjatywa, int sila, char * typ, char znak) :
swiat(swiat), x(x), y(y), sila(sila), smierc(0), typ(typ), znak(znak), wiek(0), rodzenie(0), dodatek(0), inicjatywa(inicjatywa) {
}

Organizm::~Organizm() 
{
}

bool Organizm::operator<(Organizm * drugi) {
	return wiek < drugi->wiek;
}

int Organizm::podaj(typSkladowej skladowa) {
	switch (skladowa) {
	case X: return this->x; break;
	case Y: return this->y; break;
	case WIEK: return this->wiek; break;
	case SILA: return this->sila; break;
	case INICJATYWA: return this->inicjatywa; break;
	case SMIERC: return this->smierc; break;
	case RODZENIE: return this->rodzenie; break;
	default: return 0; break;
	}
}

char Organizm::podajZnak() {
	return this->znak;
}

char * Organizm::podajTyp() {
	return this->typ;
}

void Organizm::ustaw(typSkladowej skladowa, int wartosc, char znak) {
	switch (skladowa) {
	case ZNAK: this->znak = znak; break;
	case X: this->x = wartosc; break;
	case Y: this->y = wartosc; break;
	case WIEK: this->wiek = wartosc; break;
	case SILA: this->sila = wartosc; break;
	case INICJATYWA: this->inicjatywa = wartosc; break;
	case SMIERC: this->smierc = wartosc; break;
	case RODZENIE: this->rodzenie = wartosc; break;
	case DODATEK: this->dodatek = wartosc; break;
	default: break;
	}
}