// Projekt 3 AISD.cpp : Defines the entry point for the console application.
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
 
using namespace std;
 
 
struct Drzewo
{
        int wartosc;
        Drzewo *tablica;
};
 
void wstaw(Drzewo *korzen, int liczba, int n, int k)
{
        Drzewo *tmp = NULL;
        int liczba2 = liczba;
        if (korzen->wartosc == liczba2)
        {
                cout << liczba2 << " exist" << endl;
                return;
        }
        if (korzen->wartosc == NULL)
        {
                korzen->wartosc = liczba;
                for (int i = 0; i < n; i++)
                {
                        korzen->tablica[i].wartosc = NULL;
                }
        }
        else if (korzen->tablica[liczba % n].wartosc == NULL)
        {
                if (korzen->wartosc == liczba2)
                {
                        cout << liczba2 << " exist" << endl;
                        return;
                }
                korzen->tablica[liczba % n].wartosc = liczba;
                korzen->tablica[liczba % n].tablica = new Drzewo[k];
                for (int i = 0; i < k; i++)
                {
                        korzen->tablica[liczba % n].tablica[i].wartosc = NULL;
                }
        }
        else
        {
                tmp = &korzen->tablica[liczba% n];
                liczba = liczba / n;
                while (true)
                {
                        if (tmp->wartosc == liczba2)
                        {
                                cout << liczba2 << " exist" << endl;
                                return;
                        }
                        if (tmp->wartosc == 0)
                        {
                                tmp->wartosc = liczba2;
                                tmp->tablica = new Drzewo[k];
                                for (int i = 0; i < k; i++)
                                {
                                        tmp->tablica[i].wartosc = NULL;
                                }
                                break;
                        }
                        else
                        {
                                tmp = &tmp->tablica[liczba % k];
                                liczba = liczba / k;
                        }
                }
        }
 
 
}
 
void znajdz(Drzewo *korzen, int n, int k, int liczba, bool *czyZnalazlo)
{
        Drzewo *tmp;
        int liczba2 = liczba;
        if (korzen->wartosc == liczba2)
        {
                *czyZnalazlo = true;
                return;
        }
        if (korzen->tablica[liczba % n].wartosc == liczba)
        {
                *czyZnalazlo = true;
                return;
        }
        tmp = &korzen->tablica[liczba % n];
        liczba = liczba / n;
        while (tmp->wartosc != NULL)
        {
                if (tmp->wartosc == liczba2)
                {
                        *czyZnalazlo = true;
                        return;
                }
                else
                {
 
                        tmp = &tmp->tablica[liczba % k];
                        liczba = liczba / k;
                }
        }
        return;
}
 
void wyswietl(Drzewo *korzen, int n, int k)
{
        Drzewo *tmp;
        if (korzen->wartosc != NULL)
        {
                //cout << korzen->wartosc << " ";
                printf("%d ", korzen->wartosc);
                for (int i = 0; i < n; i++)
                {
                        wyswietl(&korzen->tablica[i], k, k);
                }
        }
}
 
