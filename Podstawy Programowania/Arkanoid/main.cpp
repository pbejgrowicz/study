#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <fstream>
#include <ctime>
#include <iostream>


using namespace std;

extern "C" {
	//#ifdef BIT64
	//#include"./sdl64/include/SDL.h"
	//#include"./sdl64/include/SDL_main.h"
	//#else
#include"./sdl/include/SDL.h"
#include"./sdl/include/SDL_main.h"
	//#endif
}

#define SCREEN_WIDTH	780
#define SCREEN_HEIGHT	480
#define MAX_MAP_X 15
#define MAX_MAP_Y 16

//Stale do konfiguracji gry
#define PREDKOSC_PILECZKI 1
#define PUNKTY_ZA_SZARE 150
#define PUNKTY_ZA_CZERWONE 130
#define PUNKTY_ZA_ZOLTE 110
#define PUNKTY_ZA_NIEBIESKIE 90
#define PUNKTY_ZA_ROZOWE 70
#define PUNKTY_ZA_ZIELONE 50
#define PRAWDOPODOBIENSTWO 7  //wieksza wartosc to mniejsze prawdopodobienstwo, minimum 6 zeby dzialaly wszystkie nagrody
#define PUNKTY_ZA_TEMPO 90
#define PUNKTY_ZA_PALETKE 110
#define PUNKTY_ZA_ZYCIE 120
#define PUNKTY_ZA_SZEROKOSC 130
#define PUNKTY_ZA_KULKI 150
int iloscZycia = 3;

char mapa[16][15];
int top[5];
bool czyWcisnietyJestS = false;
bool czyWcisnietyJestS2 = false;
bool czyWcisnietyJestS3 = false;
int posX = 680 / 2, posY = 400;		//pozycja paletki poczatkowa
double posKulkiX = posX - 5, posKulkiY = 400 - 15; //pozycja pileczki
double posKulkiX2 = 0, posKulkiY2 = 0; //pozycja pileczki 2
double posKulkiX3 = 0, posKulkiY3 = 0; //pozycja pileczki 3
double kierunekX, kierunekY, kierunekX2 = 0, kierunekX3 = 0, kierunekY2 = 0, kierunekY3 = 0;
double posNagrodyTempaX = 0, posNagrodyTempaY = 0; // pozycja nagrody tempa
double posNagrodyPaletkiX = 0, posNagrodyPaletkiY = 0; // pozycja nagrody paletki
double posNagrodyZyciaX = 0, posNagrodyZyciaY = 0; // pozycja nagrody zycia
double posNagrodySzerokosciX = 0, posNagrodySzerokosciY = 0; // pozycja nagrody zycia
double posNagrodyKulekX = 0, posNagrodyKulekY = 0; // pozycja nagrody zycia


SDL_Surface *paletka, *gora, *czerwonyBlok, *niebieskiBlok, *zielonyBlok, *rozowyBlok,
*szaryBlok, *zoltyBlok, *ball, *nagTempa, *nagPaletka, *nagSzerokosc, *nagKulek, *nagZycia, *paletka2;
SDL_Surface *screen, *charset;
SDL_Texture *scrtex;
SDL_Window *window;
SDL_Renderer *renderer;

//NAGRODY
bool czyNagrodaTempa = false, zrzuconyKlocekNagrodyTempa = false;
double czasNagrodyTempa = 20;

bool czyNagrodaPaletki = false, zrzuconyKlocekNagrodyPaletki = false;

bool zrzuconyKlocekNagrodyZycia = false;

bool czyNagrodaSzerokosci = false, zrzuconyKlocekNagrodySzerokosci = false;
double czasNagrodySzerokosci = 20;

bool czyNagrodaKulek = false, zrzuconyKlocekNagrodyKulek = false;
bool wyswietlKulke2 = false, wyswietlKulke3 = false, wyswietlKulke = true;

int przesuniecieEtapu = 1;
int iloscPunktow = 0;
int ileKulekNaEkranie = 1;

void ZaladujMape()
{
	//Laduje mape z pliku tekstowego
	//S - szary, C - czerowny, Z - zolty, N - niebieski, R - rozowy, I - zielony, '-' - brak bloczka
	//Kazdy etap to 16 linii 
	char q[2];
	FILE * plik;
	plik = fopen("mapa.txt", "r");
	for (int k = 0; k < przesuniecieEtapu; k++)
	{
		for (int i = 0; i < 16; i++)
		{
			for (int j = 0; j < 15; j++)
			{
				fscanf(plik, "%s", q);
				mapa[i][j] = q[0];
			}
		}
	}
	fclose(plik);
}

void ZaladujWyniki()
{
	//Wczytuje z pliku 5 najlepszych wynikow 
	int liczba = 0;
	FILE * plik;
	plik = fopen("highscores.txt", "r");

	for (int i = 0; i < 5; i++)
	{
		fscanf(plik, "%d", &liczba);
		top[i] = liczba;
	}
	fclose(plik);
}

void ZapiszWyniki()
{
	//Zapisuje najlepsze wyniki do pliku
	FILE * plik;
	plik = fopen("highscores.txt", "w");
	fprintf(plik, "%d %d %d %d %d", top[0], top[1], top[2], top[3], top[4]);
	fclose(plik);
}

