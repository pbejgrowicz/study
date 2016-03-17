# -*- coding: utf-8 -*-
import pygame
from pygame.locals import *
from sys import exit 
from Organizm import *
import random
import sys
class Zwierze(Organizm):
	 
	def akcja(self, organizmy):
		random.seed()
		tmpX=random.randint(-1,1)
		tmpY=random.randint(-1,1)
		if (organizmy[self.X + tmpX][self.Y + tmpY] == None):
			self.X = self.X + tmpX
			self.Y = self.Y + tmpY
			if self.X > 21:
				self.X = 21
			elif self.X < 0:
				self.X = 0
			if self.Y > 21:
				self.Y = 21
			elif self.Y < 0:
				self.Y = 0
		else:
			if (organizmy[self.X + tmpX][self.Y + tmpY] != None):
				self.kolizja(organizmy[self.X + tmpX][self.Y + tmpY])
			
				
	def ruch(self):
		if self.usuniety == 0:
			prev_x = self.X
			prev_y = self.Y
			self.sw.organizmy[prev_x][prev_y] = None
			self.akcja(self.sw.organizmy)
			if self.sw.organizmy[self.X][self.Y] == None:
				self.sw.organizmy[self.X][self.Y] = self
				
	def atakuj(self, o):
		b=0
		if(self.sila >= o.sila):
			print self.nazwa + ' wygral z ' + o.nazwa
			if o.znak == "G":
				self.sila += 3
				print self.nazwa + ' zyskal 3 sily'
			for i in self.sw.tab:
				if(self.sw.tab[b] == self.sw.organizmy[o.X][o.Y]):
					o.usuniety = 1
					prev_x = self.X
					prev_y = self.Y
					self.X = o.X
					self.Y = o.Y
					self.sw.organizmy[o.X][o.Y] = self.sw.organizmy[self.X][self.Y]
					self.sw.organizmy[prev_x][prev_y] = None
					b = b - 1
				b=b+1
		else:
			print self.nazwa + ' przegral z ' + o.nazwa
			b=0
			self.usuniety = 1
			if o.znak == "J":
				o.usuniety = 1
			self.sw.organizmy[self.X][self.Y] = None
			
	
				
			
		