void usun(Drzewo *korzen, int n, int k, int liczba)
{
        Drzewo *tmp, *tmp2;
        tmp2 = NULL;
        int liczba2 = liczba;
        int najbardziejLewy = -1;
 
        if (korzen->wartosc == NULL)
                return;
 
 
        ////USUWANIE Z KORZENIA
        if (korzen->wartosc == liczba2)
        {
                for (int i = 0; i < n; i++)
                        if (korzen->tablica[i].wartosc != NULL)
                        {
                                najbardziejLewy = i;
                                break;
                        }
                if (najbardziejLewy != -1)
                {
                        tmp = &korzen->tablica[najbardziejLewy];
                        while (tmp->wartosc != NULL)
                        {
                                najbardziejLewy = -1;
                                for (int i = 0; i < k; i++)
                                        if (tmp->tablica[i].wartosc != NULL)
                                        {
                                                najbardziejLewy = i;
                                                break;
                                        }
                                if (najbardziejLewy == -1)
                                {
                                        korzen->wartosc = tmp->wartosc;
                                        tmp->wartosc = NULL;
                                        delete[] tmp->tablica;
                                        tmp = nullptr;
                                        delete tmp;
                                        return;
                                }
                                if (tmp->wartosc != NULL)
                                {
                                        korzen->wartosc = tmp->wartosc;
                                        tmp2 = tmp;
                                }
                                tmp = &tmp->tablica[najbardziejLewy];
                        }
                        tmp2->wartosc = NULL;
                        delete[] tmp2->tablica;
                        tmp2 = nullptr;
                        delete tmp2;
                }
                else
                {
                        korzen->wartosc = NULL;
                        return;
                }
        }
 
        //USUANIE Z PIERWSZEJ TABLICY
        if (korzen->tablica[liczba % n].wartosc == liczba)
        {
                for (int i = 0; i < k; i++)
                        if (korzen->tablica[liczba % n].tablica[i].wartosc != NULL)
                        {
                        najbardziejLewy = i;
                        break;
                        }
                if (najbardziejLewy != -1)
                {
                        tmp = &korzen->tablica[liczba%n].tablica[najbardziejLewy];
                        while (tmp->wartosc != NULL)
                        {
                                for (int i = 0; i < k; i++)
                                        if (tmp->tablica[i].wartosc != NULL)
                                        {
                                        najbardziejLewy = i;
                                        break;
                                        }
                                if (tmp->wartosc != 0)
                                {
                                        korzen->tablica[liczba % n].wartosc = tmp->wartosc;
                                        tmp2 = tmp;
                                }
                                tmp = &tmp->tablica[najbardziejLewy];
                        }
                        tmp2->wartosc = NULL;
                        delete[] tmp2->tablica;
                        tmp2 = nullptr;
                        delete tmp2;
                }
                else
                {
                        korzen->tablica[liczba % n].wartosc = NULL;
                        delete[] korzen->tablica[liczba % n].tablica;
                        return;
                }
        }
 
        //USUANIE Z KOLEJNYCH TABLIC
        tmp = &korzen->tablica[liczba % n];
        liczba = liczba / n;
        while (tmp->wartosc != NULL)
        {
                if (tmp->wartosc == liczba2)
                {
                        for (int i = 0; i < k; i++)
                                if (tmp->tablica[i].wartosc != NULL)
                                {
                                najbardziejLewy = i;
                                break;
                                }
                        if (najbardziejLewy != -1)
                        {
                                tmp2 = &tmp->tablica[najbardziejLewy];
                                while (tmp2->wartosc != NULL)
                                {
                                        najbardziejLewy = -1;
                                        for (int i = 0; i < k; i++)
                                                if (tmp2->tablica[i].wartosc != NULL)
                                                {
                                                najbardziejLewy = i;
                                                break;
                                                }
                                        if (najbardziejLewy == -1)
                                        {
                                                tmp->wartosc = tmp2->wartosc;
                                                tmp2->wartosc = NULL;
                                                delete[] tmp2->tablica;
                                                tmp2 = nullptr;
                                                delete tmp2;
                                                return;
                                        }
                                        tmp2 = &tmp2->tablica[najbardziejLewy];
                                }
                                tmp2->wartosc = NULL;
                                delete[] tmp2->tablica;
                                tmp2 = nullptr;
                                delete tmp2;
                        }
                        else
                        {
                                tmp->wartosc = NULL;
                                return;
                        }
                        return;
                }
                else
                {
                        tmp = &tmp->tablica[liczba % k];
                        liczba = liczba / k;
                }
        }
 
 
 
 
        return;
}
 
int main()
{
        int ileTestow, min, max, n, k;
        char znak;
        int liczba;
        bool czyZnalazlo = false;
        cin >> ileTestow >> min >> max >> n >> k;
        Drzewo korzen;
        korzen.wartosc = NULL;
        korzen.tablica = new Drzewo[n];
        while (ileTestow--)
        {
                //cin >> znak;
                scanf("\n%c", &znak);
                if (znak == 'I')
                {
                        //cin >> liczba;
                        scanf("%d", &liczba);
                        if (liczba <= max && liczba >= min)
                                wstaw(&korzen, liczba, n, k);
                }
                else if (znak == 'L')
                {
                        //cin >> liczba;
                        scanf(" %d", &liczba);
                        znajdz(&korzen, n, k, liczba, &czyZnalazlo);
                        if (czyZnalazlo == true)
                                cout << liczba << " exist" << endl;
                        else
                                cout << liczba << " not exist" << endl;
                        czyZnalazlo = false;
                }
                else if (znak == 'D')
                {
                        //cin >> liczba;
                        scanf(" %d", &liczba);
                        znajdz(&korzen, n, k, liczba, &czyZnalazlo);
                        if (czyZnalazlo == false)
                                cout << liczba << " not exist" << endl;
                        else
                                if (liczba <= max && liczba >= min)
                                        usun(&korzen, n, k, liczba);
                        czyZnalazlo = false;
                        //usun(liczba);
                }
                else if (znak == 'P')
                {
                        wyswietl(&korzen, n, k);
                        cout << endl;
                }
 
        }
        return 0;
}