# -*- coding: utf-8 -*-
import pygame
from pygame.locals import *
from sys import exit 
from Roslina import *
import random
class Guarana(Roslina):
	def __init__(self, x, y, swiat):
		self.foto = pygame.image.load('guarana.jpg')
		self.X = x 
		self.Y = y
		self.sw = swiat
		self.sila = 0
		self.nazwa = 'guarana'
		self.znak = 'G'
		self.usuniety = 0
		
	def ruch(self):
		self.akcja()
		
	def kolizja(self, o):
		pass
		
	def akcja(self):
		random.seed()
		szansa = random.randint(0, 4)
		tmpX = random.randint(-1,1) + self.X
		tmpY = random.randint(-1,1) + self.Y
		if self.sw.organizmy[tmpX][tmpY] == None and tmpX < 21 and tmpX > 0 and tmpY < 21 and tmpY > 0 and szansa == 0:
			guarana = Guarana(tmpX, tmpY, self.sw)
			self.sw.organizmy[guarana.X][guarana.Y] = guarana
			self.sw.nowy[self.sw.zliczNowy()] = guarana
		
					
		