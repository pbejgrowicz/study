# -*- coding: utf-8 -*-
import pygame
from pygame.locals import *
from sys import exit 
from Zwierze import *
import random
class Lis(Zwierze): 
	def __init__(self, x, y, swiat):
		self.sila = 3
		self.inicjatywa = 7
		self.foto = pygame.image.load('fox.png')
		self.sw = swiat
		self.X = x
		self.Y = y
		self.walka = 1
		self.nazwa = 'lis'
		self.znak = 'L'
		self.usuniety = 0
	
	def kolizja(self, o):
		if (o.nazwa == 'lis'):
			if(self.X - 1 > 1):
				if(self.sw.organizmy[self.X-1][self.Y] == None):
					lis = Lis(self.X-1, self.Y, self.sw)
					self.sw.organizmy[lis.X][lis.Y] = lis
					self.sw.nowy[self.sw.zliczNowy()] = lis

			elif(self.X + 1 < 20):
				if(self.sw.organizmy[self.X+1][self.Y] == None):
					lis = Lis(self.X+1, self.Y, self.sw)
					self.sw.organizmy[lis.X][lis.Y] = lis
					self.sw.nowy[self.sw.zliczNowy()] = lis

			elif(self.Y - 1 > 1):
				if(self.sw.organizmy[self.X][self.Y-1] == None):
					lis = Lis(self.X, self.Y-1, self.sw)
					self.sw.organizmy[lis.X][lis.Y] = lis
					self.sw.nowy[self.sw.zliczNowy()] = lis


			elif(self.Y + 1 < 20):
				if(self.sw.organizmy[self.X][self.Y+1] == None):
					lis = Lis(self.X, self.Y+1, self.sw)
					self.sw.organizmy[lis.X][lis.Y] = lis
					self.sw.nowy[self.sw.zliczNowy()] = lis

		else:
			#walka tylko ze slabszymi
			if o.sila <= self.sila:
				self.atakuj(o)