void WstawWynikDoTablicy()
{
	//Po zako�czeniu gry, wstawia wynik do tablicy 
	int schowek, schowek2;
	if (iloscPunktow > top[0])
	{
		schowek = top[0];
		top[0] = iloscPunktow;
		schowek2 = top[1];
		top[1] = schowek;
		schowek = top[2];
		top[2] = schowek2;
		schowek2 = top[3];
		top[3] = schowek;
		top[4] = schowek2;
	}
	if (iloscPunktow < top[0] && iloscPunktow > top[1])
	{
		schowek = top[1];
		top[1] = iloscPunktow;
		schowek2 = top[2];
		top[2] = schowek;
		schowek = top[3];
		top[3] = schowek2;
		top[4] = schowek;
	}
	if (iloscPunktow < top[1] && iloscPunktow > top[2])
	{
		schowek = top[2];
		top[2] = iloscPunktow;
		schowek2 = top[3];
		top[3] = schowek;
		top[4] = schowek2;
	}
	if (iloscPunktow < top[2] && iloscPunktow > top[3])
	{
		schowek = top[3];
		top[3] = iloscPunktow;
		top[4] = schowek;
	}
	if (iloscPunktow < top[3] && iloscPunktow > top[4])
		top[4] = iloscPunktow;
}

void ZwolnijPamiec()
{
	SDL_FreeSurface(charset);
	SDL_FreeSurface(ball);
	SDL_FreeSurface(nagKulek);
	SDL_FreeSurface(nagPaletka);
	SDL_FreeSurface(nagTempa);
	SDL_FreeSurface(nagZycia);
	SDL_FreeSurface(nagSzerokosc);
	SDL_FreeSurface(paletka);
	SDL_FreeSurface(paletka2);
	SDL_FreeSurface(rozowyBlok);
	SDL_FreeSurface(niebieskiBlok);
	SDL_FreeSurface(zoltyBlok);
	SDL_FreeSurface(czerwonyBlok);
	SDL_FreeSurface(szaryBlok);
	SDL_FreeSurface(gora);
	SDL_FreeSurface(screen);
	SDL_DestroyTexture(scrtex);
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

void ZaladujBitmapy()
{
	charset = SDL_LoadBMP("./cs8x8.bmp");
	if (charset == NULL) {
		printf("SDL_LoadBMP(cs8x8.bmp) error: %s\n", SDL_GetError());
		ZwolnijPamiec();
		return;
	};
	SDL_SetColorKey(charset, true, 0x000000);

	paletka = SDL_LoadBMP("paletka.bmp");
	SDL_SetColorKey(paletka, true, 0xffffff);
	if (paletka == NULL) {
		printf("SDL_LoadBMP(paletka.bmp) error: %s\n", SDL_GetError());
		ZwolnijPamiec();
		return;
	};
	paletka2 = SDL_LoadBMP("paletka2.bmp");
	if (paletka2 == NULL) {
		printf("SDL_LoadBMP(paletka2.bmp) error: %s\n", SDL_GetError());
		ZwolnijPamiec();
		return;
	};

	gora = SDL_LoadBMP("gora.bmp");
	if (gora == NULL) {
		printf("SDL_LoadBMP(gora.bmp) error: %s\n", SDL_GetError());
		ZwolnijPamiec();
		return;
	};

	szaryBlok = SDL_LoadBMP("szary.bmp");
	if (gora == NULL) {
		printf("SDL_LoadBMP(szary.bmp) error: %s\n", SDL_GetError());
		ZwolnijPamiec();
		return;
	};

	czerwonyBlok = SDL_LoadBMP("czerwony.bmp");
	if (gora == NULL) {
		printf("SDL_LoadBMP(czerwony.bmp) error: %s\n", SDL_GetError());
		ZwolnijPamiec();
		return;
	};

	zoltyBlok = SDL_LoadBMP("zolty.bmp");
	if (gora == NULL) {
		printf("SDL_LoadBMP(zolty.bmp) error: %s\n", SDL_GetError());
		ZwolnijPamiec();
		return;
	};

	niebieskiBlok = SDL_LoadBMP("niebieski.bmp");
	if (gora == NULL) {
		printf("SDL_LoadBMP(niebieski.bmp) error: %s\n", SDL_GetError());
		ZwolnijPamiec();
		return;
	};

	rozowyBlok = SDL_LoadBMP("rozowy.bmp");
	if (gora == NULL) {
		printf("SDL_LoadBMP(rozowy.bmp) error: %s\n", SDL_GetError());
		ZwolnijPamiec();
		return;
	};

	zielonyBlok = SDL_LoadBMP("zielony.bmp");
	if (gora == NULL) {
		printf("SDL_LoadBMP(zielony.bmp) error: %s\n", SDL_GetError());
		ZwolnijPamiec();
		return;
	};

	ball = SDL_LoadBMP("kulka.bmp");
	SDL_SetColorKey(ball, true, 0xffffff);
	if (gora == NULL) {
		printf("SDL_LoadBMP(kulka.bmp) error: %s\n", SDL_GetError());
		ZwolnijPamiec();
		return;
	};
	nagKulek = SDL_LoadBMP("nagrodakulek.bmp");
	SDL_SetColorKey(ball, true, 0xffffff);
	if (gora == NULL) {
		printf("SDL_LoadBMP(nagrodakulek.bmp) error: %s\n", SDL_GetError());
		ZwolnijPamiec();
		return;
	};
	nagPaletka = SDL_LoadBMP("nagrodapaletka.bmp");
	SDL_SetColorKey(ball, true, 0xffffff);
	if (gora == NULL) {
		printf("SDL_LoadBMP(nagrodapaletka.bmp) error: %s\n", SDL_GetError());
		ZwolnijPamiec();
		return;
	};
	nagSzerokosc = SDL_LoadBMP("nagrodaszerokosc.bmp");
	SDL_SetColorKey(ball, true, 0xffffff);
	if (gora == NULL) {
		printf("SDL_LoadBMP(nagrodaszerokosc.bmp) error: %s\n", SDL_GetError());
		ZwolnijPamiec();
		return;
	};
	nagTempa = SDL_LoadBMP("nagrodatempa.bmp");
	SDL_SetColorKey(ball, true, 0xffffff);
	if (gora == NULL) {
		printf("SDL_LoadBMP(nagrodatempa.bmp) error: %s\n", SDL_GetError());
		ZwolnijPamiec();
		return;
	};
	nagZycia = SDL_LoadBMP("nagrodazycia.bmp");
	SDL_SetColorKey(ball, true, 0xffffff);
	if (gora == NULL) {
		printf("SDL_LoadBMP(nagrodazycia.bmp) error: %s\n", SDL_GetError());
		ZwolnijPamiec();
		return;
	};
}

// narysowanie napisu txt na powierzchni screen, zaczynaj�c od punktu (x, y)
// charset to bitmapa 128x128 zawieraj�ca znaki
void DrawString(SDL_Surface *screen, int x, int y, const char *text,
	SDL_Surface *charset) {
	int px, py, c;
	SDL_Rect s, d;
	s.w = 8;
	s.h = 8;
	d.w = 8;
	d.h = 8;
	while (*text) {
		c = *text & 255;
		px = (c % 16) * 8;
		py = (c / 16) * 8;
		s.x = px;
		s.y = py;
		d.x = x;
		d.y = y;
		SDL_BlitSurface(charset, &s, screen, &d);
		x += 8;
		text++;
	};
};


// narysowanie na ekranie screen powierzchni sprite w punkcie (x, y)
// (x, y) to punkt �rodka obrazka sprite na ekranie
void DrawSurface(SDL_Surface *screen, SDL_Surface *sprite, int x, int y) {
	SDL_Rect dest;
	dest.x = x - sprite->w / 2;
	dest.y = y - sprite->h / 2;
	dest.w = sprite->w;
	dest.h = sprite->h;
	SDL_BlitSurface(sprite, NULL, screen, &dest);
};


// rysowanie pojedynczego pixela
void DrawPixel(SDL_Surface *surface, int x, int y, Uint32 color) {
	int bpp = surface->format->BytesPerPixel;
	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
	*(Uint32 *)p = color;
};


// rysowanie linii o d�ugo�ci l w pionie (gdy dx = 0, dy = 1) 
// b�d� poziomie (gdy dx = 1, dy = 0)
void DrawLine(SDL_Surface *screen, int x, int y, int l, int dx, int dy, Uint32 color) {
	for (int i = 0; i < l; i++) {
		DrawPixel(screen, x, y, color);
		x += dx;
		y += dy;
	};
};


// rysowanie prostok�ta o d�ugo�ci bok�w l i k
void DrawRectangle(SDL_Surface *screen, int x, int y, int l, int k,
	Uint32 outlineColor, Uint32 fillColor) {
	int i;
	DrawLine(screen, x, y, k, 0, 1, outlineColor);
	DrawLine(screen, x + l - 1, y, k, 0, 1, outlineColor);
	DrawLine(screen, x, y, l, 1, 0, outlineColor);
	DrawLine(screen, x, y + k - 1, l, 1, 0, outlineColor);
	for (i = y + 1; i < y + k - 1; i++)
		DrawLine(screen, x + 1, i, l - 2, 1, 0, fillColor);
};

bool CzyPustaMapa()
{
	//Sprawdza czy wszystkie bloczki zosta�y usuniete z planszy
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (mapa[i][j] != '-')
				return false;
		}
	}
	return true;
}

