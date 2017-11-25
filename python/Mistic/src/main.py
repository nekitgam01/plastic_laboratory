"Модул  MAIN"

import window, os, pygame,level0

try:                   
    os.system('clear')  #Линукс
except KeyError:
    os.system('cls')    #Виндовс

win = window.createWindow(800,600,'Мистическая башня')
#screen = window.createScreen(800,600)
screen = pygame.Surface((800,600))

level0.gameRun(True,win,screen,(146,205,255))

