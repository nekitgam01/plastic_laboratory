# -*- coding: utf-8 -*-
#класс уровня 1

import pygame, sys, graph, window, hero, stepper

class level0:

    """Инициализируем наш уровень и все его объекты"""
    def __init__(self,win,screen,sRGB = [],mX=0,mY=0):
        #Получаемые переменные
        self.screen0 = screen
        self.win0 = win
        self.sRGB = sRGB
        self.scX = 0
        self.scY = 0
        self.mX = mX
        self.mY = mY
        #Героиня
        self.nanami = hero.hero(400,300,'sprites/nana.png',(0,0,32,56))
        self.nanami.DownAnimate()
        #Позиция гороини от левого верхнего угла
        self.nanami.xpos = 257
        self.nanami.ypos = 372
        #Позиция ног Нанами
        self.nanami.gX = self.nanami.xpos - 16
        self.nanami.gY = self.nanami.ypos - 53
        #Булеан переменные говорящие Нанами о том что нужно идти
        self.nanami.down_step = False
        self.nanami.up_step = False
        self.nanami.left_step = False
        self.nanami.right_step = False
        #Определитель нажатия
        self.KeyDownMap = 0
        #Отрисовка комнаты (слои)
        self.room = graph.Sprite(0,0,'sprites/level0.png',(0,0,800,600))
        self.roomFront = graph.Sprite(0,0,'sprites/level0_yt.png',(0,0,800,600))
        #Курсор
        self.pngCursor = graph.Sprite(0,0,'sprites/town_forest_tiles.png'
        ,(32,320,32,32))
        #Допустим попытка номер 1 - список непроходимостей
        self.StopListDown = [[166,229,202,280,250,0],   #x1 Example: if ((x > x1) and (x < x2))
                             [202,247,228,600,280,166], #x2          :
                             [274,341,320,274,285,211], #y1          and ((y < y1) and (y < y2))
                             [274,341,320,274,285,211]] #y2          :
        
        self.StopListLeft = [[205,235,175,140,175], # Example if ((x > x1) and (x > x2))
                             [205,235,175,140,175], #         :
                             [279,328,214,185,103], #         and ((y > y1) and (y < y2))
                             [328,350,281,214,185]]
                             
        self.StopListRight = [[244,600,442,600,280], #Example if ((x < x1) and (x < x2))
                              [244,600,442,600,280], #        :
                              [286,103,141,235,274], #        and ((y > y1) and (y < y2))
                              [341,142,235,275,287]] #        :
        
        self.StopListUp = [[175,358,405], #x1 Example if ((x>=x1) and (x<=x2))
                           [359,406,600], #x2         :
                           [113,50,113],  #y1         and ((y<=y1) and (y<=y2))
                           [113,50,113]]  #y2         :
	

    """Отрисовываем все объекты в игре"""
    def render(self,mX,mY):
        #mouse
        self.mX = mX
        self.mY = mY
        '''Заливка Игрвого экрана'''
        self.screen0.fill((self.sRGB[0],self.sRGB[1],self.sRGB[2]))

        """Объекты игрового поля"""
        #Комната
        self.room.render(self.screen0)

        #Персонаж
        self.nanami.FPSadd()
        self.nanami.renderXY(self.screen0,self.nanami.xpos,self.nanami.ypos)

        #Передние объекты комнаты
        self.roomFront.render(self.screen0)
        #Ходьба
        
        for i in range(3):
            if (((self.nanami.gX >= self.StopListUp[0][i]) and (self.nanami.gX <= self.StopListUp[1][i]))
            and ((self.nanami.gY >= self.StopListUp[2][i]) and (self.nanami.gY >= self.StopListUp[3][i]))):
                if self.nanami.up_step:
                    self.nanami.UpAnimate()
                    self.nanami.ypos -= 3
                    self.nanami.up_step = False

        for i in range(6):
            if (((self.nanami.gX > self.StopListDown[0][i]) and (self.nanami.gX < self.StopListDown[1][i]))
            and ((self.nanami.gY < self.StopListDown[2][i]) and (self.nanami.gY < self.StopListDown[3][i]))):
                if self.nanami.down_step:
                    self.nanami.DownAnimate()
                    self.nanami.ypos += 3
                    self.nanami.down_step = False
        for i in range(5):
            if (((self.nanami.gX > self.StopListLeft[0][i]) and (self.nanami.gX > self.StopListLeft[1][i]))
            and ((self.nanami.gY > self.StopListLeft[2][i]) and (self.nanami.gY < self.StopListLeft[3][i]))):    
                if self.nanami.left_step:
                    self.nanami.LeftAnimate()
                    self.nanami.xpos -= 3
                    self.nanami.left_step = False
        for i in range(5):
            if (((self.nanami.gX < self.StopListRight[0][i]) and (self.nanami.gX < self.StopListRight[1][i]))
            and ((self.nanami.gY > self.StopListRight[2][i]) and (self.nanami.gY < self.StopListRight[3][i]))):
                if self.nanami.right_step:
                    self.nanami.RightAnimate()
                    self.nanami.xpos += 3
                    self.nanami.right_step = False
        #Координаты
        self.nanami.gX = self.nanami.xpos - 16
        self.nanami.gY = self.nanami.ypos - 53
        print('X='+str(self.nanami.gX)+' Y='+str(self.nanami.gY)+' rX='+str(self.nanami.xpos)+' rY='+str(self.nanami.ypos))
        print('Step?='+str(stepper.canvas_step(142,96,534,338,self.nanami.gX, self.nanami.gY)))
        #Курсор
        self.pngCursor.renderXY(self.screen0, self.mX-self.scX, self.mY)






