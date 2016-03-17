// Projekt 2 AISD.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <vector>

#define ROZMIAR_KOLEJEK 1000
#define ROZMIAR_MAPY 1500

using namespace std;

struct Wierzcholek{
	int x;
	int y;
	int wysokoscGory;
	bool odwiedzone;
	int * koszt;
};


struct Kolejka{
	int x;
	int y;
	int koncX;
	int koncY;
	int czasTrwania;
	int coIle;
	Kolejka *next;
};

struct Kopiec{
	Wierzcholek punkt;
	int *priorytet;
	bool usuniety;
};

struct Lista{
	Wierzcholek punkt;
	struct Lista *next;
	struct Lista *prev;
} *ogon = NULL, *glowa = NULL;

void dodajDoListy(Wierzcholek punkt)
{
	//dodanie nowego elementu do tablicy
	struct Lista *stan;

	//sprawdzenie czy mozna przydzielic mu pamiec
	if ((stan = (struct Lista *)malloc(sizeof(struct Lista))) == NULL)
		return;

	stan->punkt = punkt;
	if (glowa == NULL)
	{
		stan->next = NULL;
		stan->prev = NULL;
		glowa = ogon = stan;
	}
	else
	{
		stan->next = NULL;
		stan->prev = ogon;
		ogon->next = stan;
		ogon = stan;
	}
	
}

