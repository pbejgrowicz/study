#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <Windows.h>
#include <sstream>
#include "conio2.h"

#define POZYCJA_PLANSZY_X 1 
#define POZYCJA_PLANSZY_Y 1
#define POZYCJA_POMOCY_X 30
#define POZYCJA_POMOCY_Y 4
#define POZYCJA_KOMENTARZA_X 30
#define POZYCJA_KOMENTARZA_Y 15
#define POZYCJA_CZASU_X 40
#define POZYCJA_CZASU_Y 1

using namespace std;

int iloscKrokow = 0;		//ogolna ilosc krokow
int iloscKrokowDoTylu = 0;	//ogolna ilosc krokow do tylu na liscie undo-redo
int ileStanow = 0;			//ile ogolnie jest stanow na liscie undo-redo


struct SudokuState{
	int sudoku[9][9];
	int komentarz[9][9][9];
	int activeState;
	struct SudokuState *next;
	struct SudokuState *prev;
};

struct SudokuState *ogon = NULL;		//inicjalizacja ostatniego elementu listy i wyzerowanie go 

void inicjalizuj()
{
	//tworzenie elementu stan i sprawdzenie czy mozna mu przyidzelic pamiec
	struct SudokuState *stan;
	if ((stan = (struct SudokuState *)malloc(sizeof(struct SudokuState))) == NULL)
		return;

	//wypelnienie tablice 2d zerami
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			stan->sudoku[j][i] = 0;
		}
	}

	//wyzerowanie komentarzy
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			for (int k = 0; k < 9; k++)
			{
				stan->komentarz[j][i][k] = 0;
			}
		}
	}

	stan->activeState = 0;

	//inicjalizujemy pusta tablice ktora bedzie poczatkiem jak i koncem struktury
	stan->next = NULL;
	stan->prev = NULL;
	ogon = stan;
}

string wpisywanieZnakow(int x, int y)
{
	int pomocX = x, pomocY = y; //przypisanie pomocniczy X i Y
	gotoxy(pomocX, pomocY); //przesuniecie kursora do polozenia pomocniczych X i Y
	string polecenie = "\0";  //zainicializowanie stringa i "wyzerowanie" go
	char znak = '\0'; // j/w tylko że chara
	do{
		znak = getche();   //pobiera klawisz i wyswietla go na ekranie konsoli
		pomocX++;
		if (znak != 13)   //wykonuj jeżeli znaki są różne od ENTER'a

			if (znak == 8)  //znak backspace i rozne operacje do kontroli kursora
			{
				cout << " ";
				if (polecenie != "\0")
				{
					polecenie.erase(polecenie.end() - 1);
					pomocX -= 2;
				}
				else
				{
					pomocX = x;
					
				}

				if (pomocX < x)
				{
					pomocX = x;
					//polecenie.erase(polecenie.end() - 1);
				}
				

			}
			else
				polecenie = polecenie + znak;  //dodanie znaku do stringa;
		gotoxy(pomocX, pomocY);  //przesuniecie kursora

	} while (znak != 13);
	polecenie = polecenie + "\0";
	return polecenie;
}

int zmienStringaNaInt(string wartosc)
{
	// zamiana lancucha znakowego na zmienna int
	int wyjsciowa;
	istringstream strumien(wartosc);
	strumien >> wyjsciowa;
	return wyjsciowa;
}

// OPERACJE NA LISCIE DWUKIERUNKOWEJ

void dodajDoTablicy(int x, int y, int liczba)
{
	//dodanie nowego elementu do tablicy
	struct SudokuState *stan;

	//sprawdzenie czy mozna przydzielic mu pamiec
	if ((stan = (struct SudokuState *)malloc(sizeof(struct SudokuState))) == NULL)
		return;

	//przepisanie tablicy z obecnego ogona do stanu stan
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			stan->sudoku[j][i] = ogon->sudoku[j][i];
		}
	}

	//przepisanie tablicy z obecnego ogona do stanu stan
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			for (int k = 0; k < 9; k++)
			{
				stan->komentarz[j][i][k] = ogon->komentarz[j][i][k];
			}
		}
	}

	//przypisanie nowej wartości do tablicy 2d
	stan->sudoku[y][x] = liczba;

	stan->activeState = ogon->activeState + 1;


	//stan element staje sie teraz ogonem
	stan->next = NULL;
	stan->prev = ogon;
	ogon->next = stan;
	ogon = stan;
}

void dodajKomentarzDoTablicy(int x, int y, int z, int liczba)
{
	//dodanie nowego elementu do tablicy
	struct SudokuState *stan;

	//przydzielenie mu pamieci
	if ((stan = (struct SudokuState *)malloc(sizeof(struct SudokuState))) == NULL)
		return;

	//przepisanie tablicy z obecnego ogona do elementu stan
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			stan->sudoku[j][i] = ogon->sudoku[j][i];
		}
	}

	//przepisanie tablicy z obecnego ogona do elementu stan
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			for (int k = 0; k < 9; k++)
			{
				stan->komentarz[j][i][k] = ogon->komentarz[j][i][k];
			}
		}
	}

	//przypisanie nowej wartości do tablicy 3d
	stan->komentarz[x][y][z] = liczba;

	stan->activeState = ogon->activeState + 1;

	//stan element staje sie teraz ogonem
	stan->next = NULL;
	stan->prev = ogon;
	ogon->next = stan;
	ogon = stan;
}

void usunStanZListy(struct SudokuState *stan)
{
	//sprawdza czy stan nie jest pusty 
	if (stan == NULL)
		return;

	else if (stan == ogon) //jezeli stan jest ogonem, to ogonem bedzie poprzedni stan
	{
		ogon = stan->prev;
		ogon->next = NULL;
	}

	else //przypadek gdy usuwamy stan nie z ogona ani z poczatku listy
	{
		stan->prev->next = stan->next;
		stan->next->prev = stan->prev;
	}

	//zwolnienie pamieci 
	free(stan);
}