void RysujEkran()
{
	// narysowanie brzeg�w i blokow
	for (int i = 0; i < 32; i++)
	{
		DrawSurface(screen, gora, (i + 1) * 40 - 20, 15 - 8);
		DrawSurface(screen, gora, 20, (i)* 15 + 8);
		DrawSurface(screen, gora, 660, (i)* 15 + 8);
	}

	for (int y = 0; y < 16; y++)
	{
		for (int x = 0; x < 15; x++)
		{
			if (mapa[y][x] == 'S')  //rysowanie szarego bloku
			{
				DrawSurface(screen, szaryBlok, (x + 1) * 40 + 20, (y + 1) * 15 - 8);
			}
			if (mapa[y][x] == 'C')  //rysowanie czerwonego bloku
			{
				DrawSurface(screen, czerwonyBlok, (x + 1) * 40 + 20, (y + 1) * 15 - 8);
			}
			if (mapa[y][x] == 'Z')  //rysowanie zoltego bloku
			{
				DrawSurface(screen, zoltyBlok, (x + 1) * 40 + 20, (y + 1) * 15 - 8);
			}
			if (mapa[y][x] == 'N')  //rysowanie niebieskiego bloku
			{
				DrawSurface(screen, niebieskiBlok, (x + 1) * 40 + 20, (y + 1) * 15 - 8);
			}
			if (mapa[y][x] == 'R')  //rysowanie rozowego bloku
			{
				DrawSurface(screen, rozowyBlok, (x + 1) * 40 + 20, (y + 1) * 15 - 8);
			}
			if (mapa[y][x] == 'I')  //rysowanie zielonego bloku
			{
				DrawSurface(screen, zielonyBlok, (x + 1) * 40 + 20, (y + 1) * 15 - 8);
			}
		}
	}

}

void PrzydzielPunkty(char znak)
{
	//Przydzielenie punktow za zbidcie danego bloczka
	if (znak == 'S')
		iloscPunktow += PUNKTY_ZA_SZARE;
	if (znak == 'C')
		iloscPunktow += PUNKTY_ZA_CZERWONE;
	if (znak == 'Z')
		iloscPunktow += PUNKTY_ZA_ZOLTE;
	if (znak == 'N')
		iloscPunktow += PUNKTY_ZA_NIEBIESKIE;
	if (znak == 'R')
		iloscPunktow += PUNKTY_ZA_ROZOWE;
	if (znak == 'I')
		iloscPunktow += PUNKTY_ZA_ZIELONE;
}

