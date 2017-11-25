# -*- coding: utf-8 -*-
import pygame

def createWindow(width,height,title):
    pygame.init()
    win = pygame.display.set_mode((width,height))
    pygame.display.set_caption((title));
    #pygame.display.toggle_fullscreen()
    return win

def createScreen(width,height):
    screen = pygame.Surface((width,height))
    return screen


    
