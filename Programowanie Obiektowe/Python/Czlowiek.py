# -*- coding: utf-8 -*-
import pygame
from pygame.locals import *
from sys import exit 
from Zwierze import *
import random
class Czlowiek(Zwierze):
	def __init__(self, x, y, swiat):
		self.sila = 5
		self.inicjatywa = 4
		self.foto = pygame.image.load('human.png')
		self.sw = swiat
		self.X = x
		self.Y = y 
		self.nazwa = 'czlowiek'
		self.znak = '@'
		self.usuniety = 0
		self.ileRund = 0
		self.ileRundBezUmiejetnosci = 0

	def akcja(self, organizmy):
		tmpX = self.X
		tmpY = self.Y
		
		if self.sw.czyAktywowanoUmiejetnosc == True and self.ileRund == 0 and self.ileRundBezUmiejetnosci == 0:
			self.ileRund = 6
			self.ileRundBezUmiejetnosci = 11
			print 'AKTYWOWANO UMIEJETNOSC'

		if self.ileRundBezUmiejetnosci > 0 and self.ileRund == 0: 
			self.sw.czyAktywowanoUmiejetnosc = False
			
		if (self.sw.kierunekCzlowieka == 1):
			self.X += 1
		if (self.sw.kierunekCzlowieka == 2):
			self.Y += 1
		if (self.sw.kierunekCzlowieka == 3):
			self.X -= 1
		if (self.sw.kierunekCzlowieka == 4):
			self.Y -= 1
		if self.X > 21:
			self.X = 21
		elif self.X < 0:
			self.X = 0
		if self.Y > 21:
			self.Y = 21
		elif self.Y < 0:
			self.Y = 0
		else:
			if(organizmy[self.X][self.Y] != None and organizmy[self.X][self.Y].sila > self.sila and self.sw.czyAktywowanoUmiejetnosc == True):
				self.X = tmpX
				self.Y = tmpY
			elif (organizmy[self.X][self.Y] != None):
				self.atakuj(organizmy[self.X][self.Y])
		
		if self.sw.czyAktywowanoUmiejetnosc == True:
			self.ileRund -= 1
		if self.ileRundBezUmiejetnosci > 0: 
			self.ileRundBezUmiejetnosci -= 1
		if self.sw.czyAktywowanoUmiejetnosc == True and self.ileRund == 0:
			self.sw.czyAktywowanoUmiejetnosc = False
			print 'WYLACZONO UMIEJETNOSC'


		
		self.sw.wyczyscUmarlych()		
		self.sw.rysujSwiat()
				