void stworzNowyStan(int sudokuNew[9][9], int komentarzNew[9][9][9])
{
	struct SudokuState *stan;

	//przydzielenie mu pamieci
	if ((stan = (struct SudokuState *)malloc(sizeof(struct SudokuState))) == NULL)
		return;

	//przepisanie tablicy z obecnego ogona do elementu stan
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			stan->sudoku[j][i] = sudokuNew[j][i];
		}
	}

	//przepisanie tablicy z obecnego ogona do elementu stan
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			for (int k = 0; k < 9; k++)
			{
				stan->komentarz[j][i][k] = komentarzNew[i][j][k];
			}
		}
	}

	stan->activeState = ogon->activeState + 1;

	//stan element staje sie teraz ogonem
	stan->next = NULL;
	stan->prev = ogon;
	ogon->next = stan;
	ogon = stan;
}

void undoredo(struct SudokuState *pozycja)
{
	//wypisuje na planszy stan poprzedni lub nastepny w zaleznosci od undo badz redo
	int x = 1 + POZYCJA_PLANSZY_X;
	int y = 1 + POZYCJA_PLANSZY_Y;
	char pomocnicza;
	gotoxy(x, y);
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			x += 2;
			pomocnicza = pozycja->sudoku[j][i] + 48;
			if (pozycja->sudoku[j][i] == 0) cout << ' '; else cout << pomocnicza;
			gotoxy(x, y);
		}
		x = 1 + POZYCJA_PLANSZY_X;
		y += 2;
		gotoxy(x, y);
	}
}

//FUNKCJE DO SPRAWDZANIA

bool czyMoznaWstawicDoWiersza(int x, char klawisz) {
	for (int j = 0; j < 9; j++)
	{
		if (ogon->sudoku[j][x] == klawisz - 48) return false;
	}
	return true;
}

bool czyMoznaWstawicDoKolumny(int y, char klawisz) {
	for (int j = 0; j < 9; j++)
	{
		if (ogon->sudoku[y][j] == klawisz - 48)
			return false;
	}
	return true;
}

bool czyMoznaWstawicDoBoxa(int x, int y, char klawisz)
{
	int i, j;

	if (x == 0 || x == 1 || x == 2) i = 0;
	if (x == 3 || x == 4 || x == 5) i = 3;
	if (x == 6 || x == 7 || x == 8) i = 6;
	if (y == 0 || y == 1 || y == 2) j = 0;
	if (y == 3 || y == 4 || y == 5) j = 3;
	if (y == 6 || y == 7 || y == 8) j = 6;

	for (int k = 0; k < 3; k++)
	{
		for (int l = 0; l < 3; l++)
		{
			if (ogon->sudoku[i + k][j + l] == klawisz - 48) return false;
		}
	}
	return true;

}

bool czyWystepujaKomentarze()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			for (int k = 0; k < 9; k++)
			{
				if (ogon->komentarz[j][i][k] != 0)
					return true;
			}
		}
	}
	return false;
}

//RYSOWANIE GRY

void rysujPlansze(int x, int y)
{
	gotoxy(x, y);

	cout << (char)0xC9 << (char)0xCD << (char)0xCB << (char)0xCD << (char)0xCB << (char)0xCD << (char)0xCB
		<< (char)0xCD << (char)0xCB << (char)0xCD << (char)0xCB << (char)0xCD << (char)0xCB
		<< (char)0xCD << (char)0xCB << (char)0xCD << (char)0xCB << (char)0xCD << (char)0xBB;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			y++;
			gotoxy(x, y);
			cout << (char)0xBA << " " << (char)0xB3 << " " << (char)0xB3 << " " << (char)0xBA << " " << (char)0xB3
				<< " " << (char)0xB3 << " " << (char)0xBA << " " << (char)0xB3 << " " << (char)0xB3 << " " << (char)0xBA;
			y++;
			gotoxy(x, y);
			cout << (char)0xCC << (char)0xC4 << (char)0xC5 << (char)0xC4 << (char)0xC5 << (char)0xC4 << (char)0xCE
				<< (char)0xC4 << (char)0xC5 << (char)0xC4 << (char)0xC5 << (char)0xC4 << (char)0xCE
				<< (char)0xC4 << (char)0xC5 << (char)0xC4 << (char)0xC5 << (char)0xC4 << (char)0xB9;
		}
		y++;
		gotoxy(x, y);
		cout << (char)0xBA << " " << (char)0xB3 << " " << (char)0xB3 << " " << (char)0xBA << " " << (char)0xB3
			<< " " << (char)0xB3 << " " << (char)0xBA << " " << (char)0xB3 << " " << (char)0xB3 << " " << (char)0xBA;
		y++;
		gotoxy(x, y);
		cout << (char)0xCC << (char)0xCD << (char)0xCE << (char)0xCD << (char)0xCE << (char)0xCD << (char)0xCE
			<< (char)0xCD << (char)0xCE << (char)0xCD << (char)0xCE << (char)0xCD << (char)0xCE
			<< (char)0xCD << (char)0xCE << (char)0xCD << (char)0xCE << (char)0xCD << (char)0xB9;
	}
	for (int i = 0; i < 2; i++)
	{
		y++;
		gotoxy(x, y);
		cout << (char)0xBA << " " << (char)0xB3 << " " << (char)0xB3 << " " << (char)0xBA << " " << (char)0xB3
			<< " " << (char)0xB3 << " " << (char)0xBA << " " << (char)0xB3 << " " << (char)0xB3 << " " << (char)0xBA;
		y++;
		gotoxy(x, y);
		cout << (char)0xCC << (char)0xC4 << (char)0xC5 << (char)0xC4 << (char)0xC5 << (char)0xC4 << (char)0xCE
			<< (char)0xC4 << (char)0xC5 << (char)0xC4 << (char)0xC5 << (char)0xC4 << (char)0xCE
			<< (char)0xC4 << (char)0xC5 << (char)0xC4 << (char)0xC5 << (char)0xC4 << (char)0xB9;
	}
	y++;
	gotoxy(x, y);
	cout << (char)0xBA << " " << (char)0xB3 << " " << (char)0xB3 << " " << (char)0xBA << " " << (char)0xB3
		<< " " << (char)0xB3 << " " << (char)0xBA << " " << (char)0xB3 << " " << (char)0xB3 << " " << (char)0xBA;
	y++;
	gotoxy(x, y);
	cout << (char)0xC8 << (char)0xCD << (char)0xCA << (char)0xCD << (char)0xCA << (char)0xCD << (char)0xCA
		<< (char)0xCD << (char)0xCA << (char)0xCD << (char)0xCA << (char)0xCD << (char)0xCA
		<< (char)0xCD << (char)0xCA << (char)0xCD << (char)0xCA << (char)0xCD << (char)0xBC;
}