void WykryjSzanse(int szansa)
{

	if (szansa == 2 && zrzuconyKlocekNagrodyTempa == false) //mozliwosc nagrody tempa
	{
		zrzuconyKlocekNagrodyTempa = true;
		posNagrodyTempaX = posKulkiX;
		posNagrodyTempaY = posKulkiY;
	}
	if (szansa == 3 && zrzuconyKlocekNagrodyPaletki == false)	//mozliwosc nagrody przylepienia paletki
	{
		zrzuconyKlocekNagrodyPaletki = true;
		posNagrodyPaletkiX = posKulkiX;
		posNagrodyPaletkiY = posKulkiY;
	}
	if (szansa == 4 && zrzuconyKlocekNagrodyZycia == false)	//mozliwosc nagrody zycia paletki
	{
		zrzuconyKlocekNagrodyZycia = true;
		posNagrodyZyciaX = posKulkiX;
		posNagrodyZyciaY = posKulkiY;
	}
	if (szansa == 5 && zrzuconyKlocekNagrodySzerokosci == false)	//mozliwosc nagrody szerokosci paletki
	{
		zrzuconyKlocekNagrodySzerokosci = true;
		posNagrodySzerokosciX = posKulkiX;
		posNagrodySzerokosciY = posKulkiY;
	}
	if (szansa == 6 && zrzuconyKlocekNagrodyKulek == false)	//mozliwosc nagrody szerokosci paletki
	{
		zrzuconyKlocekNagrodyKulek = true;
		posNagrodyKulekX = posKulkiX;
		posNagrodyKulekY = posKulkiY;
	}
}

void CzyKolizja(int x, int y)
{
	//Funkcja sprawdza czy kulka zderzy�a sie z jakims bloczkiem
	int szansa = rand() % PRAWDOPODOBIENSTWO;
	if (round(posKulkiX) == ((x + 1) * 40 + 20 + 25) || round(posKulkiX) == ((x + 1) * 40 + 20 - 25))
	{
		for (int i = 0; i < 20; i++)
		{
			if (round(posKulkiY) + i == (y + 1) * 15 - 8 + 10)
			{
				kierunekX = -kierunekX;
				PrzydzielPunkty(mapa[y][x]);
				mapa[y][x] = '-';
				WykryjSzanse(szansa);
				break;
			}
		}
	}

	if (round(posKulkiY) == (y + 1) * 15 - 8 + 15 || round(posKulkiY) == (y + 1) * 15 - 8 - 15)
	{
		for (int i = 0; i < 40; i++)
		{
			if (round(posKulkiX) + i == ((x + 1) * 40 + 20 + 10))
			{
				kierunekY = -kierunekY;
				posKulkiY += kierunekY;
				PrzydzielPunkty(mapa[y][x]);
				mapa[y][x] = '-';
				WykryjSzanse(szansa);
				break;
			}
		}
	}
}

void CzyKolizja2(int x, int y)
{
	//Funkcja sprawdza czy kulka z nagrody zderzy�a sie z jakims bloczkiem
	int szansa = rand() % 6;
	if (round(posKulkiX2) == ((x + 1) * 40 + 20 + 25) || round(posKulkiX2) == ((x + 1) * 40 + 20 - 25))
	{
		for (int i = 0; i < 20; i++)
		{
			if (round(posKulkiY2) + i == (y + 1) * 15 - 8 + 10)
			{
				kierunekX2 = -kierunekX2;
				PrzydzielPunkty(mapa[y][x]);
				mapa[y][x] = '-';
				WykryjSzanse(szansa);
				break;
			}
		}
	}

	if (round(posKulkiY2) == (y + 1) * 15 - 8 + 15 || round(posKulkiY2) == (y + 1) * 15 - 8 - 15)
	{
		for (int i = 0; i < 40; i++)
		{
			if (round(posKulkiX2) + i == ((x + 1) * 40 + 20 + 10))
			{
				kierunekY2 = -kierunekY2;
				mapa[y][x] = '-';
				iloscPunktow += 150;
				WykryjSzanse(szansa);
				break;
			}
		}
	}
}

void CzyKolizja3(int x, int y)
{
	//Funkcja sprawdza czy kulka z nagrody zderzy�a sie z jakims bloczkiem
	int szansa = rand() % 6;
	if (round(posKulkiX3) == ((x + 1) * 40 + 20 + 25) || round(posKulkiX3) == ((x + 1) * 40 + 20 - 25))
	{
		for (int i = 0; i < 20; i++)
		{
			if (round(posKulkiY3) + i == (y + 1) * 15 - 8 + 10)
			{
				kierunekX3 = -kierunekX3;
				PrzydzielPunkty(mapa[y][x]);
				mapa[y][x] = '-';
				WykryjSzanse(szansa);
				break;
			}
		}
	}

	if (round(posKulkiY3) == (y + 1) * 15 - 8 + 15 || round(posKulkiY3) == (y + 1) * 15 - 8 - 15)
	{
		for (int i = 0; i < 40; i++)
		{
			if (round(posKulkiX3) + i == ((x + 1) * 40 + 20 + 10))
			{
				kierunekY3 = -kierunekY3;
				PrzydzielPunkty(mapa[y][x]);
				mapa[y][x] = '-';
				WykryjSzanse(szansa);
				break;
			}
		}
	}
}

void WykryjKolizje()
{
	// przekazuje pozycje kulki i sprawdza czy nie wykryto kolizji z jakims bloczkiem
	for (int y = 0; y < 16; y++)
	{
		for (int x = 0; x < 17; x++)
		{
			if (mapa[y][x] == 'S')
			{
				CzyKolizja(x, y);
				CzyKolizja2(x, y);
				CzyKolizja3(x, y);
			}

			if (mapa[y][x] == 'C')
			{
				CzyKolizja(x, y);
				CzyKolizja2(x, y);
				CzyKolizja3(x, y);
			}

			if (mapa[y][x] == 'Z')
			{
				CzyKolizja(x, y);
				CzyKolizja2(x, y);
				CzyKolizja3(x, y);
			}

			if (mapa[y][x] == 'N')
			{
				CzyKolizja(x, y);
				CzyKolizja2(x, y);
				CzyKolizja3(x, y);
			}

			if (mapa[y][x] == 'R')
			{
				CzyKolizja(x, y);
				CzyKolizja2(x, y);
				CzyKolizja3(x, y);
			}

			if (mapa[y][x] == 'I')
			{
				CzyKolizja(x, y);
				CzyKolizja2(x, y);
				CzyKolizja3(x, y);
			}
		}
	}
}

