# -*- coding: utf-8 -*-
import pygame
from pygame.locals import *
from sys import exit 
from Zwierze import *
class Owca(Zwierze):
	def __init__(self, x, y, swiat): 
		self.sila = 4
		self.inicjatywa = 4
		self.foto = pygame.image.load('sheep.png')
		self.sw = swiat
		self.X = x
		self.Y = y
		self.nazwa = 'owca'
		self.znak = 'O'
		self.usuniety = 0
		
	def kolizja(self, o):
		if (o.nazwa == 'owca'):
			if(self.X - 1 > 1):
				if(self.sw.organizmy[self.X-1][self.Y] == None):
					owca = Owca(self.X-1, self.Y, self.sw)
					self.sw.organizmy[owca.X][owca.Y] = owca
					self.sw.nowy[self.sw.zliczNowy()] = owca
				
			elif(self.X + 1 < 20):
				if(self.sw.organizmy[self.X+1][self.Y] == None):
					owca = Owca(self.X+1, self.Y, self.sw)
					self.sw.organizmy[owca.X][owca.Y] = owca
					self.sw.nowy[self.sw.zliczNowy()] = owca
					
			elif(self.Y - 1 > 1):		
				if(self.sw.organizmy[self.X][self.Y-1] == None):
					owca = Owca(self.X, self.Y-1, self.sw)
					self.sw.organizmy[owca.X][owca.Y] = owca
					self.sw.nowy[self.sw.zliczNowy()] = owca
					
			elif(self.Y + 1 < 20):	
				if(self.sw.organizmy[self.X][self.Y+1] == None):
					owca = Owca(self.X, self.Y+1, self.sw)
					self.sw.organizmy[owca.X][owca.Y] = owca
					self.sw.nowy[self.sw.zliczNowy()] = owca
		else:
			self.atakuj(o)
	