void rysujPlanszeKomentarza(int x, int y)
{
	gotoxy(x, y);
	cout << "Komentarz:";
	y++;
	gotoxy(x, y);

	cout << (char)0xC9 << (char)0xCD << (char)0xCB << (char)0xCD << (char)0xCB << (char)0xCD << (char)0xCB
		<< (char)0xCD << (char)0xCB << (char)0xCD << (char)0xCB << (char)0xCD << (char)0xCB
		<< (char)0xCD << (char)0xCB << (char)0xCD << (char)0xCB << (char)0xCD << (char)0xBB;

	y++;
	gotoxy(x, y);
	cout << (char)0xBA << " " << (char)0xBA << " " << (char)0xBA << " " << (char)0xBA << " " << (char)0xBA
		<< " " << (char)0xBA << " " << (char)0xBA << " " << (char)0xBA << " " << (char)0xBA << " " << (char)0xBA;

	y++;
	gotoxy(x, y);
	cout << (char)0xC8 << (char)0xCD << (char)0xCA << (char)0xCD << (char)0xCA << (char)0xCD << (char)0xCA
		<< (char)0xCD << (char)0xCA << (char)0xCD << (char)0xCA << (char)0xCD << (char)0xCA
		<< (char)0xCD << (char)0xCA << (char)0xCD << (char)0xCA << (char)0xCD << (char)0xBC;
}

void rysujIloscKrokow(clock_t czas)
{
	gotoxy(POZYCJA_CZASU_X, POZYCJA_CZASU_Y);
	cout << "Ilosc krokow: " << iloscKrokow;
	gotoxy(POZYCJA_CZASU_X, POZYCJA_CZASU_Y + 1);
	cout << "Czas w sekundach: " << czas;
}

void rysujKomentarz(int x, int y)
{
	bool czySaKomentarze = false;
	int y1 = (y - POZYCJA_PLANSZY_Y - 1) / 2, x1 = (x - POZYCJA_PLANSZY_X - 1) / 2; // konwersja x i y na polozenie w tablicy sudoku
	int x2 = POZYCJA_KOMENTARZA_X + 1, y2 = POZYCJA_KOMENTARZA_Y + 1;				//ustawienie kursora w ramce komentarza
	gotoxy(x2, y2);

	for (int j = 0; j < 9; j++)		//sprawdzenie czy wystepuje komentarz
	{
		if (ogon->komentarz[y1][x1][j] != 0)
			czySaKomentarze = true;
	}

	if (czySaKomentarze == true)
	{
		rysujPlanszeKomentarza(POZYCJA_KOMENTARZA_X, POZYCJA_KOMENTARZA_Y);
		for (int j = 0; j < 9; j++)
		{
			gotoxy(x2, y2 + 1);
			if (ogon->komentarz[y1][x1][j] != 0)
				cout << ogon->komentarz[y1][x1][j];
			x2 += 2;
		}
	}
	else
	{
		gotoxy(POZYCJA_KOMENTARZA_X, POZYCJA_KOMENTARZA_Y);
		cout << "                                             ";
		gotoxy(POZYCJA_KOMENTARZA_X, POZYCJA_KOMENTARZA_Y + 1);
		cout << "                                             ";
		gotoxy(POZYCJA_KOMENTARZA_X, POZYCJA_KOMENTARZA_Y + 2);
		cout << "                                             ";
		gotoxy(POZYCJA_KOMENTARZA_X, POZYCJA_KOMENTARZA_Y + 3);
		cout << "                                             ";
	}


}

void wypiszPomoc(int x, int y)
{
	gotoxy(x, y);
	cout << "1..9 - wstawianie cyfry i nadpisanie cyfry";
	y++;
	gotoxy(x, y);
	cout << "backspace lub del - usuniecie cyfry";
	y++;
	gotoxy(x, y);
	cout << "spacja - tymczasowo pokoloruj wybrana liczbe";
	y++;
	gotoxy(x, y);
	cout << "u - undo";
	y++;
	gotoxy(x, y);
	cout << "r - redo";
	y++;
	gotoxy(x, y);
	cout << "l - lista mozliwych cyfr (mala litera L)";
	y++;
	gotoxy(x, y);
	cout << "p - podpowiedz";
	y++;
	gotoxy(x, y);
	cout << "s - zapisanie do pliku";
	y++;
	gotoxy(x, y);
	cout << "o - odczytanie pliku";
	y++;
	gotoxy(x, y);
	cout << "k - wejscie w tryb edycji komentarza";
	y++;
	gotoxy(x, y);
	cout << "q - zakonczenie gry";
}

