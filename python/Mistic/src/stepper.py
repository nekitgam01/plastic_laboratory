# -*- coding: utf-8 -*-
#Модуль отвечающий за ходьбу персонажа

def canvas_step(x1,y1,x2,y2,hero_xpos, hero_ypos):
	if ((hero_xpos >= x1) and (hero_xpos <= x2)) and ((hero_ypos >= y1) and (hero_ypos <= y2)):
		return True
	else:
		return False
	
	
