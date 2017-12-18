#ifndef _GRAPH_H_
#define _GRAPH_H_H

#include <SDL/SDL.h>
#include <string>

const char cCLEAR = 's';
const char cWHITE = 'W';
const char cBLACK = 'B';
const char cRED = 'r';
const char cGREEN = 'g';
const char cBLUE = 'b';
const char cGRAY = 'G';
const char cYELLOW = 'y';
const char cDRAK_GRAY = '0';
const char cMIN_GRAY = '1';
const char cNORM_GRAY = '2';
const char cDARK_RED = '3';
const char cMIN_RED = '4';
const char cNORM_RED = '5';
const char cDARK_GREEN = '6';
const char cMIN_GREEN = '7';
const char cNORM_GREEN = '8';
const char cDARK_BLUE = '9';
const char cMIN_BLUE = 'a';
const char cNORM_BLUE = 'c';
const char cDARK_YELLOW = 'd';
const char cMIN_YELLOW = 'e';
const char cNORM_YELLOW = 'f';
const char cDARK_CYAN = 'h';
const char cMIN_CYAN = 'k';
const char cNORM_CYAN = 'l';
const char cCYAN = 'm';
const char cDARK_ORANGE = 't';
const char cMIN_ORANGE = 'u';
const char cORANGE = 'v';
const char cDARK_PURPLE = 'n';
const char cMIN_PURPLE = 'o';
const char cNORM_PURPLE = 'p';
const char cPURPLE = 'q';

extern void DrawPixel(SDL_Surface *screen, int x, int y, Uint8 R, Uint8 G, Uint8 B);
extern void DrawPixel4(SDL_Surface *screen,int X, int Y, Uint8 R, Uint8 G, Uint8 B);
extern void DrawMatrixDeColor(SDL_Surface *screen,char cMatrix[][8],int X, int Y, char cFColor ,char NColor);
extern void DrawMatrix(SDL_Surface *screen,char cMatrix[][8],int X, int Y);
extern void DrawSym(SDL_Surface *screen,int lang, char sym,int x, int y, char color);
extern void DrawWord(SDL_Surface *screen,int lang, char* szText,int X, int Y, char color);


#endif