void WykryjKolizjeNagrod()
{

	//Sprawdza kolizje nagord z paletka
	int dlugosc = 60, xDodatkowe = 0;

	if (czyNagrodaSzerokosci == true)
	{
		dlugosc = 120;
		xDodatkowe = 30;
	}
	else
	{
		dlugosc = 60;
		xDodatkowe = 0;
	}

	if (round(posNagrodyTempaY) == 385)	// KOLIZJA PALETKI Z NAGRODA TEMPA
	{
		for (int i = 0; i < dlugosc; i++)
		{
			if (round(posNagrodyTempaX) + i == (posX + 25 + xDodatkowe))
			{
				czyNagrodaTempa = true;
				kierunekX *= 0.5;
				kierunekY *= 0.5;
				kierunekX2 *= 0.5;
				kierunekY2 *= 0.5;
				kierunekX3 *= 0.5;
				kierunekY3 *= 0.5;
				zrzuconyKlocekNagrodyTempa = false;
				iloscPunktow += PUNKTY_ZA_TEMPO;
				posNagrodyTempaY = 500;
				break;
			}
		}
	}

	if (round(posNagrodyPaletkiY) == 385)	// KOLIZJA PALETKI Z NAGRODA PRZYLEPIENIA SIE
	{
		for (int i = 0; i < dlugosc; i++)
		{
			if (round(posNagrodyPaletkiX) + i == (posX + 25 + xDodatkowe))
			{
				czyNagrodaPaletki = true;
				zrzuconyKlocekNagrodyPaletki = false;
				iloscPunktow += PUNKTY_ZA_PALETKE;
				posNagrodyPaletkiY = 500;
				break;
			}
		}
	}

	if (round(posNagrodyZyciaY) == 385)	// KOLIZJA PALETKI Z NAGRODA ZYCIA
	{
		for (int i = 0; i < dlugosc; i++)
		{
			if (round(posNagrodyZyciaX) + i == (posX + 25 + xDodatkowe))
			{
				zrzuconyKlocekNagrodyZycia = false;
				iloscPunktow += PUNKTY_ZA_ZYCIE;
				posNagrodyZyciaY = 500;
				iloscZycia++;
				break;
			}
		}
	}

	if (round(posNagrodySzerokosciY) == 385)	// KOLIZJA PALETKI Z NAGRODA TEMPA
	{
		for (int i = 0; i < dlugosc; i++)
		{
			if (round(posNagrodySzerokosciX) + i == (posX + 25 + xDodatkowe))
			{
				czyNagrodaSzerokosci = true;
				zrzuconyKlocekNagrodySzerokosci = false;
				iloscPunktow += PUNKTY_ZA_SZEROKOSC;
				posNagrodySzerokosciY = 500;
				if (posX > 130)
					posX -= 30;
				else if (posX < 550)
					posX += 30;

				break;
			}
		}
	}

	if (round(posNagrodyKulekY) == 385)	// KOLIZJA PALETKI Z NAGRODA TEMPA
	{
		for (int i = 0; i < dlugosc; i++)
		{
			if (round(posNagrodyKulekX) + i == (posX + 25 + xDodatkowe))
			{
				posKulkiX2 = posKulkiX3 = posKulkiX;
				posKulkiY2 = posKulkiY3 = posKulkiY;
				kierunekX2 = -kierunekX;
				kierunekY2 = kierunekY;
				kierunekY3 = -kierunekY;
				kierunekX3 = kierunekX;
				ileKulekNaEkranie = 3;
				czyNagrodaKulek = true;
				zrzuconyKlocekNagrodyKulek = false;
				iloscPunktow += PUNKTY_ZA_KULKI;
				posNagrodyKulekY = 500;
				break;
			}
		}
	}
}

