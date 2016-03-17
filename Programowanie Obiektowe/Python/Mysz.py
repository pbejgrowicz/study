# -*- coding: utf-8 -*-
import pygame
from pygame.locals import *
from sys import exit 
from Zwierze import *
import random
class Mysz(Zwierze):
	def __init__(self, x, y, swiat):
		self.sila = 1
		self.inicjatywa = 6
		self.foto = pygame.image.load('mouse.png')
		self.sw = swiat
		self.X = x
		self.Y = y 
		self.walka = 1
		self.nazwa = 'mysz'
		self.znak = 'U'

	def kolizja(self, o):
		if (o.nazwa == 'mysz'):
			if(self.X - 1 > 1):
				if(self.sw.organizmy[self.X-1][self.Y] == None):
					mysz = Mysz(self.X-1, self.Y, self.sw)
					self.sw.organizmy[mysz.X][mysz.Y] = mysz
					self.sw.nowy[self.sw.zlicz_nowy()] = mysz

			elif(self.X + 1 < 20):
				if(self.sw.organizmy[self.X+1][self.Y] == None):
					mysz = Mysz(self.X+1, self.Y, self.sw)
					self.sw.organizmy[mysz.X][mysz.Y] = mysz
					self.sw.nowy[self.sw.zlicz_nowy()] = mysz

			elif(self.Y - 1 > 1):
				if(self.sw.organizmy[self.X][self.Y-1] == None):
					mysz = Mysz(self.X, self.Y-1, self.sw)
					self.sw.organizmy[mysz.X][mysz.Y] = mysz
					self.sw.nowy[self.sw.zlicz_nowy()] = mysz

			elif(self.Y + 1 < 20):
				if(self.sw.organizmy[self.X][self.Y+1] == None):
					mysz = Mysz(self.X, self.Y+1, self.sw)
					self.sw.organizmy[mysz.X][mysz.Y] = mysz
					self.sw.nowy[self.sw.zlicz_nowy()] = mysz

		else:
			b=0
			if(self.sila >= o.sila):
				for i in self.sw.tab:
					if(self.sw.tab[b] == self.sw.organizmy[o.X][o.Y]):
						self.sw.tab.remove(self.sw.tab[b])
						prev_x = self.X
						prev_y = self.Y
						self.sw.organizmy[o.X][o.Y] = self.sw.organizmy[self.X][self.Y]
						#self.X = o.X
						#self.Y = o.Y
						self.sw.organizmy[o.X][o.Y] = None
						self.sw.organizmy[prev_x][prev_y] = None
						b = b - 1
					b = b + 1