//OPERACJE NA TABLICY SUDOKU I KOMENTARZACH

void wpiszLiczbe(int x, int y, char klawisz)
{
	int x2 = POZYCJA_PLANSZY_X, y2 = POZYCJA_PLANSZY_Y + 20; //wspolrzedne komunitatow

	bool bladWiersza = false, bladKolumny = false, bladBoxa = false;

	if (czyMoznaWstawicDoWiersza((y - POZYCJA_PLANSZY_Y - 1) / 2, klawisz) == false) bladWiersza = true;

	if (czyMoznaWstawicDoKolumny((x - POZYCJA_PLANSZY_X - 1) / 2, klawisz) == false) bladKolumny = true;

	if (czyMoznaWstawicDoBoxa((x - POZYCJA_PLANSZY_X - 1) / 2, (y - POZYCJA_PLANSZY_Y - 1) / 2, klawisz) == false) bladBoxa = true;

	if (bladBoxa == true || bladKolumny == true || bladWiersza == true)
	{
		if (bladBoxa == true)
		{
			gotoxy(x2, y2);
			cout << "Blad w boxie";
			y2++;
		}
		if (bladKolumny == true)
		{
			gotoxy(x2, y2);
			cout << "Blad w kolumnie";
			y2++;
		}
		if (bladWiersza == true)
		{
			gotoxy(x2, y2);
			cout << "Blad w wierszu";
			y2++;
		}

	}
	else
	{
		ileStanow++;
		gotoxy(x, y);
		if (klawisz == '0') cout << ' '; else cout << (char)klawisz;
		gotoxy(x, y);
		int cyfra = klawisz - 48;
		dodajDoTablicy((y - POZYCJA_PLANSZY_Y - 1) / 2, (x - POZYCJA_PLANSZY_X - 1) / 2, cyfra);
		for (int i = 0; i < iloscKrokowDoTylu; i++)
		{
			usunStanZListy(ogon->next);
			ileStanow--;
		}
	}
	if (bladBoxa == true || bladKolumny == true || bladWiersza == true)
	{
		Sleep(1000);
		gotoxy(POZYCJA_PLANSZY_X, POZYCJA_PLANSZY_Y + 20);
		cout << "                                                                                             " << endl;
		cout << "                                                                                             " << endl;
		cout << "                                                                                             " << endl;
	}
	iloscKrokowDoTylu = 0;
}

void wpiszLiczbeDoKomentarza(int x, int y, int xKom, char klawisz)
{
	bool czyMoznaWstawic = true;
	int pomocnicza = 0, z = 0;
	pomocnicza = klawisz - 48;
	int y1 = (y - POZYCJA_PLANSZY_Y - 1) / 2, x1 = (x - POZYCJA_PLANSZY_X - 1) / 2, x2 = (xKom - POZYCJA_KOMENTARZA_X - 1) / 2;

	for (int j = 0; j < 9; j++)		//sprawdzenie czy mozna wstawic cyfre robocza
	{
		if (ogon->komentarz[y1][x1][j] == pomocnicza) czyMoznaWstawic = false;
	}

	if (czyMoznaWstawic == true)
	{
		ileStanow++;
		dodajKomentarzDoTablicy(y1, x1, x2, pomocnicza);
		cout << klawisz;


		for (int i = 0; i < iloscKrokowDoTylu; i++)
		{
			usunStanZListy(ogon->next);
			ileStanow--;
		}
		iloscKrokowDoTylu = 0;
	}
}

void usunLiczbe(int x, int y)
{
	cout << " ";
	gotoxy(x, y);
	dodajDoTablicy((y - POZYCJA_PLANSZY_Y - 1) / 2, (x - POZYCJA_PLANSZY_X - 1) / 2, 0);

	for (int i = 0; i < iloscKrokowDoTylu; i++)
	{
		usunStanZListy(ogon->next);
		ileStanow--;
	}
	iloscKrokowDoTylu = 0;
}

void usunLiczbeZKomentarza(int x, int y, int xKom)
{
	int y1 = (y - POZYCJA_PLANSZY_Y - 1) / 2, x1 = (x - POZYCJA_PLANSZY_X - 1) / 2, x2 = (xKom - POZYCJA_KOMENTARZA_X - 1) / 2;

	ogon->komentarz[y1][x1][x2] = 0;
	cout << " ";

	for (int i = 0; i < iloscKrokowDoTylu; i++)
	{
		usunStanZListy(ogon->next);
		ileStanow--;
	}
	iloscKrokowDoTylu = 0;
}

//OPERACJE NA PLIKACH

void zapisz(int x, int y)
{
	gotoxy(x, y);
	cout << "Podaj nazwe pliku: ";
	string plik;
	plik = wpisywanieZnakow(x + 20, y);
	fstream plikzapis;
	plikzapis.open(plik + ".txt", ios::out); //otworzenie pliku
	if (plikzapis.good() == true) //sprawdzenie czy plik sie otworzyl
	{
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				plikzapis << ogon->sudoku[j][i];
			}
			plikzapis << "\n";
		}
		plikzapis.close(); //zamkniecie pliku
	}
	gotoxy(x, y);
	cout << "                                                                                             ";

} // funkcja zapisywania do txt

