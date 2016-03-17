# -*- coding: utf-8 -*-
import pygame
from pygame.locals import *
from sys import exit 
from Roslina import *
import random
class Mlecz(Roslina):
    	def __init__(self, x, y, swiat):
		self.foto = pygame.image.load('sonchus.png')
		self.X = x
		self.Y = y
		self.sw = swiat 
		self.sila = 0
		self.nazwa = 'mlecz'
		self.znak = 'M'
		self.usuniety = 0

	def ruch(self):
		for x in range(0,3):
			self.akcja()

	def kolizja(self, o):
		pass
		
	def akcja(self):
		random.seed()
		szansa = random.randint(0, 4)
		tmpX = random.randint(-1,1) + self.X
		tmpY = random.randint(-1,1) + self.Y
		if self.sw.organizmy[tmpX][tmpY] == None and tmpX < 21 and tmpX > 0 and tmpY < 21 and tmpY > 0 and szansa == 0:
			mlecz = Mlecz(tmpX, tmpY, self.sw)
			self.sw.organizmy[mlecz.X][mlecz.Y] = mlecz
			self.sw.nowy[self.sw.zliczNowy()] = mlecz
					
		