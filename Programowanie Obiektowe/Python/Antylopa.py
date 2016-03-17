# -*- coding: utf-8 -*-
import pygame                # importujemy biblioteki pygame
from pygame.locals import *  # importujemy nazwy [QUIT, KEYDOWN,K_ESCAPE] itp.
from sys import exit 
from Zwierze import *
import random
class Antylopa(Zwierze):
	def __init__(self, x, y, swiat):
		self.sila = 4 
		self.inicjatywa = 4
		self.foto = pygame.image.load('antylopa.png')
		self.sw = swiat
		self.X = x
		self.Y = y
		self.walka = 1
		self.nazwa = 'antylopa'
		self.znak = 'A'
		self.usuniety = 0
		
	def akcja(self, organizmy):
		random.seed()
		tmp_x = random.randint(-2, 2)
		tmp_y = random.randint(-2, 2)
		if (organizmy[self.X + tmp_x][self.Y + tmp_y] == None):
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
		else:
			self.kolizja(organizmy[self.X + tmp_x][self.Y + tmp_y])
			
	def kolizja(self, o):
		if (o.nazwa == 'antylopa'):
			if(self.X - 1 > 1):
				if(self.sw.organizmy[self.X-1][self.Y] == None):
					antylopa = Antylopa(self.X-1, self.Y, self.sw)
					self.sw.organizmy[antylopa.X][antylopa.Y] = antylopa
					self.sw.nowy[self.sw.zliczNowy()] = antylopa
			elif(self.X + 1 < 20):
				if(self.sw.organizmy[self.X+1][self.Y] == None):
					antylopa = Antylopa(self.X+1, self.Y, self.sw)
					self.sw.organizmy[antylopa.X][antylopa.Y] = antylopa
					self.sw.nowy[self.sw.zliczNowy()] = antylopa
					
			elif(self.Y - 1 > 1):		
				if(self.sw.organizmy[self.X][self.Y-1] == None):
					antylopa = Antylopa(self.X, self.Y-1, self.sw)
					self.sw.organizmy[antylopa.X][antylopa.Y] = antylopa
					self.sw.nowy[self.sw.zliczNowy()] = antylopa
					
			elif(self.Y + 1 < 20):	
				if(self.sw.organizmy[self.X][self.Y+1] == None):
					antylopa = Antylopa(self.X, self.Y+1, self.sw)
					self.sw.organizmy[antylopa.X][antylopa.Y] = antylopa
					self.sw.nowy[self.sw.zliczNowy()] = antylopa
		else:
		
			self.walka = self.walka * (-1)
			if(self.walka == 1):
				self.atakuj(o)
						
			elif(self.walka == (-1)):
				if(self.X - 1 > 1):
					if(self.sw.organizmy[self.X-1][self.Y] == None):
						prev_x = self.X
						prev_y = self.Y
						self.sw.organizmy[self.X-1][self.Y] = self.sw.organizmy[self.X][self.Y]
						self.sw.organizmy[prev_x][prev_y] = None
						self.X = self.X - 1
				
				if(self.X + 1 < 20):
					if(self.sw.organizmy[self.X+1][self.Y] == None):
						prev_x = self.X
						prev_y = self.Y
						self.sw.organizmy[self.X+1][self.Y] = self.sw.organizmy[self.X][self.Y]
						self.sw.organizmy[prev_x][prev_y] = None
						self.X = self.X + 1		
						
				if(self.Y - 1 > 1):		
					if(self.sw.organizmy[self.X][self.Y-1] == None):
						prev_x = self.X
						prev_y = self.Y
						self.sw.organizmy[self.X][self.Y-1] = self.sw.organizmy[self.X][self.Y]
						self.sw.organizmy[prev_x][prev_y] = None
						self.X = self.Y - 1
					
				if(self.Y + 1 < 20):	
					if(self.sw.organizmy[self.X][self.Y+1] == None):
						prev_x = self.X
						prev_y = self.Y
						self.sw.organizmy[self.X][self.Y+1] = self.sw.organizmy[self.X][self.Y]
						self.sw.organizmy[prev_x][prev_y] = None
						self.X = self.X + 1
			
			