void zapiszXML(int x, int y)
{
	gotoxy(x, y);
	int x1, y1;
	int aktualnyStan = ogon->activeState;
	int aktywny = ogon->activeState;
	aktywny++;
	bool jestKomentarz = false;
	bool wypisane = false;
	cout << "Podaj nazwe pliku: ";
	string plik;
	plik = wpisywanieZnakow(x + 19, y);
	fstream plikzapis;
	plikzapis.open(plik + ".xml", ios::out); //otworzenie pliku
	if (plikzapis.good() == true) //sprawdzenie czy plik sie otworzyl
	{

		plikzapis << "<?xml version=\"1.0\"?>\n";
		plikzapis << "<sudoku active-state=\"" << aktywny << "\">\n";

		while (ogon->prev != NULL)		//przejscie do pierwszego stanu
		{
			ogon = ogon->prev;
		}

		for (int k = 1; k <= ileStanow+1; k++)		//wypisanie stanow 
		{
			plikzapis << "<state nr=\"" << k << "\">\n";
			plikzapis << "\t<board>\n";		//wypiszanie planszy
			for (int i = 0; i < 9; i++)
			{
				plikzapis << "\t\t";
				for (int j = 0; j < 9; j++)
				{
					if (ogon->sudoku[j][i] != 0)
						plikzapis << ogon->sudoku[j][i];
					else
						plikzapis << "-";
					plikzapis << " ";
				}
				plikzapis << "\n";
			}
			plikzapis << "\t</board>\n";
			if (czyWystepujaKomentarze() == true)		//sprawdza czy istnieja komentarze w obecnym stanie i wypisuje
			{
				plikzapis << "\t<comments>\n";
				for (int l = 0; l < 9; l++)
				{
					if (wypisane == true)
					{
						wypisane = false;
					}
					for (int m = 0; m < 9; m++)
					{
						for (int n = 0; n < 9; n++)
						{
							if (ogon->komentarz[m][l][n] != 0)
							{
								x1 = m; y1 = l;
								jestKomentarz = true;
								break;
							}
							if (jestKomentarz == true && wypisane == false)
							{
								plikzapis << "\t<comment row=\"" << x1 << "\" col=\"" << y1 << "\">";
								for (int o = 0; o < 9; o++)
								{
									if (ogon->komentarz[x1][y1][o] != 0)
										plikzapis << ogon->komentarz[x1][y1][o];
									else
										plikzapis << " ";
								}
								plikzapis << "</comment>\n";
								wypisane = true;
								jestKomentarz = false;
							}
						}
					}
				}

				plikzapis << "\t</comments>\n";
			}
			plikzapis << "</state>\n";
			if (ogon->next == NULL)
				ogon = ogon;
			else
			{
				ogon = ogon->next;
			}
		}
		plikzapis << "</sudoku>";

		plikzapis.close(); //zamkniecie pliku
	}
	while (ogon->activeState != aktualnyStan) //powrot do aktywnegoStanu
	{
		ogon = ogon->prev;
	}
	gotoxy(x, y);
	cout << "                                                                                             ";

}

void wczytajXML(int x1, int y1)
{
	int sudokuNew[9][9];
	int komentarzNew[9][9][9];

	for (int i = 0; i < 9; i++)		//wyzerowanie tablicy z komentarzami
	{
		for (int j = 0; j < 9; j++)
		{
			for (int k = 0; k < 9; k++)
			{
				komentarzNew[j][i][k] = 0;
			}
		}
	}

	int x = 0, y = 0, z = 0;
	int stan;
	char pomocnicza;
	string plik;
	string tabela;
	string active;
	string pomocniczaString;
	fstream plikodczyt;
	gotoxy(x1, y1);
	cout << "Podaj nazwe pliku: ";
	plik = wpisywanieZnakow(x1 + 19, y);
	plikodczyt.open(plik + ".xml", ios::in);
	if (plikodczyt.good() == true)
	{

		do		//szuka węzla z numerem aktywnego stanu
		{
			plikodczyt >> tabela;
		} while (tabela.find("active"));
		active = tabela;
		active.erase(0, active.find("\"") + 1);
		active.erase(active.find("\""));
		stan = zmienStringaNaInt(active) + ogon->activeState;
		do
		{
			do
			{
				do
				{
					plikodczyt >> tabela;
				} while (tabela.find("<board>"));


				while (tabela != "</board>")		//wczytanie planszy do tablicy
				{
					for (int i = 0; i < 9; i++)
					{
						for (int j = 0; j < 9; j++)
						{
							plikodczyt >> tabela;
							if (tabela == "-")
								sudokuNew[j][i] = 0;
							else
								sudokuNew[j][i] = zmienStringaNaInt(tabela);
						}
					}
					plikodczyt >> tabela;
				}

				plikodczyt >> tabela;

				if (tabela == "<comments>")		//sprawdzenie czy wystepuja komenentarze
				{
					do
					{
						getline(plikodczyt, tabela);
						if (!tabela.find("\t"))
							tabela.erase(tabela.find("\t"), 1);
						if (!tabela.find("<comment"))
						{
							tabela.erase(0, 9);
						}
						if (!tabela.find("row")) //gdy znajdzie row 
						{
							tabela.erase(0, 5);
							tabela.erase(tabela.find("\""), 1);
							pomocnicza = tabela[0];
							x = pomocnicza - 48; // wspolrzedna row przypisana do x
							tabela.erase(0, 2);
						}
						if (!tabela.find("col")) //gdy znajdzie col
						{
							tabela.erase(0, 5);
							tabela.erase(tabela.find("\""), 1);
							pomocnicza = tabela[0];
							y = pomocnicza - 48; // wspolrzedna col przypisana do y
							tabela.erase(0, 2);
							for (int i = 0; i < 9; i++)   // DODANIE KOMENTARZA
							{
								if (tabela[i] == ' ')		//gdy puste pole
									komentarzNew[y][x][i] = 0;
								else		//gdy liczba
									komentarzNew[y][x][i] = tabela[i] - 48;
							}
						}
						else
							continue;
					} while (tabela != "</comments>");
					plikodczyt >> tabela;
				}
				stworzNowyStan(sudokuNew, komentarzNew);
			} while (tabela != "</state>");
			plikodczyt >> tabela;
		} while (tabela != "</sudoku>");
		plikodczyt.close();			//zamkniecie pliku
	}
	ileStanow = ogon->activeState;//ile jest stanow
	//stan++;
	while (ogon->activeState != stan) //powrot do aktywnegoStanu
	{
		ogon = ogon->prev;
	}
	gotoxy(x1, y1);
	cout << "                                                       ";
	undoredo(ogon); //wyswietlenie aktywnego stanu
	x1 = 2 + POZYCJA_PLANSZY_X;
	y1 = 2 + POZYCJA_PLANSZY_Y;
	gotoxy(x1, y1);
	iloscKrokowDoTylu = ileStanow - stan;


}