void WykryjKolizjeZPaletka()
{
	//wykrywa kolzje kulek z paletka
	int xDodatkowe = 0;
	if (czyNagrodaSzerokosci == true)
		xDodatkowe = 30;
	else
		xDodatkowe = 0;

	if (round(posKulkiY) == 385)
	{
		for (int i = 0; i < 30 + xDodatkowe; i++)
		{
			if (round(posKulkiX) + i == (posX + 25 + xDodatkowe) && czyWcisnietyJestS == true)
			{
				if (czyWcisnietyJestS == true && czyNagrodaPaletki == true)
					czyWcisnietyJestS = false;
				posKulkiY--;
				kierunekY = -kierunekY;
				if (kierunekX != 0)
				{
					kierunekX += 0.5;
					break;
				}
				else
				{
					kierunekX += 0.2;
					break;
				}
				break;
			}

		}

		for (int i = 30 + xDodatkowe; i < 60 + (xDodatkowe * 2); i++)
		{
			if (round(posKulkiX) + i == (posX + 25 + xDodatkowe) && czyWcisnietyJestS == true)
			{
				if (czyWcisnietyJestS == true && czyNagrodaPaletki == true)
					czyWcisnietyJestS = false;
				posKulkiY--;
				kierunekY = -kierunekY;
				if (kierunekX != 0)
				{
					kierunekX -= 0.5;
					break;
				}
				else
				{
					kierunekX -= 0.2;
					break;
				}

				break;
			}
		}
	}

	if (round(posKulkiY2) == 385)
	{
		for (int i = 0; i < 30 + xDodatkowe; i++)
		{
			if (round(posKulkiX2) + i == (posX + 25 + xDodatkowe) && czyWcisnietyJestS2 == true)
			{
				if (czyWcisnietyJestS2 == true && czyNagrodaPaletki == true)
					czyWcisnietyJestS2 = false;
				posKulkiY2--;
				kierunekY2 = -kierunekY2;
				if (kierunekX2 != 0)
				{
					kierunekX2 += 0.5;
					break;
				}
				else
				{
					kierunekX2 += 0.2;
					break;
				}
				break;
			}

		}

		for (int i = 30 + xDodatkowe; i < 60 + (xDodatkowe * 2); i++)
		{
			if (round(posKulkiX2) + i == (posX + 25 + xDodatkowe) && czyWcisnietyJestS2 == true)
			{
				if (czyWcisnietyJestS2 == true && czyNagrodaPaletki == true)
					czyWcisnietyJestS2 = false;
				posKulkiY2--;
				kierunekY2 = -kierunekY2;
				if (kierunekX2 != 0)
				{
					kierunekX2 -= 0.5;
					break;
				}
				else
				{
					kierunekX2 -= 0.2;
					break;
				}
				break;
			}
		}
	}

	if (round(posKulkiY3) == 385)
	{
		for (int i = 0; i < 30 + xDodatkowe; i++)
		{
			if (round(posKulkiX3) + i == (posX + 25 + xDodatkowe) && czyWcisnietyJestS3 == true)
			{
				if (czyWcisnietyJestS3 == true && czyNagrodaPaletki == true)
					czyWcisnietyJestS3 = false;
				posKulkiY3--;
				kierunekY3 = -kierunekY3;
				if (kierunekX3 != 0)
				{
					kierunekX3 += 0.5;
					break;
				}
				else
				{
					kierunekX3 += 0.2;
					break;
				}
				break;
			}

		}

		for (int i = 30 + xDodatkowe; i < 60 + (xDodatkowe * 2); i++)
		{
			if (round(posKulkiX3) + i == (posX + 25 + xDodatkowe) && czyWcisnietyJestS3 == true)
			{
				if (czyWcisnietyJestS3 == true && czyNagrodaPaletki == true)
					czyWcisnietyJestS3 = false;
				posKulkiY3--;
				kierunekY3 = -kierunekY3;
				if (kierunekX3 != 0)
				{
					kierunekX3 -= 0.5;
					break;
				}
				else
				{
					kierunekX3 -= 0.2;
					break;
				}
				break;
			}
		}
	}
}

void ObslugaKolizji()
{
	if (ileKulekNaEkranie == 0)		// Jezeli nie ma zadnej kulki na ekranie, jedno zycie mniej
	{
		ileKulekNaEkranie = 1;
		czyNagrodaPaletki = false;
		wyswietlKulke = true;
		posX = 680 / 2, posY = 400;
		posKulkiX = posX - 5, posKulkiY = 400 - 15;
		czyWcisnietyJestS = false;
		czyWcisnietyJestS2 = true;
		czyWcisnietyJestS3 = true;
		kierunekY = -1 * PREDKOSC_PILECZKI;
		kierunekX = (rand() % 2 + -2) * PREDKOSC_PILECZKI;
		iloscZycia--;
	}



	//wykrecie kolizji ze sciana albo wypadniecie kulki
	if (czyWcisnietyJestS == true)
	{
		posKulkiY += (kierunekY * 0.25);
		posKulkiX += (kierunekX * 0.25);


		// ODBIJANIE SIE OD SCIAN
		if (posKulkiX < 635)
		{
			kierunekX = -kierunekX;
		}

		if (posKulkiX > 45)
		{
			kierunekX = -kierunekX;
		}

		if (posKulkiY < 25)
		{
			kierunekY = -kierunekY;
		}

		WykryjKolizjeZPaletka();

		WykryjKolizjeNagrod();
		WykryjKolizje();

	}

	if (czyWcisnietyJestS2 == true)
	{
		posKulkiY2 += (kierunekY2 * 0.25);
		posKulkiX2 += (kierunekX2 * 0.25);


		// ODBIJANIE SIE OD SCIAN
		if (posKulkiX2 < 635)
		{
			kierunekX2 = -kierunekX2;
		}

		if (posKulkiX2 > 45)
		{
			kierunekX2 = -kierunekX2;
		}

		if (posKulkiY2 < 25)
		{
			kierunekY2 = -kierunekY2;
		}

		WykryjKolizjeZPaletka();


		WykryjKolizjeNagrod();
		WykryjKolizje();

	}

	if (czyWcisnietyJestS3 == true)
	{
		posKulkiY3 += (kierunekY3 * 0.25);
		posKulkiX3 += (kierunekX3 * 0.25);


		// ODBIJANIE SIE OD SCIAN
		if (posKulkiX3 < 635)
		{
			kierunekX3 = -kierunekX3;
		}

		if (posKulkiX3 > 45)
		{
			kierunekX3 = -kierunekX3;
		}

		if (posKulkiY3 < 25)
		{
			kierunekY3 = -kierunekY3;
		}

		WykryjKolizjeZPaletka();

		WykryjKolizjeNagrod();
		WykryjKolizje();

	}

	//sprawdza czy nagrody nie wyszly poza ekran;
	if (posNagrodyTempaY > 460)
		zrzuconyKlocekNagrodyTempa = false;

	if (posNagrodyPaletkiY > 460)
		zrzuconyKlocekNagrodyPaletki = false;

	if (posNagrodyZyciaY > 460)
		zrzuconyKlocekNagrodyZycia = false;

	if (posNagrodySzerokosciY > 460)
		zrzuconyKlocekNagrodySzerokosci = false;

	if (posNagrodyKulekY > 460)
		zrzuconyKlocekNagrodyKulek = false;

	if (posKulkiY3 > 460)
	{
		wyswietlKulke3 = false;
		posKulkiX3 = 0;
		posKulkiY3 = 0;
		ileKulekNaEkranie--;
		czyWcisnietyJestS3 = false;
	}

	if (posKulkiY2 > 460)
	{
		wyswietlKulke2 = false;
		posKulkiX2 = 0;
		posKulkiY2 = 0;
		ileKulekNaEkranie--;
		czyWcisnietyJestS2 = false;
	}

	if (posKulkiY > 460)
	{
		wyswietlKulke = false;
		posKulkiX = 0;
		posKulkiY = 0;
		ileKulekNaEkranie--;
		czyWcisnietyJestS = false;
	}

}

