// Projekt 4 AISD.cpp : Defines the entry point for the console application.
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
 
using namespace std;
 
void parser(int matrix[200][200], int n)
{
        char *tab = NULL;
        int liczba = 0;
        int tempLiczba = 0;
        int k = 0, l = 0;
        tab = new char[n*n * 4];
        fgets(tab, n*n * 4, stdin);
        for (int i = 0;; i++)
        {
                if (tab[i] == '\0')
                        break;
                if (tab[i] == ' ')
                        continue;
                if ((tab[i + 1] <= '9' || tab[i + 1] >= '0') && (tab[i + 1] == '\0' || tab[i + 1] == ' '))
                {
                        liczba = tempLiczba + tab[i] - 48;
                        if (liczba < 0)
                                liczba = 0;
                        matrix[k][l] = liczba;
                        k++;
                        if (k == n)
                        {
                                k = 0;
                                l++;
                        }
                        liczba = 0;
                        tempLiczba = 0;
                }
                else
                        tempLiczba += (tab[i] - 48) * 10;
        }
        delete[] tab;
}
 
struct Zbior
{
        int ileElemetnow;
        bool wierzcholki[200];
};
 
void wyznaczSasiadow(Zbior *docelowy1, Zbior *sasiedzi, Zbior  *poczatkowy1, Zbior *R, int matrix[200][200], int numerWierzcholka, int numerPodgrafu, int n)
{
 
        R->ileElemetnow = 0;
        poczatkowy1->ileElemetnow = 0;
 
        //dodanie sasiadow
        for (int i = 0; i < n; i++)
        {
                //podliczenie elementow w zbiorach poczatkowych
                if (R->wierzcholki[i] == true)
                        R->ileElemetnow++;
                if (poczatkowy1->wierzcholki[i] == true)
                        poczatkowy1->ileElemetnow++;
 
                //wyzerowanie sasiadow
                sasiedzi->wierzcholki[i] = false;
 
                //dodanie sasiadow
                if (numerPodgrafu == matrix[numerWierzcholka][i])
                {
                        sasiedzi->ileElemetnow++;
                        sasiedzi->wierzcholki[i] = true;
                }
 
                //czesc wspolna ze zbiorem pierwszym
                if (sasiedzi->wierzcholki[i] == true && poczatkowy1->wierzcholki[i] == true)
                {
                        docelowy1->wierzcholki[i] = true;
                        docelowy1->ileElemetnow++;
                }
                else
                        docelowy1->wierzcholki[i] = false;
        }
}
 
void BronKerbosh(Zbior *R, Zbior *P, int matrix[200][200], int n, int numerPodgrafu, int p, bool *ok)
{
        if (*ok == true)
                return;
 
        Zbior PTemp, RTemp; //zbiory pomocnicze
        Zbior N;
        int ileElementow = 0;
        N.ileElemetnow = 0;
        PTemp.ileElemetnow = 0;
        RTemp = *R;
        RTemp.ileElemetnow = 0;
 
 
        if (R->ileElemetnow >= p)
        {
                *ok = true;
                return;
        }
        else
        {
                for (int i = 0; i < n; i++)
                {
                        if (P->wierzcholki[i] == true) //dla kazdego wierzcholka w P
                        {
                                if (*ok == true)
                                        return;
                                if (RTemp.wierzcholki[i] == false)
                                        RTemp.ileElemetnow++;
                                RTemp.wierzcholki[i] = true;
 
                                wyznaczSasiadow(&PTemp, &N, P, &RTemp, matrix, i, numerPodgrafu, n);
 
                                if (PTemp.ileElemetnow + RTemp.ileElemetnow >= p && N.ileElemetnow >= p)
                                        BronKerbosh(&RTemp, &PTemp, matrix, n, numerPodgrafu, p, ok);
 
                                if (P->wierzcholki[i] == true)
                                        P->ileElemetnow--;
                                P->wierzcholki[i] = false;
 
                                RTemp.wierzcholki[i] = false;
                                RTemp.ileElemetnow--;
                        }
                }
 
        }
}
 
int main()
{
        int n, k, p;
        int ileSasiadow = 0;
        Zbior R, P;
        int matrix[200][200];
 
        bool ok = false;
        while (scanf("%d %d %d\n", &n, &k, &p) != EOF)
        {
                P.ileElemetnow = 0;
                R.ileElemetnow = 0;
                parser(matrix, n);
                for (int l = 1; l <= k; l++)
                {
                        if (ok == true)
                                break;
                        for (int i = 1; i < n; i++)
                        {
                                for (int j = 0; j < i; j++)
                                {
                                        if (l == matrix[i][j])
                                        {
                                                if (P.wierzcholki[i] == false && P.wierzcholki[j] == false)
                                                        P.ileElemetnow++;
                                                P.wierzcholki[i] = true;
                                                P.wierzcholki[j] = true;
                                        }
                                }
                        }
                        for (int i = 0; i < n; i++)
                        {
                                if (P.wierzcholki[i])
                                        for (int j = 0; j < n; j++)
                                        {
                                        if (l == matrix[i][j])
                                                ileSasiadow++;
                                        }
                                if (ileSasiadow < p - 1)
                                        P.wierzcholki[i] = false;
                                ileSasiadow = 0;
                        }
                        if (n == 1)
                        {
                                ok = true;
                                break;
                        }
                        else if (ok == false && n != 1)
                                BronKerbosh(&R, &P, matrix, n, l, p, &ok);
                }
                if (ok == false)
                        printf("Nie\n");
                else
                {
                        printf("Tak\n");
                        ok = false;
                }
        }
        return 0;
}
 