void wczytaj(int x, int y)
{
	gotoxy(x, y);
	wcout << "Podaj nazwe pliku: ";
	string plik;
	plik = wpisywanieZnakow(x + 20, y);
	fstream plikodczyt;
	char tabela[9][9];
	plikodczyt.open(plik + ".txt", ios::in); //otworzenie pliku
	if (plikodczyt.good() == true) // wczytanie liczb do pomocniczej tablicy 
	{
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				plikodczyt >> tabela[j][i];
			}
		}
		plikodczyt.close(); //zamkniecie pliku
	}
	x = 1 + POZYCJA_PLANSZY_X;
	y = 1 + POZYCJA_PLANSZY_Y;
	gotoxy(x, y);
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			x += 2;
			if (tabela[j][i] == '0') cout << ' '; else cout << (char)tabela[j][i];
			gotoxy(x, y);
			ogon->sudoku[j][i] = tabela[j][i] - 48;
		}
		x = 1 + POZYCJA_PLANSZY_X;
		y += 2;
		gotoxy(x, y);
	}
	x = POZYCJA_PLANSZY_X;
	y = POZYCJA_PLANSZY_Y + 20;
	gotoxy(x, y);
	cout << "                                                       ";
	x = 2 + POZYCJA_PLANSZY_X;
	y = 2 + POZYCJA_PLANSZY_Y;
	gotoxy(x, y);
}

//PODPOWIEDZI

void wyswietlListeMozliwychCyfr(int x, int y)
{
	int x1 = (x - POZYCJA_PLANSZY_X - 1) / 2;
	int y1 = (y - POZYCJA_PLANSZY_Y - 1) / 2;
	int cyfry[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	//sprawdzanie w wierszu, kolumnie i boxie czy nie mozna jakiejs liczby wpisac, 
	//jezeli nie mozna to dana liczba w tabeli sie zeruje
	for (int j = 0; j < 9; j++)
	{
		for (int k = 0; k < 9; k++)
		{
			if (ogon->sudoku[j][(y - POZYCJA_PLANSZY_Y - 1) / 2] == cyfry[k])
				cyfry[k] = 0;
		}
	}
	for (int j = 0; j < 9; j++)
	{
		for (int k = 0; k < 9; k++)
		{
			if (ogon->sudoku[(x - POZYCJA_PLANSZY_X - 1) / 2][j] == cyfry[k])
				cyfry[k] = 0;
		}
	}

	int i, j;

	if (x1 == 0 || x1 == 1 || x1 == 2) i = 0;
	if (x1 == 3 || x1 == 4 || x1 == 5) i = 3;
	if (x1 == 6 || x1 == 7 || x1 == 8) i = 6;
	if (y1 == 0 || y1 == 1 || y1 == 2) j = 0;
	if (y1 == 3 || y1 == 4 || y1 == 5) j = 3;
	if (y1 == 6 || y1 == 7 || y1 == 8) j = 6;

	for (int k = 0; k < 3; k++)
	{
		for (int l = 0; l < 3; l++)
		{
			for (int m = 0; m < 9; m++)
			{
				if (ogon->sudoku[i + k][j + l] == cyfry[m])
					cyfry[m] = 0;
			}
		}
	}
	//wypisanie podpowiedzi
	gotoxy(POZYCJA_PLANSZY_X, POZYCJA_PLANSZY_Y + 20);
	cout << "Mozliwe cyfry do wpisania: ";
	for (int i = 0; i < 9; i++)
	{
		if (cyfry[i] != 0) cout << cyfry[i] << " ";
	}

	Sleep(1500);
	gotoxy(POZYCJA_PLANSZY_X, POZYCJA_PLANSZY_Y + 20);
	cout << "                                                                                             ";

}

int czyMoznaWypelnic(int x1, int y1)
{
	int cyfry[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int ileZer = 0;
	//sprawdzanie jakimi liczbami mozna wypelnic pole
	for (int j = 0; j < 9; j++)
	{
		for (int k = 0; k < 9; k++)
		{
			if (ogon->sudoku[j][y1] == cyfry[k])
				cyfry[k] = 0;
		}
	}
	for (int j = 0; j < 9; j++)
	{
		for (int k = 0; k < 9; k++)
		{
			if (ogon->sudoku[x1][j] == cyfry[k])
				cyfry[k] = 0;
		}
	}

	int i, j;

	if (x1 == 0 || x1 == 1 || x1 == 2) i = 0;
	if (x1 == 3 || x1 == 4 || x1 == 5) i = 3;
	if (x1 == 6 || x1 == 7 || x1 == 8) i = 6;
	if (y1 == 0 || y1 == 1 || y1 == 2) j = 0;
	if (y1 == 3 || y1 == 4 || y1 == 5) j = 3;
	if (y1 == 6 || y1 == 7 || y1 == 8) j = 6;

	for (int k = 0; k < 3; k++)
	{
		for (int l = 0; l < 3; l++)
		{
			for (int m = 0; m < 9; m++)
			{
				if (ogon->sudoku[i + k][j + l] == cyfry[m])
					cyfry[m] = 0;
			}
		}
	}
	//podliczenie ile zer wystepuje w 9 cyfrowej tablicy
	for (int i = 0; i < 9; i++)
	{
		if (cyfry[i] == 0)
			ileZer++;
	}


	if (ogon->sudoku[x1][y1] != 0)
		return 0;
	else
		for (int i = 0; i < 9; i++)
		{
		if (cyfry[i] != 0 && ileZer == 8)	//jezeli tablica nie jest pusta i mozna wpisac tylko 1 liczbe
		{									//to zwraca te liczbe
			return cyfry[i];
		}
		}
	return 0;
}

void znajdzPoleDoWypelnienia(int x, int y) {
	int pomocX = 0;
	int pomocY = 0;
	int liczba = 0;

	//przeszukanie tablicy sudoku w ktorym wystepuje tylko jednoznaczna podpowiedz
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			liczba = czyMoznaWypelnic(i, j);
			if (liczba != 0)
			{
				pomocY = j;
				break;
			}
		}
		if (liczba != 0)
		{
			pomocX = i;
			break;
		}
	}



	gotoxy(POZYCJA_PLANSZY_X, POZYCJA_PLANSZY_Y + 20);
	if (liczba == 0)
	{
		cout << "Brak mozliwych jednoznacznych liczb do wpisania.";
		Sleep(1000);
	}

	else		//wpisanie liczby z podpowiedzi
	{
		cout << "Mozna wypelnic pole X: " << ++pomocX << " Y: " << ++pomocY << " liczba " << liczba;
		gotoxy(POZYCJA_PLANSZY_X, POZYCJA_PLANSZY_Y + 21);
		cout << "Skorzystac z pomocy? T/n";
		char wybor = getch();
		if (wybor == 't' || wybor == 'T')
		{
			int x2 = 1 + POZYCJA_PLANSZY_X;
			int y2 = 1 + POZYCJA_PLANSZY_Y;
			pomocX--; pomocY--;
			x2 = x2 + pomocX * 2;
			y2 = y2 + pomocY * 2;
			wpiszLiczbe(x2, y2, liczba + 48);
		}
	}
	gotoxy(POZYCJA_PLANSZY_X, POZYCJA_PLANSZY_Y + 20);
	cout << "                                                                                             ";
	gotoxy(POZYCJA_PLANSZY_X, POZYCJA_PLANSZY_Y + 21);
	cout << "                                                                                             ";

}

