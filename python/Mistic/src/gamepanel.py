# -*- coding: utf-8 -*-
import pygame, graph

class GamePanel:
    def __init__(self,gamePanel,HP,MP):
        self.gamePanel = gamePanel
        
        self.fonGamePanel = graph.Sprite(0,0,'sprites/gamepanel.png',(0,0,800,48))
        #Кнопочки
        self.buttonExit = graph.Sprite(0,0,'sprites/buttons.png',(152,0,53,37))
        self.buttonExit0 = graph.Sprite(0,0,'sprites/buttons.png',(152,37,53,37))
        #Шрифты
        self.HPFont = pygame.font.Font('fonts/STIXGeneral-Bold.otf',12)
        self.MPFont = pygame.font.Font('fonts/STIXGeneral-Bold.otf',12) 
        
        self.fontExit = pygame.font.Font('fonts/STIXGeneral-Bold.otf',16)
        #Жизнь
        self.HPStart = graph.Sprite(0,0,'sprites/town_forest_tiles.png',(160,289,3,16))
        self.HPMiddle = graph.Sprite(0,0,'sprites/town_forest_tiles.png',(164,289,2,16))
        self.HPEnd = graph.Sprite(0,0,'sprites/town_forest_tiles.png',(172,289,3,16))
        #Мана
        self.MPStart = graph.Sprite(0,0,'sprites/town_forest_tiles.png',(160,289+16,3,16))
        self.MPMiddle = graph.Sprite(0,0,'sprites/town_forest_tiles.png',(164,289+16,2,16))
        self.MPEnd = graph.Sprite(0,0,'sprites/town_forest_tiles.png',(172,289+16,3,16))
        
        self.gamePanel = gamePanel
        self.HP = HP
        self.MP = MP
        #Курсор
        self.pngCursor = graph.Sprite(0,0,'sprites/town_forest_tiles.png',(32,320,32,32))
        self.mX = 0
        self.mY = 0
        
        
    def setHPMP(self,HP,MP):
        self.HP = HP
        self.MP = MP
        
    def infoTableFonts(self):
        #Отрисовываем шрифты 
        self.gamePanel.blit(self.HPFont.render(str(self.HP)+'/112',1,(255,255,255)),(105,6))
        self.gamePanel.blit(self.MPFont.render(str(self.MP)+'/112',1,(255,255,255)),(105,6+16))
    
    def buttonExitSprite(self):
        #Кнопка выхода    
        pX = 800
        self.buttonExit0.renderXY(self.gamePanel,pX-61,6)
        self.gamePanel.blit(self.fontExit.render('Меню',1,(111,111,111)),(744,15))
        self.gamePanel.blit(self.fontExit.render('Меню',1,(1,1,1)),(742,13))
		#Курсор игровой панель
        self.pngCursor.renderXY(self.gamePanel, self.mX, self.mY-522-30)
    
    def infoTable(self):
        """Индикаторы жизни и маны"""
        #Жизнь
        if (self.HP>1):     #112
            for i in range(self.HP-6):
                self.HPMiddle.renderXY(self.gamePanel,11+(i*2),9)
            self.HPStart.renderXY(self.gamePanel,8,9)            
        if (self.HP>110):
            self.HPEnd.renderXY(self.gamePanel,(self.HP*2)-2,9)
        #Мана
        if (self.MP>1):     #112
            for i in range(self.MP-6):
                self.MPMiddle.renderXY(self.gamePanel,11+(i*2),24)
            self.MPStart.renderXY(self.gamePanel,8,24)            
        if (self.MP>110):
            self.MPEnd.renderXY(self.gamePanel,(self.MP*2)-2,24)
    
        #self.infoTableFonts()
    def setMouseLoc(self,mX,mY):
        self.mX = mX
        self.mY = mY
        
    def render(self):
        """Объекты игровой панели"""
        #Отрисовка
        self.fonGamePanel.renderXY(self.gamePanel,0,0)
        #Кнопка выхода    
        pX = 800
        self.buttonExit.renderXY(self.gamePanel,pX-61,6)
        self.gamePanel.blit(self.fontExit.render('Меню',1,(111,111,111)),(744,15))
        self.gamePanel.blit(self.fontExit.render('Меню',1,(1,1,1)),(742,13))
        #Жизни и мана
        self.infoTable()
        #Курсор игровой панель
        self.pngCursor.renderXY(self.gamePanel, self.mX, self.mY-522-30)
        

    
