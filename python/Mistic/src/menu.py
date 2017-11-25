# -*- coding: utf-8 -*-
'''Модуль основного меню'''
import pygame, sys, graph, window, level0

class menu:
	def __init__(self,win, screen, sRGB = [],mX=0,mY=0): #| True/False | window | screen
		#Инициализация
		pygame.font.init()
		#Получаемые переменные
		self.screen0 = screen
		self.win0 = win
		self.sRGB = sRGB
		#Переменные
		self.mX = self.mY = 0
		#Кнопочки
		self.button_start = graph.Sprite(720,560,'sprites/buttons.png',(0,0,75,36))
		self.fontStart = pygame.font.Font('fonts/STIXGeneral-Bold.otf',14)
		self.button_exit = graph.Sprite(643,560,'sprites/buttons.png',(76,0,75,36))
		self.fontExit = pygame.font.Font('fonts/STIXGeneral-Bold.otf',14)
		#Независимые надписи
		self.fontCompany = pygame.font.Font('fonts/STIXGeneral-Bold.otf',18)
		self.fontTitle = pygame.font.Font('fonts/STIXGeneral-Bold.otf',40)
		self.fontVer = pygame.font.Font('fonts/STIXGeneral-Bold.otf',18)
		#Курсор
		self.cursor = pygame.cursors.load_xbm('sprites/crs.xbm','sprites/crs.xbm')
		pygame.mouse.set_cursor(*self.cursor)
		self.pngCursor = graph.Sprite(0,0,'sprites/town_forest_tiles.png',(32,320,32,32))
		#Фон
		self.background = graph.Sprite(0,0,'sprites/title.png',(0,0,800,600))
	def button_start_active(self):
		self.button_start = graph.Sprite(720,560,'sprites/buttons.png',(0,37,75,36))
	def button_start_inactive(self):
		self.button_start = graph.Sprite(720,560,'sprites/buttons.png',(0,0,75,36))
	def button_exit_active(self):
		self.button_exit = graph.Sprite(643,560,'sprites/buttons.png',(76,37,75,36))
	def button_exit_inactive(self):
		self.button_exit = graph.Sprite(643,560,'sprites/buttons.png',(76,0,75,36))
	def render(self,mX,mY):
		self.mX = mX
		self.mY = mY 
		'''Заливка экрана'''
		self.screen0.fill((self.sRGB[0],self.sRGB[1],self.sRGB[2]))
		#Отображаем тайлы
		self.background.render(self.screen0)
			
			
		self.button_start.render(self.screen0)

		self.button_exit.render(self.screen0)
			
			
		#Отрисовываем шрифты
		self.screen0.blit(self.fontStart.render('Начать',1,(111,111,111)),(745,568))
		self.screen0.blit(self.fontStart.render('Начать',1,(0,0,0)),(743,566))

		self.screen0.blit(self.fontExit.render('Выйти',1,(111,111,111)),(671,568))
		self.screen0.blit(self.fontExit.render('Выйти',1,(0,0,0)),(669,566))


		self.screen0.blit(self.fontCompany.render('[ При поддержке PyGame 3 ]',1,(1,1,1)),(12,549))
		self.screen0.blit(self.fontCompany.render('[ При поддержке PyGame 3 ]',1,(212,253,255)),(10,547))
		self.screen0.blit(self.fontCompany.render('[ Разработчик: MoonLight+]',1,(1,1,1)),(12,568))
		self.screen0.blit(self.fontCompany.render('[ Разработчик: MoonLight+]',1,(212,253,255)),(10,566))

		self.screen0.blit(self.fontTitle.render('Мистическая башня',1,(1,1,1)),(227,14))
		self.screen0.blit(self.fontTitle.render('Мистическая башня',1,(212,253,255)),(225,12))

		self.screen0.blit(self.fontVer.render('[Альфа]',1,(1,1,1)),(532,57))
		self.screen0.blit(self.fontVer.render('[Альфа]',1,(212,253,255)),(530,55))
		#Курсор
		self.pngCursor.renderXY(self.screen0, self.mX, self.mY)
		
