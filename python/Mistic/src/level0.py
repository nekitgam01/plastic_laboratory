# -*- coding: utf-8 -*-
"""Модуль 0 уровня"""

import pygame, sys, graph, window, gamepanel, gamemenu, hero, stepper,l0, menu

def gameRun(run, win, screen, sRGB = []): #| True/False | window | screen | (R,G,B)
    #Получаемые переменные
    screen0 = screen                                                         
    win0 = win                                                              
    gamePanel = pygame.Surface((800,48))                                     
    cGamePanel = gamepanel.GamePanel(gamePanel,112,112)
    cGamePanel.ShowHPMP = False
    cGamePanel.OnButton = False
    
    #Переменные
    mX = mY = 0 #Позиция мыши
    sX = sY = 0 #Позиция игрового экрана
    HP = 112
    MP = 112
    #
    scX = 0
    scY = 0
	#Определитель уровня
    room = 'menu'
    m_menu = menu.menu(win0, screen0, (111,111,111),mX,mY)
	
    #Уровень 1
    #level0 = l0.level0(win0, screen0, (111,111,111),mX,mY)
	


    
    '''Начало игрового цикла'''
    pygame.key.set_repeat(1,2) #Зажатие клавиши
    while run:
        """--------------------------------------------------------------------------------------------"""
        if (room == 'menu'):
            for e in pygame.event.get():
                if e.type == pygame.QUIT:
                    sys.exit()
                if e.type == pygame.KEYDOWN:
                    if e.key == pygame.K_F10:
                        sys.exit()
                    if e.key == pygame.K_F11:
                        pygame.display.toggle_fullscreen()
		        #Мышь
                if e.type == pygame.MOUSEMOTION:
                    pygame.mouse.set_visible(True)
                    m = pygame.mouse.get_pos()
                    mX = m[0]
                    mY = m[1]
                    if (((mX >=720) and (mX <=790)) and ((mY >=560) and (mY <=596))):
                        m_menu.button_start_active()
                    else:
                        m_menu.button_start_inactive()
                    if (((mX >=643) and (mX <=719)) and ((mY >=560) and (mY <=596))):
                        m_menu.button_exit_active()
                    else:
                        m_menu.button_exit_inactive()
		        #Нажатие
                if e.type == pygame.MOUSEBUTTONDOWN:
                    if e.button == 1: #Left
                        if (((mX >=720) and (mX <=790)) and ((mY >=560) and (mY <=596))):
                            #Если нажали на кнопку, загружаем уровень
                            level0 = l0.level0(win0, screen0, (111,111,111),mX,mY)
                            room = 'home'
                            m_menu = None
                        if (((mX >=643) and (mX <=719)) and ((mY >=560) and (mY <=596))):
                            print('Выход')
                            sys.exit()
        elif (room == 'home'):                
            '''Обработчик событий'''
	    #Выход из программы
            for e in pygame.event.get():
                if e.type == pygame.QUIT:
                    sys.exit()
                if e.type == pygame.KEYDOWN:
                    if e.key == pygame.K_F10:
                        sys.exit()
                    if e.key == pygame.K_F11:
                        pygame.display.toggle_fullscreen()
                    #Ходьба
                    if e.key == pygame.K_w:
                        if ((level0.KeyDownMap == 2) and (level0.KeyDownMap == 3) and (level0.KeyDownMap == 4)):
                            level0.KeyDownMap = 0
                        if level0.KeyDownMap == 0:
                            level0.nanami.UpStop()
                        if (level0.nanami.gY >=96):
                            level0.nanami.up_step = True
                            level0.KeyDownMap = 1
                    elif e.key == pygame.K_s:
                        if ((level0.KeyDownMap == 1) and (level0.KeyDownMap == 3) and (level0.KeyDownMap == 4)):
                            level0.KeyDownMap = 0
                        if level0.KeyDownMap == 0:
                            level0.nanami.DownStop()
                        if (level0.nanami.gY <= 338):
                            level0.nanami.down_step = True
                            level0.KeyDownMap = 2
                    elif e.key == pygame.K_a:
                        if ((level0.KeyDownMap == 1) and (level0.KeyDownMap == 2) and (level0.KeyDownMap == 4)):
                            level0.KeyDownMap = 0
                        if level0.KeyDownMap == 0:
                            level0.nanami.LeftStop()
                        if (level0.nanami.gX >= 142):
                            level0.nanami.left_step = True
                            level0.KeyDownMap = 3
                    elif e.key == pygame.K_d:
                        if ((level0.KeyDownMap == 1) and (level0.KeyDownMap == 2) and (level0.KeyDownMap == 3)):
                            level0.KeyDownMap = 0
                        if level0.KeyDownMap == 0:
                            level0.nanami.RightStop()
                        if (level0.nanami.gX <= 534):
                            level0.nanami.right_step = True
                            level0.KeyDownMap = 4
		            #Мышь
                if e.type == pygame.MOUSEMOTION:
                    pygame.mouse.set_visible(True)
                    m = pygame.mouse.get_pos()
                    mX = m[0]
                    mY = m[1]
                    cGamePanel.setMouseLoc(m[0],m[1])
                    #print('X:'+str(mX)+' Y:'+str(mY));
                    #555 0,800 230
                    if (((mX>=0)and(mX<=230)) and ((mY>=555)and(mY<=600))):
                        cGamePanel.ShowHPMP = True
                    else:
                        cGamePanel.ShowHPMP = False
                    if (((mX>=800-65)and(mX<=800-8)) and ((mY>=600-40)and(mY<=600-8))):
                        cGamePanel.OnButton = True
                    else:
                        cGamePanel.OnButton = False
		        #Нажатия мышью
                if e.type == pygame.MOUSEBUTTONDOWN:
                    if e.button == 1: #Left
                        if (((mX>=800-65)and(mX<=800-8)) and ((mY>=600-40)and(mY<=600-8))):
                            pause = gamemenu.GameMenu(True, win0, screen0,mX,mY)
                            room = 'pause'
                        #if e.button == 3: #Right
                            #scX -= 5
        elif (room == 'pause'):
            for e in pygame.event.get():
                #Выход из программы
                if e.type == pygame.QUIT:
                    sys.exit()
                #Мышь
                if e.type == pygame.MOUSEMOTION:
                    pygame.mouse.set_visible(True)
                    m = pygame.mouse.get_pos()
                    mX = m[0]
                    mY = m[1]
                #Нажатия мыши
                if e.type == pygame.MOUSEBUTTONDOWN:
                    if e.button == 1: #Left
                        room = 'home'
                        pause = None
                     
        """--------------------------------------------------------------------------------------------"""
        """Уровни"""
        if (room == 'home'):
            level0.render(mX,mY)
            """ОБъекты игровой панели"""
            cGamePanel.setHPMP(HP,MP)
            cGamePanel.render()
            if cGamePanel.ShowHPMP == True:
                cGamePanel.infoTableFonts()
            if cGamePanel.OnButton == True:
                cGamePanel.buttonExitSprite()
            win.blit(screen0,(scX,scY))
            win.blit(gamePanel,(0,552))
        elif (room == 'menu'):
            m_menu.render(mX,mY)
            win.blit(screen0,(scX,scY))
        elif (room == 'pause'):
            pause.render(mX,mY)
            win.blit(screen0,(scX,scY))
        pygame.display.flip()
        
