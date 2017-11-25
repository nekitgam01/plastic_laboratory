# -*- coding: utf-8 -*-
"""Модуль героя"""
import graph, pygame

class hero:
    def __init__(self,xpos,ypos,filename,kadrXYWH=[]):
        self.filename = filename
        self.kadrXYWH = kadrXYWH
        self.x = xpos
        self.y = ypos
        self.animPlus = 4
        self.name = 'Nanami'
        self.brushHero = graph.Sprite(0,0,self.filename,(self.kadrXYWH[0],self.kadrXYWH[1],self.kadrXYWH[2],self.kadrXYWH[3])) 
        self.mFPS = 0
    def FPSadd(self):
        self.mFPS += 1
        if self.mFPS == self.animPlus * 4:
            self.mFPS = 0
    def LeftStop(self):
        self.brushHero = None
        self.brushHero = graph.Sprite(0,0,self.filename,(self.kadrXYWH[0],
                                      self.kadrXYWH[1]+224,self.kadrXYWH[2],self.kadrXYWH[3]))
    def RightStop(self):
        self.brushHero = None
        self.brushHero = graph.Sprite(0,0,self.filename,(self.kadrXYWH[0],
                                      self.kadrXYWH[1]+672,self.kadrXYWH[2],self.kadrXYWH[3]))
    def UpStop(self):
        self.brushHero = None
        self.brushHero = graph.Sprite(0,0,self.filename,(self.kadrXYWH[0],
                                      self.kadrXYWH[1]+448,self.kadrXYWH[2],self.kadrXYWH[3]))
    def DownStop(self):
        self.brushHero = None
        self.brushHero = graph.Sprite(0,0,self.filename,(self.kadrXYWH[0],
                                      self.kadrXYWH[1],self.kadrXYWH[2],self.kadrXYWH[3]))
    def LeftAnimate(self):
        if  ((self.mFPS >= 0) and (self.mFPS <self.animPlus)):
            self.brushHero = None
            self.brushHero = graph.Sprite(0,0,self.filename,(self.kadrXYWH[0],
                                          self.kadrXYWH[1]+224,self.kadrXYWH[2],self.kadrXYWH[3])) 
        elif (self.mFPS == self.animPlus):
            self.brushHero = None
            self.brushHero = graph.Sprite(0,0,self.filename,(self.kadrXYWH[0],
                                          self.kadrXYWH[1]+224+56,self.kadrXYWH[2],self.kadrXYWH[3])) 
        elif (self.mFPS == self.animPlus * 2):
            self.brushHero = None
            self.brushHero = graph.Sprite(0,0,self.filename,(self.kadrXYWH[0],
                                          self.kadrXYWH[1]+224+112,self.kadrXYWH[2],self.kadrXYWH[3])) 
        elif (self.mFPS == self.animPlus * 3):
            self.brushHero = None
            self.brushHero = graph.Sprite(0,0,self.filename,(self.kadrXYWH[0],
                                          self.kadrXYWH[1]+224+168,self.kadrXYWH[2],self.kadrXYWH[3])) 
    def RightAnimate(self):
        if  ((self.mFPS >= 0) and (self.mFPS <self.animPlus)):
            self.brushHero = None
            self.brushHero = graph.Sprite(0,0,self.filename,(self.kadrXYWH[0],
                                          self.kadrXYWH[1]+672,self.kadrXYWH[2],self.kadrXYWH[3])) 
        elif (self.mFPS == self.animPlus):
            self.brushHero = None
            self.brushHero = graph.Sprite(0,0,self.filename,(self.kadrXYWH[0],
                                          self.kadrXYWH[1]+672+56,self.kadrXYWH[2],self.kadrXYWH[3])) 
        elif (self.mFPS == self.animPlus * 2):
            self.brushHero = None
            self.brushHero = graph.Sprite(0,0,self.filename,(self.kadrXYWH[0],
                                          self.kadrXYWH[1]+672+112,self.kadrXYWH[2],self.kadrXYWH[3])) 
        elif (self.mFPS == self.animPlus * 3):
            self.brushHero = None
            self.brushHero = graph.Sprite(0,0,self.filename,(self.kadrXYWH[0],
                                          self.kadrXYWH[1]+672+168,self.kadrXYWH[2],self.kadrXYWH[3])) 
    def UpAnimate(self):
        if ((self.mFPS >= 0) and (self.mFPS <self.animPlus)):
            self.brushHero = None
            self.brushHero = graph.Sprite(0,0,self.filename,(self.kadrXYWH[0],
                                          self.kadrXYWH[1]+448,self.kadrXYWH[2],self.kadrXYWH[3])) 
        elif (self.mFPS == self.animPlus):
            self.brushHero = None
            self.brushHero = graph.Sprite(0,0,self.filename,(self.kadrXYWH[0],
                                          self.kadrXYWH[1]+448+56,self.kadrXYWH[2],self.kadrXYWH[3])) 
        elif (self.mFPS == self.animPlus * 2):
            self.brushHero = None
            self.brushHero = graph.Sprite(0,0,self.filename,(self.kadrXYWH[0],
                                          self.kadrXYWH[1]+448+112,self.kadrXYWH[2],self.kadrXYWH[3])) 
        elif (self.mFPS == self.animPlus * 3):
            self.brushHero = None
            self.brushHero = graph.Sprite(0,0,self.filename,(self.kadrXYWH[0],
                                          self.kadrXYWH[1]+448+168,self.kadrXYWH[2],self.kadrXYWH[3])) 
    def DownAnimate(self):
        if  ((self.mFPS >= 0) and (self.mFPS < self.animPlus)):
            self.brushHero = None
            self.brushHero = graph.Sprite(0,0,self.filename,(self.kadrXYWH[0],
                                                             self.kadrXYWH[1],self.kadrXYWH[2],self.kadrXYWH[3])) 
        elif (self.mFPS == self.animPlus):
            self.brushHero = None
            self.brushHero = graph.Sprite(0,0,self.filename,(self.kadrXYWH[0],
                                                             self.kadrXYWH[1]+56,self.kadrXYWH[2],self.kadrXYWH[3])) 
        elif (self.mFPS == self.animPlus * 2):
            self.brushHero = None
            self.brushHero = graph.Sprite(0,0,self.filename,(self.kadrXYWH[0],
                                                             self.kadrXYWH[1]+112,self.kadrXYWH[2],self.kadrXYWH[3])) 
        elif (self.mFPS == self.animPlus * 3):
            self.brushHero = None
            self.brushHero = graph.Sprite(0,0,self.filename,(self.kadrXYWH[0],
                                                             self.kadrXYWH[1]+168,self.kadrXYWH[2],self.kadrXYWH[3])) 
    def render(self,screen):
        self.screen0 = screen
        self.brushHero.render(self.screen0)
    def renderXY(self,screen,xpos,ypos):
        self.screen0 = screen
        self.xpos = xpos
        self.ypos = ypos
        self.brushHero.renderXY(self.screen0,self.xpos,self.ypos)
        