void PrzyspieszKulke(double worldTime)
{
	int kierunek;
	//przyspieszanie kulki wraz z czasem
	if (worldTime < 5)
	{
		if (kierunekY < 0)
			kierunekY = -1.1;
		else
			kierunekY = 1.1;
	}
	else if (worldTime < 10 && worldTime > 5)
	{
		if (kierunekY < 0)
			kierunekY = -1.3;
		else
			kierunekY = 1.3;
	}
	else if (worldTime < 15 && worldTime > 10)
	{
		if (kierunekY < 0)
			kierunekY = -1.5;
		else
			kierunekY = 1.5;
	}
	else if (worldTime < 20 && worldTime > 15)
	{
		if (kierunekY < 0)
			kierunekY = -1.7;
		else
			kierunekY = 1.7;
	}
	else if (worldTime < 25 && worldTime > 20)
	{
		if (kierunekY < 0)
			kierunekY = -1.9;
		else
			kierunekY = 1.9;
	}
	else if (worldTime < 30 && worldTime > 25)
	{
		if (kierunekY < 0)
			kierunekY = -2.1;
		else
			kierunekY = 2.1;
	}

}

// main
//#ifdef __cplusplus
//extern "C"
//#endif
int main(int argc, char **argv) {


	int t1, t2, quit, rc, komunikatQuit = 0, xDodatkowe = 0;
	double delta, worldTime;
	SDL_Event event;
	ZaladujMape();
	ZaladujWyniki();

	if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO) != 0) {
		printf("SDL_Init error: %s\n", SDL_GetError());
		return 1;
	}

	// tryb pe�noekranowy
	//	rc = SDL_CreateWindowAndRenderer(0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP,
	//	                                 &window, &renderer);
	rc = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0,
		&window, &renderer);
	if (rc != 0) {
		SDL_Quit();
		printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
		return 1;
	};

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	SDL_SetWindowTitle(window, "Arkanoid - Patryk Bejgrowicz 149385");


	screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32,
		0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

	scrtex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		SCREEN_WIDTH, SCREEN_HEIGHT);


	// wy��czenie widoczno�ci kursora myszy
	SDL_ShowCursor(SDL_DISABLE);

	ZaladujBitmapy();

	char text[128];
	int czarny = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
	int zielony = SDL_MapRGB(screen->format, 0x00, 0xFF, 0x00);
	int czerwony = SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00);
	int niebieski = SDL_MapRGB(screen->format, 0x11, 0x11, 0xCC);
	int kolorTla = SDL_MapRGB(screen->format, 0x6e, 0xa1, 0xee);

	t1 = SDL_GetTicks();

	quit = 0;
	worldTime = 0;

	srand(time(NULL));
	kierunekX = 0.1 * PREDKOSC_PILECZKI;
	kierunekY = -1 * PREDKOSC_PILECZKI;


	while (!quit) {

		t2 = SDL_GetTicks();

		// w tym momencie t2-t1 to czas w milisekundach,
		// jaki uplyna� od ostatniego narysowania ekranu
		// delta to ten sam czas w sekundach
		delta = (t2 - t1) * 0.001;
		t1 = t2;

		worldTime += delta;


		SDL_FillRect(screen, NULL, kolorTla);

		// RYSOWANIE PALETKI I EKRANU
		RysujEkran();
		if (czyNagrodaSzerokosci == false)
			DrawSurface(screen, paletka, posX, posY);
		else
			DrawSurface(screen, paletka2, posX, posY);

		if (wyswietlKulke == true)
			DrawSurface(screen, ball, posKulkiX + 5, posKulkiY);


		// NAGRODA TEMPA
		if (czyNagrodaTempa == true)
		{
			czasNagrodyTempa -= delta;
			if (czasNagrodyTempa <= 0)
			{
				worldTime = 0;
				czyNagrodaTempa = false;
			}
		}
		else
			czasNagrodyTempa = 20;

		if (zrzuconyKlocekNagrodyTempa == true)
		{
			DrawSurface(screen, nagTempa, posNagrodyTempaX, posNagrodyTempaY);
			posNagrodyTempaY += 0.5;
		}

		//Zrzucenie nagrody paletki
		if (zrzuconyKlocekNagrodyPaletki == true)
		{
			DrawSurface(screen, nagPaletka, posNagrodyPaletkiX, posNagrodyPaletkiY);
			posNagrodyPaletkiY += 0.5;
		}


		//Zrzucenie nagrody zycia
		if (zrzuconyKlocekNagrodyZycia == true)
		{
			DrawSurface(screen, nagZycia, posNagrodyZyciaX, posNagrodyZyciaY);
			posNagrodyZyciaY += 0.5;
		}

		//Zrzucenie nagrody szerokosci
		if (czyNagrodaSzerokosci == true)
		{
			czasNagrodySzerokosci -= delta;
			if (czasNagrodySzerokosci <= 0)
				czyNagrodaSzerokosci = false;
		}
		else
			czasNagrodySzerokosci = 20;

		if (zrzuconyKlocekNagrodySzerokosci == true)
		{
			DrawSurface(screen, nagSzerokosc, posNagrodySzerokosciX, posNagrodySzerokosciY);
			posNagrodySzerokosciY += 0.5;
		}

		//Zrzucenie nagrody kulek
		if (czyNagrodaKulek == true)
		{
			wyswietlKulke2 = true;
			wyswietlKulke3 = true;
		}

		if (wyswietlKulke2 == true)
			DrawSurface(screen, ball, posKulkiX2, posKulkiY2);

		if (wyswietlKulke3 == true)
			DrawSurface(screen, ball, posKulkiX3, posKulkiY3);



		if (zrzuconyKlocekNagrodyKulek == true)
		{
			DrawSurface(screen, nagKulek, posNagrodyKulekX, posNagrodyKulekY);
			posNagrodyKulekY += 0.5;
		}


#pragma region informacje
		DrawRectangle(screen, 0, 0, 680, 5, czarny, czarny);
		DrawRectangle(screen, 0, 0, 10, 480, czarny, czarny);
		DrawRectangle(screen, 670, 0, 110, SCREEN_HEIGHT, czerwony, niebieski);
		sprintf(text, "Punkty:");
		DrawString(screen, 680, 10, text, charset);
		sprintf(text, "%d", iloscPunktow);
		DrawString(screen, 680, 20, text, charset);
		sprintf(text, "Ile zyc:");
		DrawString(screen, 680, 50, text, charset);
		sprintf(text, "%d", iloscZycia);
		DrawString(screen, 680, 60, text, charset);
		sprintf(text, "Sterowanie:");
		DrawString(screen, 680, 200, text, charset);
		sprintf(text, "Esc  wyjscie");
		DrawString(screen, 680, 220, text, charset);
		sprintf(text, "<-   w lewo");
		DrawString(screen, 680, 230, text, charset);
		sprintf(text, "->   w prawo");
		DrawString(screen, 680, 240, text, charset);
		sprintf(text, "s    start");
		DrawString(screen, 680, 250, text, charset);
		sprintf(text, "Highscores:");
		DrawString(screen, 680, 340, text, charset);
		sprintf(text, "1) %d", top[0]);
		DrawString(screen, 680, 350, text, charset);
		sprintf(text, "2) %d", top[1]);
		DrawString(screen, 680, 360, text, charset);
		sprintf(text, "3) %d", top[2]);
		DrawString(screen, 680, 370, text, charset);
		sprintf(text, "4) %d", top[3]);
		DrawString(screen, 680, 380, text, charset);
		sprintf(text, "5) %d", top[4]);
		DrawString(screen, 680, 390, text, charset);
#pragma endregion 
		if (CzyPustaMapa() == true)
		{
			przesuniecieEtapu++;
			ZaladujMape();
			if (CzyPustaMapa() == true)
				iloscZycia = 0;
		}

		if (iloscZycia == 0)
		{
			DrawRectangle(screen, 240, 210, 260, 50, czarny, niebieski);
			sprintf(text, "Koniec gry!");
			DrawString(screen, 250, 220, text, charset);
			sprintf(text, "Zakonczyc czy zresetowac?: z/r");
			DrawString(screen, 250, 240, text, charset);
			while (SDL_PollEvent(&event)) {
				switch (event.type) {
				case SDL_KEYDOWN:
					if (event.key.keysym.sym == 'z' || event.key.keysym.sym == SDLK_ESCAPE)
					{
						komunikatQuit = 1;
						quit = 1;
					}
					if (event.key.keysym.sym == 'r')
					{
						przesuniecieEtapu = 1;
						iloscZycia = 3;
						iloscPunktow = 0;
						ZaladujMape();
						posX = 680 / 2, posY = 400;
						posKulkiX = posX - 5, posKulkiY = 400 - 15;
						czyWcisnietyJestS = false;
						kierunekX = (rand() % 1 + -1) * PREDKOSC_PILECZKI;
					}
					break;
				};
			};
		}

		SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
		//		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, scrtex, NULL, NULL);
		SDL_RenderPresent(renderer);
		PrzyspieszKulke(worldTime);
		if (ileKulekNaEkranie == 0) // zerowanie czasu dla przyspieszania kulki
			worldTime = 0;
		ObslugaKolizji(); // g�owna funkcja ktora obsluguje kolizji kulek, nagrod itd
		if (czyNagrodaSzerokosci == true)
			xDodatkowe = 30;
		else
			xDodatkowe = 0;

		// obs�uga zdarze� (o ile jakie� zasz�y)
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE) quit = 1;
				if (event.key.keysym.sym == 's')
				{
					czyWcisnietyJestS = true;
					czyWcisnietyJestS2 = true;
					czyWcisnietyJestS3 = true;
				}
				if (event.key.keysym.sym == SDLK_LEFT)
				{
					if (posX > 70 + xDodatkowe)
					{
						posX -= 5;
						if (czyWcisnietyJestS == false)
						{
							posKulkiX -= 5;
						}
						if (czyWcisnietyJestS2 == false)
						{
							posKulkiX2 -= 5;
						}
						if (czyWcisnietyJestS3 == false)
						{
							posKulkiX3 -= 5;
						}
					}
					else
						posX = 70 + xDodatkowe;
				}
				if (event.key.keysym.sym == SDLK_RIGHT)
				{
					if (posX < 610 - xDodatkowe)
					{
						posX += 5;
						if (czyWcisnietyJestS == false)
						{
							posKulkiX += 5;
						}
						if (czyWcisnietyJestS2 == false)
						{
							posKulkiX2 += 5;
						}
						if (czyWcisnietyJestS3 == false)
						{
							posKulkiX3 += 5;
						}
					}
					else
						posX = 610 - xDodatkowe;
				}
				/*	if (event.key.keysym.sym == SDLK_UP)
				{
				przesuniecieEtapu++;
				ZaladujMape();
				}*/
				break;
			case SDL_QUIT:
				quit = 1;
				break;
			};
		};

	};

	ZwolnijPamiec();
	WstawWynikDoTablicy();
	ZapiszWyniki();
	SDL_Quit();
	return 0;
};