void pokolorujLiczby(int x, int y, int attr)
{
	int x1 = (x - POZYCJA_PLANSZY_X - 1) / 2;
	int y1 = (y - POZYCJA_PLANSZY_Y - 1) / 2;
	textcolor(attr);
	gotoxy(x, y);
	int szukanaLiczba = 0;
	if (ogon->sudoku[x1][y1] != 0)
	{
		szukanaLiczba = ogon->sudoku[x1][y1];

		//pokolorowanie liczb
		x1 = POZYCJA_PLANSZY_X - 1;
		y1 = 1 + POZYCJA_PLANSZY_Y;
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				x1 += 2;
				if (ogon->sudoku[j][i] == szukanaLiczba)
				{
					gotoxy(x1, y1);
					cout << ogon->sudoku[j][i];
				}
			}

			x1 = POZYCJA_PLANSZY_X - 1;
			y1 += 2;
			gotoxy(x, y);


		}

		//odkolorowanie wybranych liczb
		Sleep(1200);
		textcolor(7);
		x1 = POZYCJA_PLANSZY_X - 1;
		y1 = 1 + POZYCJA_PLANSZY_Y;
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				x1 += 2;
				if (ogon->sudoku[j][i] == szukanaLiczba)
				{
					gotoxy(x1, y1);
					cout << ogon->sudoku[j][i];
				}
			}

			x1 = POZYCJA_PLANSZY_X - 1;
			y1 += 2;
			gotoxy(x, y);


		}


	}






}

void edytujKomentarz(int x, int y)
{
	int x1, y1, klawisz;
	x1 = POZYCJA_KOMENTARZA_X;
	y1 = POZYCJA_KOMENTARZA_Y;
	rysujPlanszeKomentarza(x1, y1);

	bool czySaKomentarze = false;
	int y2 = (y - POZYCJA_PLANSZY_Y - 1) / 2, x2 = (x - POZYCJA_PLANSZY_X - 1) / 2;	//konwersja wspolrzednych do wspolrzednych tablicy sudoku
	x1 = POZYCJA_KOMENTARZA_X + 1, y1 = POZYCJA_KOMENTARZA_Y + 1;	//ustawienie wspolrzednych komentarza dla kursora 

	for (int j = 0; j < 9; j++)
	{
		if (ogon->komentarz[y2][x2][j] != 0)
			czySaKomentarze = true;
	}

	if (czySaKomentarze == true)
	{
		rysujPlanszeKomentarza(POZYCJA_KOMENTARZA_X, POZYCJA_KOMENTARZA_Y);
		for (int j = 0; j < 9; j++)
		{
			gotoxy(x1, y1 + 1);
			if (ogon->komentarz[y2][x2][j] != 0)
				cout << ogon->komentarz[y2][x2][j];
			x1 += 2;
		}
	}

	x1 = POZYCJA_KOMENTARZA_X + 1;
	y1 = POZYCJA_KOMENTARZA_Y + 2;
	gotoxy(x1, y1);
	do
	{
		klawisz = getch();
		if (klawisz == 75)   // lewo
			if (x1 > POZYCJA_KOMENTARZA_X + 2)
			{
			x1 -= 2;
			gotoxy(x1, y1);
			}

		if (klawisz == 77)   // prawo
			if (x1 < POZYCJA_KOMENTARZA_X + 16)
			{
			x1 += 2;
			gotoxy(x1, y1);
			}
		if (klawisz == '1' || klawisz == '2' || klawisz == '3' || klawisz == '4' || klawisz == '5' ||
			klawisz == '6' || klawisz == '7' || klawisz == '8' || klawisz == '9')
		{
			iloscKrokow++;
			wpiszLiczbeDoKomentarza(x, y, x1, klawisz);
			gotoxy(x1, y1);
		}
		if (klawisz == 8)
		{
			iloscKrokow++;
			ileStanow++;
			usunLiczbeZKomentarza(x, y, x1);
			gotoxy(x1, y1);
		}

	} while (klawisz != 'k');

	gotoxy(POZYCJA_KOMENTARZA_X, POZYCJA_KOMENTARZA_Y);
	cout << "                                             ";
	gotoxy(POZYCJA_KOMENTARZA_X, POZYCJA_KOMENTARZA_Y + 1);
	cout << "                                             ";
	gotoxy(POZYCJA_KOMENTARZA_X, POZYCJA_KOMENTARZA_Y + 2);
	cout << "                                             ";
	gotoxy(POZYCJA_KOMENTARZA_X, POZYCJA_KOMENTARZA_Y + 3);
	cout << "                                             ";
}

