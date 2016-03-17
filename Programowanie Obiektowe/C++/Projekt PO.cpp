// Projekt PO.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <conio.h>
#include <time.h>
#include <string>
#include "Swiat.h"

using namespace std;

int main(){
	srand(static_cast<unsigned int>(time(NULL)));
	cout << "Patryk Bejgrowicz 149385" << endl;
	cout << "Podaj rozmiar swiata:  ";
	int wymiar, wybor = 0;
	cin >> wymiar;
	try 
	{
		Swiat swiat(wymiar);
		do {
			system("CLS");
			cout << "Patryk Bejgrowicz 149385" << endl;
			cout << "1  \t<- Wykonaj ture" << endl << "strzalki<- poruszanie cz³owieka \"@\" " << endl << "s  \t<- niesmiertelnosc na 5 rund" << endl << "2 \t<- Koniec programu" << endl;
			if (wybor == '1') {
				swiat.kierunekHuman = -1;
				swiat.wykonajTure();
			}
			if (wybor == 75) {
				swiat.kierunekHuman = 0; // lewo

				swiat.wykonajTure();
			}
			if (wybor == 80) {
				swiat.kierunekHuman = 1; //dol
				swiat.wykonajTure();
			}
			if (wybor == 77) {
				swiat.kierunekHuman = 2; //prawo
				swiat.wykonajTure();
			}
			if (wybor == 72) {
				swiat.kierunekHuman = 3; //gora
				swiat.wykonajTure();
			}
			if (wybor == 's') {
				swiat.czyAktywnaUmiejtnosc = true;
				swiat.wykonajTure();
			}
			if (wybor == 'z') {
				swiat.zapisz();
				swiat.rysujSwiat();
			}
			if (wybor == 'o') {
				swiat.odczyt();
				swiat.rysujSwiat();
			}
			wybor = _getch();
		} while (wybor != '2');
	}
	catch (string w)
	{
		cout << "Blad: " << w;
	}


	return 0;
}