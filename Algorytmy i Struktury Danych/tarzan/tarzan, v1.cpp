// Tarzan Aisd.cpp : Defines the entry point for the console application.
//
#define _CRT_SECURE_NO_WARNINGS
 
#include <iostream>
#include <stdio.h>
#include <cmath>
 
using namespace std;
 
struct Wioska{
        int x;
        int y;
};
 
double obliczOdleglosc(int x1, int y1, int x2, int y2)
{
        double srodek = ((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
        double wynik = sqrt(srodek);
        if (wynik > 1000)
        {
                if (y1 == y2)
                        wynik = abs(x1 - x2);
                else
                        wynik = x1 + x2 + abs(y1 - y2);
                return wynik;
        }
        return wynik;
}
 
bool sprawdzCzyJestJuz(Wioska wioski[], Wioska *start, int x, int y, int ileWiosek)
{
        if (start->x == x && start->y == y)
                return true;
        for (int i = 0; i < ileWiosek; i++)
        {
                if (wioski[i].x == x && wioski[i].y == y)
                        return true;
        }
        return false;
}
 
void wylicz(Wioska *start, Wioska *poprzednia, Wioska *aktualna, Wioska wioski[], bool *ok, int ileWiosek, double odleglosc, double *MIN)
{
        if (odleglosc > *MIN)
                return;
 
        if (poprzednia == NULL)
        {
                wylicz(start, start, start, wioski, ok, ileWiosek, odleglosc, MIN);
        }
 
        bool pusta = true;
 
        for (int i = 0; i < ileWiosek; i++)
        {
                if (ok[i] != 0)
                {
 
                        pusta = false;
                        ok[i] = 0;
 
                        if (poprzednia != NULL)
                                wylicz(start, aktualna, &wioski[i], wioski, ok, ileWiosek, odleglosc + obliczOdleglosc(wioski[i].x, wioski[i].y, aktualna->x, aktualna->y), MIN);
 
 
                        ok[i] = 1;
                }
        }
        
 
        if (pusta == true)
        {
                double temp = obliczOdleglosc(aktualna->x, aktualna->y, start->x, start->y);
 
                if ((odleglosc + temp) < *MIN)
                {
                        *MIN = odleglosc + temp;
                }
        }
}
 
int main(int argc, char *argv[])
{
        int ileTestow, ileWiosek;
        int ilePowtorzonychWiosek = 0;
        int x = 0, y = 0;
        int odpowiedz;
        double odleglosc = 100000;
        cin >> ileTestow;
        Wioska *startowa = new Wioska();
        while (ileTestow--)
        {
                scanf("%d (", &ileWiosek);
                Wioska *wioski = new Wioska[ileWiosek];
                bool *ok = new bool[ileWiosek];
                for (int i = 0; i < ileWiosek; i++)
                {
                        if (i == 0)
                                scanf("(%d,%d),", &startowa->x, &startowa->y);
                        else if (i != ileWiosek - 1)
                        {
                                scanf("(%d,%d),", &x, &y);
                                if (sprawdzCzyJestJuz(wioski, startowa, x, y, i) == true)
                                {
                                        ilePowtorzonychWiosek++;
                                }
                                else
                                {
                                        wioski[i - 1 - ilePowtorzonychWiosek].x = x;
                                        wioski[i - 1 - ilePowtorzonychWiosek].y = y;
                                }
                        }
                        else
                        {
                                scanf("(%d,%d))", &x, &y);
                                if (sprawdzCzyJestJuz(wioski, startowa, x, y, i) == true)
                                {
                                        ilePowtorzonychWiosek++;
                                }
                                else
                                {
                                        wioski[i - 1 - ilePowtorzonychWiosek].x = x;
                                        wioski[i - 1 - ilePowtorzonychWiosek].y = y;
                                }
                        }
                        ok[i] = true;
                }
                ileWiosek -= ilePowtorzonychWiosek;
                /*cout  << "start " << startowa->x << "  " << startowa->y << "  " << endl;
                for (int j = 0; j < ileWiosek - 1; j++)
                {
                        cout <<  j << ".    " << wioski[j].x << "  " << wioski[j].y << "  " << endl;
                }*/
                wylicz(startowa, NULL, startowa, wioski, ok, ileWiosek - 1, 0, &odleglosc);
                odpowiedz = odleglosc;
                cout << odpowiedz << endl;
                odleglosc = 100000;
                ilePowtorzonychWiosek = 0;
                delete ok;
                delete wioski;
        }
 
        return 0;
}
 