int main()
{
	inicjalizuj(); // wyzerowanie listy 
	clock_t czas;
	settitle("Patryk Bejgrowicz - 149385");
	int klawisz, x, y;
	x = POZYCJA_POMOCY_X;
	y = POZYCJA_POMOCY_Y;
	wypiszPomoc(x, y);
	x = POZYCJA_PLANSZY_X;
	y = POZYCJA_PLANSZY_Y;
	rysujPlansze(x, y);
	x++;
	y++;
	gotoxy(x, y);
	// czytanie klawiszy
	do {
		czas = clock() / CLOCKS_PER_SEC;
		rysujIloscKrokow(czas);
		gotoxy(x, y);
		klawisz = getch();
		// poruszanie się po planszy
		if (klawisz == 72)   // góra
			if (y > POZYCJA_PLANSZY_Y + 2)
			{
			y -= 2;
			gotoxy(x, y);
			rysujKomentarz(x, y);
			gotoxy(x, y);
			}

		if (klawisz == 80)   // dół
			if (y < POZYCJA_PLANSZY_Y + 16)
			{
			y += 2;
			gotoxy(x, y);
			rysujKomentarz(x, y);
			gotoxy(x, y);
			}

		if (klawisz == 75)   // lewo
			if (x > POZYCJA_PLANSZY_X + 2)
			{
			x -= 2;
			gotoxy(x, y);
			rysujKomentarz(x, y);
			gotoxy(x, y);
			}

		if (klawisz == 77)   // prawo
			if (x < POZYCJA_PLANSZY_X + 16)
			{
			x += 2;
			gotoxy(x, y);
			rysujKomentarz(x, y);
			gotoxy(x, y);
			}

		// wpisanie cyfry
		if (klawisz == '1' || klawisz == '2' || klawisz == '3' || klawisz == '4' || klawisz == '5' ||
			klawisz == '6' || klawisz == '7' || klawisz == '8' || klawisz == '9')
		{
			iloscKrokow++;
			wpiszLiczbe(x, y, klawisz);
		}

		// usuniecie cyfry
		if (klawisz == 83 || klawisz == 44 || klawisz == 8)
		{
			iloscKrokow++;
			ileStanow++;
			usunLiczbe(x, y);
		}

		//wyswietla liste cyfr mozliwych do wpisania
		if (klawisz == 'l')
		{
			iloscKrokow++;
			wyswietlListeMozliwychCyfr(x, y);
		}

		//zapisuje plansze do pliku tekstowego
		if (klawisz == 's')
		{
			iloscKrokow++;
			zapiszXML(POZYCJA_PLANSZY_X, POZYCJA_PLANSZY_Y + 20);
			gotoxy(x, y);
		}

		//odczytuje plansze z pliku tekstowego
		if (klawisz == 'o')
		{
			iloscKrokow++;
			wczytajXML(POZYCJA_PLANSZY_X, POZYCJA_PLANSZY_Y + 20);
			gotoxy(x, y);
		}

		//wyswietla mozliwe pole z liczba do wpisania i pyta sie czy wpisac
		if (klawisz == 'p')
		{
			iloscKrokow++;
			znajdzPoleDoWypelnienia(POZYCJA_PLANSZY_X + 1, POZYCJA_PLANSZY_Y + 1);
			gotoxy(x, y);
		}

		//tymczasowo koloruje te same liczby
		if (klawisz == ' ')
		{
			iloscKrokow++;
			pokolorujLiczby(x, y, 12);
			textcolor(7);
			gotoxy(x, y);
		}
		//ruch do tylu
		if (klawisz == 'u')
		{
			if (ogon->prev == NULL)
				ogon = ogon;
			else
			{
				ogon = ogon->prev;
				iloscKrokow++;
			}
			iloscKrokowDoTylu++;
			undoredo(ogon);
			gotoxy(x, y);
			rysujKomentarz(x, y);
			gotoxy(x, y);
		}
		//ruch do przodu
		if (klawisz == 'r')
		{
			if (iloscKrokowDoTylu > 0)
			{
				if (ogon->next == NULL)
					ogon = ogon;
				else
				{
					ogon = ogon->next;
					iloscKrokow++;
				}
				iloscKrokowDoTylu--;
				undoredo(ogon);
				gotoxy(x, y);
				rysujKomentarz(x, y);
				gotoxy(x, y);
			}

		}
		//tryb edycji komentarza
		if (klawisz == 'k')
		{
			iloscKrokow++;
			edytujKomentarz(x, y);
			gotoxy(x, y);
		}

	} while (klawisz != 'q');
	gotoxy(POZYCJA_PLANSZY_X, POZYCJA_PLANSZY_Y + 20);
	return 0;
}