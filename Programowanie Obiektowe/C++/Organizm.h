#pragma once
class Swiat;

enum typSkladowej {
	ZNAK, X, Y, WIEK, INICJATYWA, SILA, SMIERC, RODZENIE, DODATEK
};

class Organizm
{
public:
	Organizm(Swiat & swiat, int x, int y, int inicjatywa, int sila, char * typ, char znak);
	~Organizm();
	virtual void akcja() = 0; //wirtualna metoda, aby mozna bylo ja wywolywac z klasy swiat
	//virtual void kolizja(Organizm * obcy, int new_x, int new_y) = 0;
	//virtual void rysowanie() = 0;
	virtual bool operator<(Organizm * drugi);
	int podaj(typSkladowej skladowa);
	char podajZnak();
	char * podajTyp();
	void ustaw(typSkladowej skladowa, int wartosc, char znak);
protected:
	char znak, * typ;
	Swiat & swiat;
	void rozmnazaj(int x, int y);
	int sila, x, y, wiek, inicjatywa, smierc, rodzenie, dodatek;
};

