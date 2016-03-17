# -*- coding: utf-8 -*-
import time
import pygame
from pygame.locals import *
from sys import exit
from Organizm import *
from Zwierze import *
from Trawa import * 
from Jagoda import *
from Mlecz import *
from Wilk import *
from Owca import *
from Zolw import *
from Antylopa import *
from Lis import *
from Guarana import *
from Czlowiek import *
import sys
import os
import linecache

rozmiar = 22
screen_size = (rozmiar*30,rozmiar*30)

class WirtualnySwiat(object):
    pygame.init()
    flag = DOUBLEBUF
	# tworzenie grafiki
    surface = pygame.display.set_mode(screen_size,flag)
    none = pygame.image.load('none.png')
    def __init__(self):
        self.organizmy = [[None]*rozmiar for x in range(rozmiar)]
        self.nowy = [None]*5000
        self.tab = []
        czlowiek = Czlowiek(0, 0, self)
        self.tab.append(czlowiek)
        self.organizmy[czlowiek.X][czlowiek.Y] = czlowiek
        self.kierunekCzlowieka = -1
        self.czyAktywowanoUmiejetnosc = False

    def zliczNowy(self):
        t=0
        liczba_n = 0
        while self.nowy[t] != None:
            liczba_n = liczba_n + 1
            t = t + 1
        return liczba_n

    def start(self):
        self.rysujSwiat()
		
    def wyczyscUmarlych(self):
        j = 0
        for k in self.tab:
            if (self.tab[j].usuniety == 1): #usuwanie starych organizmow
                self.organizmy[self.tab[j].X][self.tab[j].Y] = None
                self.tab[j] = None
                self.tab.remove(self.tab[j])
            j = j + 1
		
    def wykonajTure(self):
        os.system('cls') #czyszczenie ekranu
        j=0
		#wykonanie ruchu obcenych organizmow
        for k in self.tab:
            self.tab[j].ruch()
            self.wyczyscUmarlych()
            j = j + 1
        t=0
        liczba_n = 0
		#dodanie nowych organizmow do tablicy
        while self.nowy[t] != None:
            print 'Narodzil sie nowy ' + self.nowy[t].nazwa
            self.tab.append(self.nowy[t])
            liczba_n = liczba_n + 1
            t = t + 1
        t=0
		#zerowanie tablicy nowych
        while t < liczba_n:
            self.nowy[t] = None
            t=t+1
		
    


    def rysujSwiat(self):
        for y in range(rozmiar):
            for x in range(rozmiar):
                if(self.organizmy[x][y] == None):
                    self.surface.blit(self.none, (x*30,y*30))
                else:
                    self.surface.blit(self.organizmy[x][y].foto, (x*30, y*30))
        pygame.display.flip()

    def zapisz(self):
        plik = open('mapa.txt', 'w')
        for y in range(rozmiar):
            for x in range(rozmiar):
                if(self.organizmy[x][y] == None):
                    plik.write(".")
                else:
                    plik.write(self.organizmy[x][y].znak)
            plik.write("\n")
        plik.close()

    def wczytaj(self):
        try:
            del self.tab[:]
            x=0
            y=0
            for x in range(rozmiar):
                for y in range(rozmiar):
                    self.organizmy[x][y] = None
            i=0
            while i<rozmiar:
                wiersz = linecache.getline('mapa.txt', i)
                j=0
                for t in wiersz:
                    if(t == '.'):
                        self.surface.blit(self.none, (j*30, i*30))
                    elif(t == 'W'):
                        wilk = Wilk(j, i, self)
                        self.tab.append(wilk)
                        self.organizmy[wilk.X][wilk.Y] = wilk
                        self.surface.blit(self.organizmy[wilk.X][wilk.Y].foto, (j*30, i*30))
                    elif(t == 'O'):
                        owca = Owca(j, i, self)
                        self.tab.append(owca)
                        self.organizmy[owca.X][owca.Y] = owca
                        self.surface.blit(self.organizmy[owca.X][owca.Y].foto, (j*30, i*30))
                    elif(t == 'Z'):
                        zolw = Zolw(j, i, self)
                        self.tab.append(zolw)
                        self.organizmy[zolw.X][zolw.Y] = pies
                        self.surface.blit(self.organizmy[zolw.X][zolw.Y].foto, (j*30, i*30))
                    elif(t == 'L'):
                        lis = Lis(j, i, self)
                        self.tab.append(lis)
                        self.organizmy[lis.X][lis.Y] = lis
                        self.surface.blit(self.organizmy[lis.X][lis.Y].foto, (j*30, i*30))
                    elif(t == 'A'):
                        antylopa = Antylopa(j, i, self)
                        self.tab.append(antylopa)
                        self.organizmy[antylopa.X][antylopa.Y] = antylopa
                        self.surface.blit(self.organizmy[antylopa.X][antylopa.Y].foto, (j*30, i*30))
                    elif(t == 'T'):
                        trawa = Trawa(j, i, self)
                        self.tab.append(trawa)
                        self.organizmy[trawa.X][trawa.Y] = trawa
                        self.surface.blit(self.organizmy[trawa.X][trawa.Y].foto, (j*30, i*30))
                    elif(t == 'M'):
                        mlecz = Mlecz(j, i, self)
                        self.tab.append(mlecz)
                        self.organizmy[mlecz.X][mlecz.Y] = mlecz
                        self.surface.blit(self.organizmy[mlecz.X][mlecz.Y].foto, (j*30, i*30))
                    elif(t == 'J'):
                        jagoda = Jagoda(j, i, self)
                        self.tab.append(jagoda)
                        self.organizmy[jagoda.X][jagoda.Y] = jagoda
                        self.surface.blit(self.organizmy[jagoda.X][jagoda.Y].foto, (j*30, i*30))
                    elif(t == 'G'):
                        guarana = Guarana(j, i, self)
                        self.tab.append(guarana)
                        self.organizmy[guarana.X][guarana.Y] = guarana
                        self.surface.blit(self.organizmy[guarana.X][guarana.Y].foto, (j*30, i*30))
                    elif(t == '@'):
                        czlowiek = Czlowiek(j, i, self)
                        self.tab.append(czlowiek)
                        self.organizmy[czlowiek.X][czlowiek.Y] = czlowiek
                        self.surface.blit(self.organizmy[czlowiek.X][czlowiek.Y].foto, (j*30, i*30))
                    j=j+1
                i=i+1
        except IOError:
            print "Error: File does not appear to exist."

        pygame.display.flip()