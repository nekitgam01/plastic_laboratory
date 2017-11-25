# -*- coding: utf-8 -*-
"""Модуль меню паузы"""

import pygame, graph, sys

class GameMenu:
    def __init__(self,run, win, screen,mX,mY):
        #Инициализация
        pygame.font.init()                                                      
        #Получаемые переменные
        self.screen0 = screen                                                         
        self.win0 = win     
        self.run0 = run
        self.mX = mX
        self.mY = mY
        #Переменные
        self.mX = self.mY = 0 #Позиция мыши
        self.sX = self.sY = 0 #Позиция игрового экрана  
        #Объекты
        self.fonGameMenu = graph.Sprite(0,0,'sprites/town_forest_tiles.png',(0,0,32,32))                   
        #Книга (стилистика меню)
        self.bookStyle = graph.Sprite(0,0,'sprites/town_forest_tiles.png',(0,384,672+64,490))
        #фон
        self.Background = graph.Sprite(0,0,'sprites/town_forest_tiles.png',(0,896,800,600))
        
    def render(self,mX,mY):
        self.mX = mX
        self.mY = mY
        '''Заливка Игрвого экрана'''
        self.screen0.fill((0,0,0))
            
        """Отрисовка объектов"""
        #Оформление
        self.Background.renderXY(self.screen0,0,0)
        self.bookStyle.renderXY(self.screen0,32,0)
               
            
            
            
            
            
            
            
