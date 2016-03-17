# -*- coding: utf-8 -*-
import pygame
from pygame.locals import *
from sys import exit 
from Zwierze import *
import random
class Zolw(Zwierze):
	def __init__(self, x, y, swiat):
		self.sila = 2
		self.inicjatywa = 1
		self.foto = pygame.image.load('zolw.png')
		self.sw = swiat
		self.X = x
		self.Y = y 
		self.walka = 1
		self.nazwa = 'zolw'
		self.znak = 'Z'
		self.usuniety = 0
	
	def akcja(self, organizmy):
		random.seed()
		tmp_x = random.randint(-1, 1)
		tmp_y = random.randint(-1, 1)
		szansa = random.randint(0,4) #tylko w 25% porusza sie zolw 
		if (organizmy[self.X + tmp_x][self.Y + tmp_y] == None and szansa == 0):
			self.X = self.X + tmp_x
			self.Y = self.Y + tmp_y
			if self.X > 18:
				self.X = 18
			elif self.X < 1:
				self.X = 1
			if self.Y > 18:
				self.Y = 18
			elif self.Y < 1:
				self.Y = 1
		elif (szansa == 0):
			self.kolizja(organizmy[self.X + tmp_x][self.Y + tmp_y])	
	
	def kolizja(self, o):
		if (o.nazwa == 'zolw'):
			if(self.X - 1 > 1):
				if(self.sw.organizmy[self.X-1][self.Y] == None):
					zolw = Zolw(self.X-1, self.Y, self.sw)
					self.sw.organizmy[zolw.X][zolw.Y] = zolw
					self.sw.nowy[self.sw.zliczNowy()] = zolw
			elif(self.X + 1 < 20):
				if(self.sw.organizmy[self.X+1][self.Y] == None):
					zolw = Zolw(self.X+1, self.Y, self.sw)
					self.sw.organizmy[zolw.X][zolw.Y] = zolw
					self.sw.nowy[self.sw.zliczNowy()] = zolw
			elif(self.Y - 1 > 1):
				if(self.sw.organizmy[self.X][self.Y-1] == None):
					zolw = Zolw(self.X, self.Y-1, self.sw)
					self.sw.organizmy[zolw.X][zolw.Y] = zolw
					self.sw.nowy[self.sw.zliczNowy()] = zolw
			elif(self.Y + 1 < 20):
				if(self.sw.organizmy[self.X][self.Y+1] == None):
					zolw = zolw(self.X, self.Y+1, self.sw)
					self.sw.organizmy[zolw.X][zolw.Y] = zolw
					self.sw.nowy[self.sw.zliczNowy()] = zolw
		elif(o.sila < 5):
			return
		else:
			self.atakuj(o)