# -*- coding: utf-8 -*-
import pygame
from pygame.locals import *
from sys import exit 
from Zwierze import *
class Wilk(Zwierze):
	def __init__(self, x, y, swiat):
		self.foto = pygame.image.load('wolf.png')
		self.sila = 9
		self.inicjatywa = 5
		self.X = x
		self.Y = y
		self.sw = swiat
		self.nazwa = 'wilk'
		self.znak = 'W'
		self.usuniety = 0
		
	def kolizja(self, o):
		if (o.nazwa == 'wilk'):
			if(self.X - 1 > 1):
				if(self.sw.organizmy[self.X-1][self.Y] == None):
					wilk = Wilk(self.X-1, self.Y, self.sw)
					self.sw.organizmy[wilk.X][wilk.Y] = wilk
					self.sw.nowy[self.sw.zliczNowy()] = wilk
				
			elif(self.X + 1 < 20):
				if(self.sw.organizmy[self.X+1][self.Y] == None):
					wilk = Wilk(self.X+1, self.Y, self.sw)
					self.sw.organizmy[wilk.X][wilk.Y] = wilk
					self.sw.nowy[self.sw.zliczNowy()] = wilk
					
			elif(self.Y - 1 > 1):		
				if(self.sw.organizmy[self.X][self.Y-1] == None):
					wilk = Wilk(self.X, self.Y-1, self.sw)
					self.sw.organizmy[wilk.X][wilk.Y] = wilk
					self.sw.nowy[self.sw.zliczNowy()] = wilk
					
			elif(self.Y + 1 < 20):	
				if(self.sw.organizmy[self.X][self.Y+1] == None):
					wilk = Wilk(self.X, self.Y+1, self.sw)
					self.sw.organizmy[wilk.X][wilk.Y] = wilk
					self.sw.nowy[self.sw.zliczNowy()] = wilk
		else:
			self.atakuj(o)
