# -*- coding: utf-8 -*-
import pygame
from pygame.locals import *
from sys import exit 
from WirtualnySwiat import *
from Organizm import *
from Zwierze import *
import os
screen_size = (650,650)
class Main(object):
    pygame.init()
    flag = DOUBLEBUF
    surface = pygame.display.set_mode(screen_size,flag)
    graj = 1 
    Swiat = WirtualnySwiat() #inicjaliacja swiata obiekt WirtualnySwiat 
    pygame.mouse.set_visible(True)
    Swiat.start() 
    i=0
    #w - wilk
    #o - owca
    #l - lis
    #z - zolw
    #t - trawa
    #m - mlecz
    #j - jagoda
	#g - guarana
    #a - antylopa
    while graj == 1:
            for event in pygame.event.get():
                if event.type==QUIT or (event.type==KEYDOWN and event.key==K_ESCAPE):
                    graj=0
                if event.type==KEYDOWN and event.key==K_1:
                    Swiat.zapisz()
                if event.type==KEYDOWN and event.key==K_2:
                    Swiat.wczytaj()
                if event.type==KEYDOWN and event.key==K_w and pygame.mouse.get_pressed()[0]: #dodanie wilka
                    p = pygame.mouse.get_pos()
                    x=p[0]
                    y=p[1]
                    if(Swiat.organizmy[x/30][y/30] == None):
                        wilk = Wilk(x/30, y/30, Swiat)
                        Swiat.tab.append(wilk)
                        Swiat.organizmy[wilk.X][wilk.Y] = wilk
                    Swiat.rysujSwiat()
                elif event.type==KEYDOWN and event.key==K_o and pygame.mouse.get_pressed()[0]: #dodanie owcy
                    p = pygame.mouse.get_pos()
                    x=p[0]
                    y=p[1]
                    if(Swiat.organizmy[x/30][y/30] == None):
                        owca = Owca(x/30, y/30, Swiat)
                        Swiat.tab.append(owca)
                        Swiat.organizmy[owca.X][owca.Y] = owca
                    Swiat.rysujSwiat()
                elif event.type==KEYDOWN and event.key==K_a and pygame.mouse.get_pressed()[0]: #dodanie antylopy
                    p = pygame.mouse.get_pos()
                    x=p[0]
                    y=p[1]
                    if(Swiat.organizmy[x/30][y/30] == None):
                        antylopa = Antylopa(x/30, y/30, Swiat)
                        Swiat.tab.append(antylopa)
                        Swiat.organizmy[antylopa.X][antylopa.Y] = antylopa
                    Swiat.rysujSwiat()
                elif event.type==KEYDOWN and event.key==K_l and pygame.mouse.get_pressed()[0]: #dodanie lisa
                    p = pygame.mouse.get_pos()
                    x=p[0]
                    y=p[1]
                    if(Swiat.organizmy[x/30][y/30] == None):
                        lis = Lis(x/30, y/30, Swiat)
                        Swiat.tab.append(lis)
                        Swiat.organizmy[lis.X][lis.Y] = lis
                    Swiat.rysujSwiat()
                elif event.type==KEYDOWN and event.key==K_z and pygame.mouse.get_pressed()[0]: #dodanie zolwia
                    p = pygame.mouse.get_pos()
                    x=p[0]
                    y=p[1]
                    if(Swiat.organizmy[x/30][y/30] == None):
                        zolw = Zolw(x/30, y/30, Swiat)
                        Swiat.tab.append(zolw)
                        Swiat.organizmy[zolw.X][zolw.Y] = zolw
                    Swiat.rysujSwiat()
                elif event.type==KEYDOWN and event.key==K_t and pygame.mouse.get_pressed()[0]: #dodanie trawy
                    p = pygame.mouse.get_pos()
                    x=p[0]
                    y=p[1]
                    if(Swiat.organizmy[x/30][y/30] == None):
                        trawa = Trawa(x/30, y/30, Swiat)
                        Swiat.tab.append(trawa)
                        Swiat.organizmy[trawa.X][trawa.Y] = trawa
                    Swiat.rysujSwiat()
                elif event.type==KEYDOWN and event.key==K_m and pygame.mouse.get_pressed()[0]: #dodanie mlecza
                    p = pygame.mouse.get_pos()
                    x=p[0]
                    y=p[1]
                    if(Swiat.organizmy[x/30][y/30] == None):
                        mlecz = Mlecz(x/30, y/30, Swiat)
                        Swiat.tab.append(mlecz)
                        Swiat.organizmy[mlecz.X][mlecz.Y] = mlecz
                    Swiat.rysujSwiat()
                elif event.type==KEYDOWN and event.key==K_j and pygame.mouse.get_pressed()[0]: #dodanie wilczych jagod
                    p = pygame.mouse.get_pos()
                    x=p[0]
                    y=p[1]
                    if(Swiat.organizmy[x/30][y/30] == None):
                        jagoda = Jagoda(x/30, y/30, Swiat)
                        Swiat.tab.append(jagoda)
                        Swiat.organizmy[jagoda.X][jagoda.Y] = jagoda
                    Swiat.rysujSwiat()
                elif event.type==KEYDOWN and event.key==K_g and pygame.mouse.get_pressed()[0]: #dodanie guarany
                    p = pygame.mouse.get_pos()
                    x=p[0]
                    y=p[1]
                    if(Swiat.organizmy[x/30][y/30] == None):
                        guarana = Guarana(x/30, y/30, Swiat)
                        Swiat.tab.append(guarana)
                        Swiat.organizmy[guarana.X][guarana.Y] = guarana
                    Swiat.rysujSwiat()
                elif event.type==KEYDOWN and event.key==K_SPACE:
                    Swiat.kierunekCzlowieka = -1
                    Swiat.wykonajTure()
                    Swiat.rysujSwiat()
                elif event.type==KEYDOWN and event.key==K_RIGHT:
                    Swiat.kierunekCzlowieka = 1
                    Swiat.wykonajTure()
                    Swiat.rysujSwiat()
                elif event.type==KEYDOWN and event.key==K_DOWN:
                    Swiat.kierunekCzlowieka = 2
                    Swiat.wykonajTure()
                    Swiat.rysujSwiat()
                elif event.type==KEYDOWN and event.key==K_LEFT:
                    Swiat.kierunekCzlowieka = 3
                    Swiat.wykonajTure()
                    Swiat.rysujSwiat()
                elif event.type==KEYDOWN and event.key==K_UP:
                    Swiat.kierunekCzlowieka = 4
                    Swiat.wykonajTure()
                    Swiat.rysujSwiat()
                elif event.type==KEYDOWN and event.key==K_s:
                    Swiat.kierunekCzlowieka = -1
                    Swiat.czyAktywowanoUmiejetnosc = True
                    Swiat.rysujSwiat()
				


if __name__ == '__main__':
   Main()