# -*- coding: utf-8 -*-
import pygame
'''Класс спрайта'''
class Sprite:
    def __init__(self,xpos,ypos,filename,kadrXYWH=[]):
        self.x=xpos
        self.y=ypos
        self.bitmap=pygame.image.load(filename);
        self.bitmap.set_colorkey((255,255,255))
        self.kadr = self.bitmap.subsurface(kadrXYWH[0],kadrXYWH[1],kadrXYWH[2],kadrXYWH[3])
    def renderXY(self,scrn,xpos,ypos):
        self.x = xpos
        self.y = ypos
        scrn.blit(self.kadr,(self.x,self.y))
    def render(self,scrn):
        scrn.blit(self.kadr,(self.x,self.y))
    def renderNewImageXY(self,scrn,xpos,ypos,filename,kadrXYWH=[]):
        self.x=xpos
        self.y=ypos
        self.bitmap=pygame.image.load(filename);
        self.bitmap.set_colorkey((255,255,255))
        self.kadr = self.bitmap.subsurface(kadrXYWH[0],kadrXYWH[1],kadrXYWH[2],kadrXYWH[3])
        scrn.blit(self.kadr,(self.x,self.y))