void usunZListy(struct Lista *stan)
{
	//sprawdza czy stan nie jest pusty 
	if (stan == NULL)
		return;
	if (stan->prev == NULL && stan->next == NULL) // je¿eli usuwamy glowe, bez nastenych elementow
	{
		glowa = ogon = NULL;
	}
	else if (stan->prev == NULL) // je¿eli usuwamy z pocz¹tku listy
	{
		stan->next->prev = NULL;
	}
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

//Algorytm Kopca z ksi¹¿ki "Wprowadzenie do Algorytmów" Thomasa Cormena str. 151 - 167
int indeksOjca(int pozycja)
{
	return pozycja / 2;
}

int indeksLewegoSyna(int pozycja)
{
	return 2 * pozycja + 1;
}

int indeksPrawegoSyna(int pozycja)
{
	return 2 * pozycja + 2;
}

void przywrocWlasnoscKopca(Kopiec *kopiec, int pozycja, int rozmiar)
{
	for (int i = 0; i < rozmiar; i++)
	{
		std::cout << *kopiec[i].priorytet << " ";
	}

	std::cout << std::endl;

	int l = indeksLewegoSyna(pozycja), r = indeksPrawegoSyna(pozycja);
	int najmniejszy = 0;

	if ( l<rozmiar && *kopiec[l].priorytet < *kopiec[pozycja].priorytet)
	najmniejszy = l;
	else
	najmniejszy = pozycja;
	if ( r<rozmiar && *kopiec[r].priorytet < *kopiec[najmniejszy].priorytet)
	najmniejszy = r;
	if (najmniejszy != pozycja)
	{
	Kopiec temp = kopiec[pozycja];
	kopiec[pozycja] = kopiec[najmniejszy];
	kopiec[najmniejszy] = temp;
	przywrocWlasnoscKopca(kopiec, najmniejszy,rozmiar);
	}
	
	/*while (pozycja < rozmiar / 2){
		int l = indeksLewegoSyna(pozycja), p = indeksPrawegoSyna(pozycja);


		if (l < rozmiar && *kopiec[l].priorytet < *kopiec[pozycja].priorytet)
		{
			temp = kopiec[pozycja];
			kopiec[pozycja] = kopiec[l];
			kopiec[l] = temp;
			pozycja = -1;
		}
		if (pozycja>=0)
		if (p < rozmiar&& *kopiec[p].priorytet < *kopiec[pozycja].priorytet)
		{
			temp = kopiec[pozycja];
			kopiec[pozycja] = kopiec[p];
			kopiec[p] = temp;
			pozycja = -1;

			
		}
		pozycja++;
	}
	for (int i = 0; i < rozmiar; i++)
	{
	std::cout << *kopiec[i].priorytet << " ";
	}
	std::cout << std::endl;*/
}




Wierzcholek zwrocMin(Kopiec *kopiec, int *pozycja)
{
	Kopiec *temp2 = NULL;
	Wierzcholek *temp = NULL;
	if (*pozycja < 1)
		return *temp;
	Wierzcholek min = kopiec[1].punkt;
	kopiec[1] = kopiec[*pozycja];
	kopiec[*pozycja].usuniety = true;
//	przywrocWlasnoscKopca(kopiec, 1);
	return min;
}

/*void wstawDoKopca(Kopiec *kopiec, int *pozycja, Wierzcholek punkt)
{
	kopiec[*pozycja + 1].punkt = punkt;
	kopiec[*pozycja + 1].priorytet = ((punkt.x * 2 + punkt.y * 2) / 2);
	kopiec[*pozycja + 1].usuniety = false;
//	przywrocWlasnoscKopca(kopiec, *pozycja);
}*/

int obliczKoszt(int A, int B)
{
	if (A > B)
		return 1;
	else
		return B - A + 1;
}

bool czyNaMapie(int x, int y, int wysokosc, int szerokosc)
{
	return (x >= 0 && x < szerokosc && y >= 0 && y < wysokosc);
}

int haszowanie(int x, int y)
{
	return (x * 13 + y * 29) % ROZMIAR_KOLEJEK;
}

void dijkstra(Wierzcholek Mapa[ROZMIAR_MAPY][ROZMIAR_MAPY], Kolejka mapa[ROZMIAR_KOLEJEK], int wysokosc, int szerokosc, int sx, int sy, int ex, int ey)
{
	Wierzcholek v;
	Wierzcholek w;
	Mapa[sx][sy].koszt = 0;
	Mapa[sx][sy].odwiedzone = true;
	dodajDoListy(Mapa[sx][sy]);
	bool ok = false;
	while (glowa != NULL && !ok)
	{
		v = glowa->punkt;
		Lista *tmp = glowa;
		Lista *doUsuniecia = tmp;
		while (tmp != NULL)
		{
			if (v.koszt > tmp->punkt.koszt)
			{
				v = tmp->punkt;
				doUsuniecia = tmp;
			}
			tmp = tmp->next;
		}
		if (doUsuniecia != glowa)
			usunZListy(doUsuniecia);
		else
			glowa = glowa->next;

		if (mapa[haszowanie(v.x, v.y)].x != -1)
		{
			Kolejka *tmp = &mapa[haszowanie(v.x, v.y)];
			while (tmp)
			{
				if (Mapa[tmp->koncX][tmp->koncY].odwiedzone == false)
				{
					*Mapa[tmp->koncX][tmp->koncY].koszt = *Mapa[v.x][v.y].koszt + tmp->czasTrwania + (tmp->coIle - *Mapa[v.x][v.y].koszt%tmp->coIle) % tmp->coIle;
					Mapa[tmp->koncX][tmp->koncY].odwiedzone = true;
					dodajDoListy(Mapa[tmp->koncX][tmp->koncY]);
				}
				else
				{
					if (Mapa[tmp->koncX][tmp->koncY].koszt > Mapa[v.x][v.y].koszt + tmp->czasTrwania + *Mapa[v.x][v.y].koszt%tmp->coIle)
					{
						*Mapa[tmp->koncX][tmp->koncY].koszt = *Mapa[v.x][v.y].koszt + tmp->czasTrwania + (tmp->coIle - *Mapa[v.x][v.y].koszt%tmp->coIle) % tmp->coIle;
						Mapa[tmp->koncX][tmp->koncY].odwiedzone = true;
					}
				}
				tmp = tmp->next;
			}
		}

		for (int i = 0; i < 4; i++)
		{
			w = v;
			if (i == 0)
				w.y += 1;
			else if (i == 1)
				w.y -= 1;
			else if (i == 2)
				w.x += 1;
			else if (i == 3)
				w.x -= 1;


			if (czyNaMapie(w.y, w.x, wysokosc, szerokosc))
			{
				if (Mapa[w.x][w.y].odwiedzone == false){
					Mapa[w.x][w.y].koszt = Mapa[v.x][v.y].koszt + obliczKoszt(Mapa[v.x][v.y].wysokoscGory, Mapa[w.x][w.y].wysokoscGory);
					Mapa[w.x][w.y].odwiedzone = true;
					if (w.y == ey && w.x == ex)
					{
						ok = true;
					}
					else
					{
						dodajDoListy(Mapa[w.x][w.y]);
					}
				}

				else{
					if (Mapa[w.x][w.y].koszt > Mapa[v.x][v.y].koszt + obliczKoszt(Mapa[v.x][v.y].wysokoscGory, Mapa[w.x][w.y].wysokoscGory))
						Mapa[w.x][w.y].koszt = Mapa[v.x][v.y].koszt + obliczKoszt(Mapa[v.x][v.y].wysokoscGory, Mapa[w.x][w.y].wysokoscGory);
				}
			}
		}
	}

}


void dijkstra2(Wierzcholek **Mapa, Kolejka* mapa, Kopiec * kopiec, int rozmiar_kopca,int wysokosc, int szerokosc, int sx, int sy, int ex, int ey)
{
	Wierzcholek v;
	Wierzcholek w;
	*Mapa[sy][sx].koszt = 0;
	Mapa[sy][sx].odwiedzone = true;
//	int rozmiar_kopca = 0;
	//kopiec[rozmiar_kopca].punkt = Mapa[sy][sx];
	//kopiec[rozmiar_kopca].priorytet = Mapa[sy][sx].koszt;
	//dodajDoListy(Mapa[sx][sy]);
	bool ok = false;
	while (!ok)
	{
		Kopiec tmp2 = kopiec[0];
		//kopiec[0] = kopiec[rozmiar_kopca-1];
		//kopiec[rozmiar_kopca-1] = tmp2;
		przywrocWlasnoscKopca(kopiec, 0, rozmiar_kopca);
		v = kopiec[0].punkt;
		 tmp2 = kopiec[0];
		kopiec[0] = kopiec[rozmiar_kopca-1];
		kopiec[rozmiar_kopca-1] = tmp2;
		rozmiar_kopca--;
		if (v.y == ey && v.x == ex)
		{
			ok = true;
		}
		
		
		if (mapa[haszowanie(v.x, v.y)].x != -1)
		{
			Kolejka *tmp = &mapa[haszowanie(v.x, v.y)];
			while (tmp)
			{
				if (Mapa[tmp->koncX][tmp->koncY].odwiedzone == false)
				{
					//rozmiar_kopca++;
					*Mapa[tmp->koncX][tmp->koncY].koszt = *Mapa[v.y][v.x].koszt + tmp->czasTrwania + (tmp->coIle - *Mapa[v.y][v.x].koszt%tmp->coIle) % tmp->coIle;
					Mapa[tmp->koncX][tmp->koncY].odwiedzone = true;
					//kopiec[rozmiar_kopca].punkt = Mapa[tmp->koncX][tmp->koncY];
					//kopiec[rozmiar_kopca].priorytet = Mapa[tmp->koncX][tmp->koncY].koszt;
					//tmp2 = kopiec[0];
					//kopiec[0] = kopiec[rozmiar_kopca];
					//kopiec[rozmiar_kopca] = tmp2;
					//przywrocWlasnoscKopca(kopiec, 0, rozmiar_kopca + 1);
				}
				else
				{
					if (*Mapa[tmp->koncX][tmp->koncY].koszt > *Mapa[v.y][v.x].koszt + tmp->czasTrwania + *Mapa[v.y][v.x].koszt%tmp->coIle)
					{
						*Mapa[tmp->koncX][tmp->koncY].koszt = *Mapa[v.y][v.x].koszt + tmp->czasTrwania + (tmp->coIle - *Mapa[v.y][v.x].koszt%tmp->coIle) % tmp->coIle;
						Mapa[tmp->koncX][tmp->koncY].odwiedzone = true;
					}
				}
				tmp = tmp->next;
			}
		}

		for (int i = 0; i < 4; i++)
		{
			w = v;
			if (i == 0)
				w.y += 1;
			else if (i == 1)
				w.y -= 1;
			else if (i == 2)
				w.x += 1;
			else if (i == 3)
				w.x -= 1;


			if (czyNaMapie(w.x, w.y, wysokosc, szerokosc))
			{
				if (Mapa[w.y][w.x].odwiedzone == false){
					*Mapa[w.y][w.x].koszt = *Mapa[v.y][v.x].koszt + obliczKoszt(Mapa[v.y][v.x].wysokoscGory, Mapa[w.y][w.x].wysokoscGory);
					Mapa[w.y][w.x].odwiedzone = true;
					if (w.y == ey && w.x == ex)
					{
						ok = true;
					}
					else
					{
						/*rozmiar_kopca++;
						kopiec[rozmiar_kopca].punkt = Mapa[w.y][w.x];
						kopiec[rozmiar_kopca].priorytet = Mapa[w.y][w.x].koszt;
						tmp2 = kopiec[0];
						kopiec[0] = kopiec[rozmiar_kopca];
						kopiec[rozmiar_kopca] = tmp2;
						przywrocWlasnoscKopca(kopiec, 0, rozmiar_kopca + 1);*/
					}
				}

				else{
					if (*Mapa[w.y][w.x].koszt > *Mapa[v.y][v.x].koszt + obliczKoszt(Mapa[v.y][v.x].wysokoscGory, Mapa[w.y][w.x].wysokoscGory))
						*Mapa[w.y][w.x].koszt = *Mapa[v.y][v.x].koszt + obliczKoszt(Mapa[v.y][v.x].wysokoscGory, Mapa[w.y][w.x].wysokoscGory);
				}
			}
		}
	}

}


int main()
{
	Kolejka mapa[1000];
	for (int i = 0; i < ROZMIAR_KOLEJEK; i++)
	{
		mapa[i].x = -1;
	}
	int szerokoscMapy = 0, wysokoscMapy = 0, posStartX, posStartY, posEndX, posEndY, ileWyciagow; //dane wejsciowe
	int posStartWycX, posStartWycY, posEndWycX, posEndWycY, czasPodrozy, minutyOdjazdu; // zmienne dla wyciagu


	cin >> szerokoscMapy >> wysokoscMapy >> posStartX >> posStartY >> posEndX >> posEndY >> ileWyciagow;

	Kopiec *kopiec = new Kopiec[wysokoscMapy*szerokoscMapy];
	int rozmiar_kopca = 0;
	Wierzcholek **Mapa = new Wierzcholek*[wysokoscMapy];
	int posX = posStartX, posY = posStartY;
	while (ileWyciagow--)
	{
		Kolejka *tmp = new Kolejka();
		cin >> posStartWycX >> posStartWycY >> posEndWycX >> posEndWycY >> czasPodrozy >> minutyOdjazdu;
		tmp->x = posStartWycX;
		tmp->y = posStartWycY;
		tmp->koncX = posEndWycY;
		tmp->koncY = posEndWycX;
		tmp->czasTrwania = czasPodrozy;
		tmp->coIle = minutyOdjazdu;
		tmp->next = NULL;

		if (mapa[haszowanie(tmp->x, tmp->y)].x != -1)
		{
			Kolejka *tmp2 = &mapa[haszowanie(tmp->x, tmp->y)];
			while (tmp2->next != NULL)
			{
				tmp2 = tmp2->next;
			}
			tmp2->next = tmp;
		}
		else
			mapa[haszowanie(tmp->x, tmp->y)] = *tmp;
	}
	for (int i = 0; i < wysokoscMapy; i++)
	{
		Mapa[i] = new Wierzcholek[szerokoscMapy];

		for (int j = 0; j < szerokoscMapy; j++)
		{
			cin >> Mapa[i][j].wysokoscGory;
			Mapa[i][j].x = j;
			Mapa[i][j].y = i;
			Mapa[i][j].odwiedzone = false;
			Mapa[i][j].koszt = new int;
			*Mapa[i][j].koszt = INT_MAX;
			kopiec[rozmiar_kopca].punkt = Mapa[i][j];
			kopiec[rozmiar_kopca].priorytet = Mapa[i][j].koszt;
			rozmiar_kopca++;

		}
	}

	dijkstra2(Mapa, mapa, kopiec, rozmiar_kopca, wysokoscMapy, szerokoscMapy, posStartX, posStartY, posEndX, posEndY);
	cout << *Mapa[posEndY][posEndX].koszt;
	//MAPA DO WYŒWIETLENIA
	/*cout << endl;
	for (int i = 0; i < wysokoscMapy; i++)
	{
		for (int j = 0; j < szerokoscMapy; j++)
		{
			cout << *Mapa[j][i].koszt << "  ";
		}
		cout << endl;
	}*/

	return 0;
}