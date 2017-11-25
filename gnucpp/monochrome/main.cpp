#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include <SDL/SDL.h>
#include <SDL/SDL_audio.h>
#include <iostream>
#include <string>

/*
#ifdef __linux__ 
    //linux code goes here
#elif _WIN32
    // windows code goes here
#else

#endif
*/
using namespace std;

//----------------------------FORWARD-----------------------------------
int Init();
void Events();
void Draw();
void DrawPixel(SDL_Surface *screen, int x, int y, Uint8 R, Uint8 G, Uint8 B);
void DrawPixel4(int X, int Y, Uint8 R, Uint8 G, Uint8 B);
void DrawXLine(int X, int Y, int X1, Uint8 R, Uint8 G, Uint8 B);
void DrawYLine(int X, int Y, int Y1, Uint8 R, Uint8 G, Uint8 B);
void DrawMatrixDeColor(char cMatrix[][8],int X, int Y, char cFColor ,char NColor);
void DrawMatrixDeColor(char cMatrix[][16],int X, int Y, char cFColor ,char NColor);
void DrawMatrixDeColor(char cMatrix[][32],int X, int Y, char cFColor ,char NColor);
void DrawMatrix(char cMatrix[][8],int X, int Y);
void DrawMatrix(char cMatrix[][16],int X, int Y);
void DrawMatrix(char cMatrix[][32],int X, int Y);
void DrawSym(int lang, char sym,int x, int y, char color);
void DrawWord(int lang, char* szText,int X, int Y, char color);
void MatrixDeColor(char cMatrix[][32], char cFColor ,char NColor);
void MatrixDeColor(char cMatrix[][16], char cFColor ,char NColor);
void MatrixDeColor(char cMatrix[][8], char cFColor ,char NColor);
void DeMultyColor(char cMatrix[][8],char fC0, char nc0, char fc1, char nc1);
void DeMultyColor(char cMatrix[][16],char fC0, char nc0, char fc1, char nc1);
void DeMultyColor(char cMatrix[][32],char fC0, char nc0, char fc1, char nc1);
void DeMultyColor(char cMatrix[][8],char fC0, char nc0, char fc1, char nc1, char fc2, char nc2);
void DeMultyColor(char cMatrix[][16],char fC0, char nc0, char fc1, char nc1, char fc2, char nc2);
void DeMultyColor(char cMatrix[][32],char fC0, char nc0, char fc1, char nc1, char fc2, char nc2);
void DeMultyColor(char cMatrix[][8],char fC0, char nc0, char fc1, 
					char nc1, char fc2, char nc2, char fC3, char nc3);
void DeMultyColor(char cMatrix[][8],char fC0, char nc0, char fc1, 
					char nc1, char fc2, char nc2, char fC3, char nc3, 
					char fc4, char nc4);
void DeMultyColor(char cMatrix[][16],char fC0, char nc0, char fc1, 
					char nc1, char fc2, char nc2, char fC3, char nc3);
void DeMultyColor(char cMatrix[][16],char fC0, char nc0, char fc1, 
					char nc1, char fc2, char nc2, char fC3, char nc3, 
					char fc4, char nc4);
void DeMultyColor(char cMatrix[][32],char fC0, char nc0, char fc1, 
					char nc1, char fc2, char nc2, char fC3, char nc3);
void DeMultyColor(char cMatrix[][32],char fC0, char nc0, char fc1, 
					char nc1, char fc2, char nc2, char fC3, char nc3, 
					char fc4, char nc4);
void DeMultyColor(char cMatrix[][8],char fC0, char nc0, char fc1, 
					char nc1, char fc2, char nc2, char fC3, char nc3, 
					char fc4, char nc4, char fc5, char nc5);
void DeMultyColor(char cMatrix[][16],char fC0, char nc0, char fc1, 
					char nc1, char fc2, char nc2, char fC3, char nc3, 
					char fc4, char nc4, char fc5, char nc5);
void DeMultyColor(char cMatrix[][32],char fC0, char nc0, char fc1, 
					char nc1, char fc2, char nc2, char fC3, char nc3, 
					char fc4, char nc4, char fc5, char nc5);
void DrawRect(int X, int Y, int X1, int Y1,Uint8 R, Uint8 G, Uint8 B);
void DrawFillRect(int X, int Y, int X1, int Y1, Uint8 R, Uint8 G, Uint8 B);



//--------------------------VARIABLES-----------------------------------
SDL_Surface* screen;
SDL_Event event;
bool done = false;

//--------------------------CONSTANTS-----------------------------------
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

//----------------------------CLASSES-----------------------------------

class Player{
	private:
		int X;
		int Y;
		int mode;
		char c32[32][32] = {
			{'s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s'},
			{'s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s'},
			{'s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s'},
			{'s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s'},
			{'s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s'},
			{'s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s'},
			{'s','s','s','s','s','s','s','s','k','k','s','s','l','k','l','s','s','k','k','s','s','s','s','s','s','s','s','s','s','s','s','s'},
			{'s','s','s','s','s','s','s','k','l','h','l','l','k','l','l','k','l','h','l','k','s','s','s','s','s','s','s','s','s','s','s','s'},
			{'s','s','s','s','s','s','s','l','h','l','k','l','k','l','k','l','k','l','h','l','s','s','s','s','s','s','s','s','s','s','s','s'},
			{'s','s','s','s','s','s','s','k','h','l','k','m','l','l','k','m','k','l','h','k','s','s','s','s','s','s','s','s','s','s','s','s'},
			{'s','s','s','s','s','s','s','l','h','m','k','n','u','m','l','n','k','m','h','l','s','s','s','s','s','s','s','s','s','s','s','s'},
			{'s','s','s','s','s','s','s','l','h','h','l','o','v','v','v','o','l','h','h','l','s','s','s','s','s','s','s','s','s','s','s','s'},
			{'s','s','s','s','s','s','s','k','l','h','u','v','v','v','v','v','u','h','l','k','s','s','s','s','s','s','s','s','s','s','s','s'},
			{'s','s','s','s','s','s','k','k','l','l','s','u','u','u','u','u','s','l','l','k','k','s','s','s','s','s','s','s','s','s','s','s'},
			{'s','s','s','s','s','s','s','l','k','s','v','2','v','v','v','2','v','s','k','l','s','s','s','s','s','s','s','s','s','s','s','s'},
			{'s','s','s','s','s','s','s','s','s','s','v','2','2','2','2','2','v','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s'},
			{'s','s','s','s','s','s','s','s','s','s','v','1','2','2','2','1','v','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s'},
			{'s','s','s','s','s','s','s','s','s','v','v','1','2','2','2','1','v','v','s','s','s','s','s','s','s','s','s','s','s','s','s','s'},
			{'s','s','s','s','s','s','s','s','s','a','1','0','2','2','2','0','1','a','s','s','s','s','s','s','s','s','s','s','s','s','s','s'},
			{'s','s','s','s','s','s','s','s','s','c','a','2','0','2','0','2','a','c','s','s','s','s','s','s','s','s','s','s','s','s','s','s'},
			{'s','s','s','s','s','s','s','s','s','s','c','a','c','a','c','a','c','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s'},
			{'s','s','s','s','s','s','s','s','s','s','s','v','v','s','v','v','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s'},
			{'s','s','s','s','s','s','s','s','s','s','s','0','0','s','0','0','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s'},
			{'s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s'},
			{'s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s'},
			{'s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s'},
			{'s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s'},
			{'s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s'},
			{'s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s'},
			{'s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s'},
			{'s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s'},
			{'s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s'}};
	public:
		Player()
		{
			mode = 0;
			DeMultyColor(c32,cNORM_CYAN,cMIN_RED,cMIN_CYAN,cRED,
						cDARK_CYAN,cDARK_RED,cCYAN,cNORM_RED,cMIN_BLUE,
						cMIN_RED,cNORM_BLUE,cNORM_RED);	
		}
		
		~Player(){}
		
		void SetPostion(int x, int y)
		{
			X = x;
			Y = y;
		}
		
		void SetMode(int Mode)
		{
			mode = Mode;
		}
		
		void Draw()
		{
			if (mode == 0)
			{
				DrawPixel4(X+1,Y,255,255,255);
				DrawPixel4(X+4,Y,255,255,255);
				
				DrawPixel4(X+2,Y+2,255,255,255);
				DrawPixel4(X+3,Y+2,255,255,255);
				
				DrawPixel4(X+1,Y+3,255,255,255);
				DrawPixel4(X+4,Y+3,255,255,255);
			} 
			else if (mode == 1)
			{
				DrawXLine(X+2,Y,X+5,100,100,100);
				DrawXLine(X+2,Y+1,X+5,100,100,100);
				DrawXLine(X+2,Y+2,X+5,100,100,100);
				
				DrawYLine(X+1,Y+1,Y+3,50,50,50);
				DrawYLine(X+6,Y+1,Y+3,50,50,50);
				
				DrawYLine(X,Y+3,Y+5,50,50,50);
				DrawYLine(X+7,Y+3,Y+5,50,50,50);
				
				DrawXLine(X+2,Y+3,X+5,255,255,255);
				DrawXLine(X+1,Y+4,X+6,255,255,255);
				DrawXLine(X+1,Y+5,X+6,255,255,255);
				
				DrawXLine(X,Y+6,X+7,255,255,255);
				
				DrawXLine(X,Y+7,X+2,255,255,255);
				DrawXLine(X+3,Y+7,X+4,0,0,0);
				DrawXLine(X+5,Y+7,X+7,255,255,255);
				
				DrawXLine(X,Y+8,X+2,255,255,255);
				DrawXLine(X+3,Y+8,X+4,0,0,0);
				DrawXLine(X+5,Y+8,X+7,255,255,255);
				
				DrawXLine(X,Y+9,X+2,255,255,255);
				DrawXLine(X+3,Y+9,X+4,0,0,0);
				DrawXLine(X+5,Y+9,X+7,255,255,255);
				
				DrawXLine(X,Y+10,X+7,255,255,255);
				
				DrawXLine(X+1,Y+11,X+6,255,255,255);
				DrawXLine(X+1,Y+12,X+6,255,255,255);
				
				DrawXLine(X+2,Y+13,X+5,255,255,255);
				
				DrawPixel4(X+1,Y+13,00,00,170);
				DrawPixel4(X,Y+14,00,00,170);
				DrawPixel4(X-1,Y+15,00,00,170);
				DrawYLine(X-1,Y+16,Y+18,00,00,170);

				DrawPixel4(X+6,Y+13,00,00,170);
				DrawPixel4(X+7,Y+14,00,00,170);
				DrawPixel4(X+8,Y+15,00,00,170);
				DrawYLine(X+8,Y+16,Y+18,00,00,170);
				

				DrawYLine(X-1,Y+10,Y+12,00,00,100);
				
				DrawYLine(X+8,Y+10,Y+12,00,00,100);

			}
			else if (mode == 2)
			{
				//DrawMatrixDeColor32(c32,10,10,'b','r');
				DrawMatrix(c32,10,10);
				
			}
			else if (mode == 3)
			{
				DrawMatrix(c32,10,10);
			}
		}
};
//----------------------------OBJECTS-----------------------------------
Player megu;

//----------------------------ROOMS-------------------------------------
class Rooms{
public:
	int nRoom;

	Rooms(){
		nRoom = 0;
	};
	~Rooms(){};

	void Draw(){
		if (nRoom == 0){ //Main Menu
			DrawWord(0,"Monochrome",159,4,cMIN_CYAN);
			DrawWord(0,"Monochrome",160,3,cWHITE);
			
			DrawWord(1,"Bxb? :bpym rjhjnrf!",5,120,cMIN_CYAN);
			DrawWord(1,"Bxb? :bpym rjhjnrf!",6,119,cWHITE);
			//DrawWord(1,"Monochrome",21,119,cWHITE);
			DrawRect(2,118,169,131,0,100,100);
			DrawRect(3,117,170,130,255,255,255);
			
			char selecter8[8][8] = {
					{'s','s','1','1','0','1','s','s'},
					{'s','2','2','0','2','1','1','s'},
					{'2','2','0','W','2','2','1','1'},
					{'2','4','r','4','W','2','1','1'},
					{'2','r','4','r','W','2','1','1'},
					{'2','2','0','W','2','2','1','1'},
					{'s','2','2','0','2','1','1','s'},
					{'s','s','1','1','0','1','s','s'}};
			DrawMatrix(selecter8,150,3);
			DrawMatrix(selecter8,230,3);
		}
		if (nRoom == 1){    //Ichi's password
			//Up-Down Window
			DrawXLine(115,90,285,0,100,150);
			DrawXLine(115,180,285,0,100,150);
			//Left-Right Window
			DrawYLine(112,93,177,0,100,150);
			DrawYLine(288,93,177,0,100,150);
			//Ramka
			DrawPixel4(114,91,0,100,150);
			DrawPixel4(113,92,0,100,150);
			DrawPixel4(286,91,0,100,150);
			DrawPixel4(287,92,0,100,150);
			DrawPixel4(114,179,0,100,150);
			DrawPixel4(113,178,0,100,150);
			DrawPixel4(286,179,0,100,150);
			DrawPixel4(287,178,0,100,150);
			//TextEdit
			DrawFillRect(120,115,280,130,0,50,70);
			DrawRect(120,115,280,130,0,100,150);
			//Label Please, auth
			DrawWord(1,"Ddtlbnt gfhjkm",120,100,cNORM_CYAN);
			//Label Hint
			DrawWord(1,"Tckb ds pfgecnbkb buhe dgthdst? ghjcnj yf;vbnt Ddjl!",
						5,285,cRED);
			//Button Ok
			DrawFillRect(230,145,280,160,0,50,70);
			DrawRect(230,145,280,160,255,255,255);
			DrawWord(1,"Jr",248,150,cNORM_CYAN);
		}
	};
};

Rooms rRooms;

//----------------------------DEFS--------------------------------------
void DrawPixel(SDL_Surface *screen, int x, int y, Uint8 R, Uint8 G, Uint8 B){ 
 Uint32 color = SDL_MapRGB(screen->format, R, G, B); 
 switch (screen->format->BytesPerPixel){ 
   case 1:  // Assuming 8-bpp 
   { 
     Uint8 *bufp; 
     bufp = (Uint8 *)screen->pixels + y*screen->pitch + x; *bufp = color; 
   } break; 
   case 2: // Probably 15-bpp or 16-bpp 
   { 
     Uint16 *bufp; 
     bufp = (Uint16 *)screen->pixels + y*screen->pitch/2 + x; *bufp = color; 
   } break; 
   case 3: // Slow 24-bpp mode, usually not used 
   { 
     Uint8 *bufp; 
     bufp = (Uint8 *)screen->pixels + y*screen->pitch + x * 3; 
     if(SDL_BYTEORDER == SDL_LIL_ENDIAN){ 
       bufp[0] = color; 
       bufp[1] = color >> 8; 
       bufp[2] = color >> 16; 
     }else{ 
       bufp[2] = color; 
       bufp[1] = color >> 8; 
       bufp[0] = color >> 16; 
     } 
   } break; 
   case 4: // Probably 32-bpp 
   { 
     Uint32 *bufp; 
     bufp = (Uint32 *)screen->pixels + y*screen->pitch/4 + x; 
     *bufp = color; 
   } break; 
 } 
}

void DrawPixel4(int X, int Y, Uint8 R, Uint8 G, Uint8 B){
	int x = X*2;
	int y = Y*2;
	DrawPixel(screen, x,y, R,G,B);
	DrawPixel(screen, x+1,y, R,G,B);
	DrawPixel(screen, x,y+1, R,G,B);
	DrawPixel(screen, x+1,y+1, R,G,B);
}

void DrawMatrixDeColor(char cMatrix[][8],int X, int Y, char cFColor ,char NColor){
	char cRead;
	int w = 8;
	int h = 8;
	for (int y=0;y<h;y++){
		for (int x=0;x<=w;x++){
			cRead = cMatrix[y][x];
			if (cRead=='s'){}
			else if(cRead==cFColor){
				cMatrix[y][x] = NColor;
			}
		}
	}
	DrawMatrix(cMatrix,X,Y);
}

void DrawMatrixDeColor(char cMatrix[][16],int X, int Y, char cFColor ,char NColor){
	char cRead;
	int w = 16;
	int h = 16;
	for (int y=0;y<h;y++){
		for (int x=0;x<=w;x++){
			cRead = cMatrix[y][x];
			if (cRead=='s'){}
			else if(cRead==cFColor){
				cMatrix[y][x] = NColor;
			}
		}
	}
	DrawMatrix(cMatrix,X,Y);
}

void MatrixDeColor(char cMatrix[][8], char cFColor ,char NColor){
	int w=8;
	int h=8;
	char cRead;
	for (int y=0;y<h;y++){
		for (int x=0;x<=w;x++){
			cRead = cMatrix[y][x];
			if (cRead=='s'){}
			else if(cRead==cFColor){
				cMatrix[y][x] = NColor;
			}
		}
	}
}

void MatrixDeColor(char cMatrix[][16], char cFColor ,char NColor){
	int w=16;
	int h=16;
	char cRead;
	for (int y=0;y<h;y++){
		for (int x=0;x<=w;x++){
			cRead = cMatrix[y][x];
			if (cRead=='s'){}
			else if(cRead==cFColor){
				cMatrix[y][x] = NColor;
			}
		}
	}
}

void MatrixDeColor(char cMatrix[][32], char cFColor ,char NColor){
	int w=32;
	int h=32;
	char cRead;
	for (int y=0;y<h;y++){
		for (int x=0;x<=w;x++){
			cRead = cMatrix[y][x];
			if (cRead=='s'){}
			else if(cRead==cFColor){
				cMatrix[y][x] = NColor;
			}
		}
	}
}

void DrawMatrixDeColor(char cMatrix[][32],int X, int Y, char cFColor ,char NColor){
	char cRead;
	int w = 32;
	int h = 32;
	for (int y=0;y<h;y++){
		for (int x=0;x<=w;x++){
			cRead = cMatrix[y][x];
			if (cRead=='s'){}
			else if(cRead==cFColor){
				cMatrix[y][x] = NColor;
			}
		}
	}
	DrawMatrix(cMatrix,X,Y);
}



void DrawMatrix(char cMatrix[][8],int X, int Y){
	char cRead;
	int w = 8;
	int h = 8;
	for (int y=0;y<h;y++){
		for (int x=0;x<w;x++){
			cRead = cMatrix[y][x];
			if (cRead=='s'){}
			else if(cRead=='r'){
				DrawPixel4(X+x, Y+y, 255, 0, 0);
			}
			else if(cRead=='g'){
				DrawPixel4(X+x, Y+y, 0, 255, 0);
			}
			else if(cRead=='b'){
				DrawPixel4(X+x, Y+y, 0, 0, 255);
			}
			else if(cRead=='W'){
				DrawPixel4(X+x, Y+y, 255, 255, 255);
			}
			else if(cRead=='B'){
				DrawPixel4(X+x, Y+y, 0, 0, 0);
			}
			else if(cRead=='G'){
				DrawPixel4(X+x, Y+y, 100, 100, 100);
			}
			else if(cRead=='0'){
				DrawPixel4(X+x, Y+y, 50, 50, 50);
			}
			else if(cRead=='1'){
				DrawPixel4(X+x, Y+y, 150, 150, 150);
			}
			else if(cRead=='2'){
				DrawPixel4(X+x, Y+y, 200, 200, 200);
			}
			else if(cRead=='3'){
				DrawPixel4(X+x, Y+y, 50, 0, 0);
			}
			else if(cRead=='4'){
				DrawPixel4(X+x, Y+y, 150, 0, 0);
			}
			else if(cRead=='5'){
				DrawPixel4(X+x, Y+y, 200, 0, 0);
			}
			else if(cRead=='6'){
				DrawPixel4(X+x, Y+y, 0, 50, 0);
			}
			else if(cRead=='7'){
				DrawPixel4(X+x, Y+y, 0, 150, 0);
			}
			else if(cRead=='8'){
				DrawPixel4(X+x, Y+y, 0, 200, 0);
			}
			else if(cRead=='9'){
				DrawPixel4(X+x, Y+y, 0, 0, 50);
			}
			else if(cRead=='a'){
				DrawPixel4(X+x, Y+y, 0, 0, 150);
			}
			else if(cRead=='c'){
				DrawPixel4(X+x, Y+y, 0, 0, 200);
			}
			else if(cRead=='y'){
				DrawPixel4(X+x, Y+y, 255, 255, 0);
			}
			else if(cRead=='d'){
				DrawPixel4(X+x, Y+y, 50, 50, 0);
			}
			else if(cRead=='e'){
				DrawPixel4(X+x, Y+y, 150, 150, 0);
			}
			else if(cRead=='f'){
				DrawPixel4(X+x, Y+y, 200, 200, 0);
			}
			else if(cRead=='h'){
				DrawPixel4(X+x, Y+y, 0, 50, 50);
			}
			else if(cRead=='k'){
				DrawPixel4(X+x, Y+y, 0, 150, 150);
			}
			else if(cRead=='l'){
				DrawPixel4(X+x, Y+y, 0, 200, 200);
			}
			else if(cRead=='m'){
				DrawPixel4(X+x, Y+y, 0, 255, 255);
			}
			else if(cRead=='n'){
				DrawPixel4(X+x, Y+y, 50, 0, 50);
			}
			else if(cRead=='o'){
				DrawPixel4(X+x, Y+y, 150, 0, 150);
			}
			else if(cRead=='p'){
				DrawPixel4(X+x, Y+y, 200, 0, 200);
			}
			else if(cRead=='q'){
				DrawPixel4(X+x, Y+y, 255, 0, 255);
			}
			else if(cRead=='t'){
				DrawPixel4(X+x, Y+y, 100, 50, 0);
			}
			else if(cRead=='u'){
				DrawPixel4(X+x, Y+y, 200, 150, 0);
			}
			else if(cRead=='v'){
				DrawPixel4(X+x, Y+y, 255, 200, 0);
			}
		}
	}
}

void DrawMatrix(char cMatrix[][16],int X, int Y){
	char cRead;
	int w = 16;
	int h = 16;
	for (int y=0;y<h;y++){
		for (int x=0;x<=w;x++){
			cRead = cMatrix[y][x];
			if (cRead=='s'){}
			else if(cRead=='r'){
				DrawPixel4(X+x, Y+y, 255, 0, 0);
			}
			else if(cRead=='g'){
				DrawPixel4(X+x, Y+y, 0, 255, 0);
			}
			else if(cRead=='b'){
				DrawPixel4(X+x, Y+y, 0, 0, 255);
			}
			else if(cRead=='W'){
				DrawPixel4(X+x, Y+y, 255, 255, 255);
			}
			else if(cRead=='B'){
				DrawPixel4(X+x, Y+y, 0, 0, 0);
			}
			else if(cRead=='G'){
				DrawPixel4(X+x, Y+y, 100, 100, 100);
			}
			else if(cRead=='0'){
				DrawPixel4(X+x, Y+y, 50, 50, 50);
			}
			else if(cRead=='1'){
				DrawPixel4(X+x, Y+y, 150, 150, 150);
			}
			else if(cRead=='2'){
				DrawPixel4(X+x, Y+y, 200, 200, 200);
			}
			else if(cRead=='3'){
				DrawPixel4(X+x, Y+y, 50, 0, 0);
			}
			else if(cRead=='4'){
				DrawPixel4(X+x, Y+y, 150, 0, 0);
			}
			else if(cRead=='5'){
				DrawPixel4(X+x, Y+y, 200, 0, 0);
			}
			else if(cRead=='6'){
				DrawPixel4(X+x, Y+y, 0, 50, 0);
			}
			else if(cRead=='7'){
				DrawPixel4(X+x, Y+y, 0, 150, 0);
			}
			else if(cRead=='8'){
				DrawPixel4(X+x, Y+y, 0, 200, 0);
			}
			else if(cRead=='9'){
				DrawPixel4(X+x, Y+y, 0, 0, 50);
			}
			else if(cRead=='a'){
				DrawPixel4(X+x, Y+y, 0, 0, 150);
			}
			else if(cRead=='c'){
				DrawPixel4(X+x, Y+y, 0, 0, 200);
			}
			else if(cRead=='y'){
				DrawPixel4(X+x, Y+y, 255, 255, 0);
			}
			else if(cRead=='d'){
				DrawPixel4(X+x, Y+y, 50, 50, 0);
			}
			else if(cRead=='e'){
				DrawPixel4(X+x, Y+y, 150, 150, 0);
			}
			else if(cRead=='f'){
				DrawPixel4(X+x, Y+y, 200, 200, 0);
			}
			else if(cRead=='h'){
				DrawPixel4(X+x, Y+y, 0, 50, 50);
			}
			else if(cRead=='k'){
				DrawPixel4(X+x, Y+y, 0, 150, 150);
			}
			else if(cRead=='l'){
				DrawPixel4(X+x, Y+y, 0, 200, 200);
			}
			else if(cRead=='m'){
				DrawPixel4(X+x, Y+y, 0, 255, 255);
			}
			else if(cRead=='n'){
				DrawPixel4(X+x, Y+y, 50, 0, 50);
			}
			else if(cRead=='o'){
				DrawPixel4(X+x, Y+y, 150, 0, 150);
			}
			else if(cRead=='p'){
				DrawPixel4(X+x, Y+y, 200, 0, 200);
			}
			else if(cRead=='q'){
				DrawPixel4(X+x, Y+y, 255, 0, 255);
			}
			else if(cRead=='t'){
				DrawPixel4(X+x, Y+y, 100, 50, 0);
			}
			else if(cRead=='u'){
				DrawPixel4(X+x, Y+y, 200, 150, 0);
			}
			else if(cRead=='v'){
				DrawPixel4(X+x, Y+y, 255, 200, 0);
			}
		}
	}
}

void DrawMatrix(char cMatrix[][32],int X, int Y){
	char cRead;
	int w = 32;
	int h = 32;
	for (int y=0;y<h;y++){
		for (int x=0;x<=w;x++){
			cRead = cMatrix[y][x];
			if (cRead=='s'){}
			else if(cRead=='r'){
				DrawPixel4(X+x, Y+y, 255, 0, 0);
			}
			else if(cRead=='g'){
				DrawPixel4(X+x, Y+y, 0, 255, 0);
			}
			else if(cRead=='b'){
				DrawPixel4(X+x, Y+y, 0, 0, 255);
			}
			else if(cRead=='W'){
				DrawPixel4(X+x, Y+y, 255, 255, 255);
			}
			else if(cRead=='B'){
				DrawPixel4(X+x, Y+y, 0, 0, 0);
			}
			else if(cRead=='G'){
				DrawPixel4(X+x, Y+y, 100, 100, 100);
			}
			else if(cRead=='0'){
				DrawPixel4(X+x, Y+y, 50, 50, 50);
			}
			else if(cRead=='1'){
				DrawPixel4(X+x, Y+y, 150, 150, 150);
			}
			else if(cRead=='2'){
				DrawPixel4(X+x, Y+y, 200, 200, 200);
			}
			else if(cRead=='3'){
				DrawPixel4(X+x, Y+y, 50, 0, 0);
			}
			else if(cRead=='4'){
				DrawPixel4(X+x, Y+y, 150, 0, 0);
			}
			else if(cRead=='5'){
				DrawPixel4(X+x, Y+y, 200, 0, 0);
			}
			else if(cRead=='6'){
				DrawPixel4(X+x, Y+y, 0, 50, 0);
			}
			else if(cRead=='7'){
				DrawPixel4(X+x, Y+y, 0, 150, 0);
			}
			else if(cRead=='8'){
				DrawPixel4(X+x, Y+y, 0, 200, 0);
			}
			else if(cRead=='9'){
				DrawPixel4(X+x, Y+y, 0, 0, 50);
			}
			else if(cRead=='a'){
				DrawPixel4(X+x, Y+y, 0, 0, 150);
			}
			else if(cRead=='c'){
				DrawPixel4(X+x, Y+y, 0, 0, 200);
			}
			else if(cRead=='y'){
				DrawPixel4(X+x, Y+y, 255, 255, 0);
			}
			else if(cRead=='d'){
				DrawPixel4(X+x, Y+y, 50, 50, 0);
			}
			else if(cRead=='e'){
				DrawPixel4(X+x, Y+y, 150, 150, 0);
			}
			else if(cRead=='f'){
				DrawPixel4(X+x, Y+y, 200, 200, 0);
			}
			else if(cRead=='h'){
				DrawPixel4(X+x, Y+y, 0, 50, 50);
			}
			else if(cRead=='k'){
				DrawPixel4(X+x, Y+y, 0, 150, 150);
			}
			else if(cRead=='l'){
				DrawPixel4(X+x, Y+y, 0, 200, 200);
			}
			else if(cRead=='m'){
				DrawPixel4(X+x, Y+y, 0, 255, 255);
			}
			else if(cRead=='n'){
				DrawPixel4(X+x, Y+y, 50, 0, 50);
			}
			else if(cRead=='o'){
				DrawPixel4(X+x, Y+y, 150, 0, 150);
			}
			else if(cRead=='p'){
				DrawPixel4(X+x, Y+y, 200, 0, 200);
			}
			else if(cRead=='q'){
				DrawPixel4(X+x, Y+y, 255, 0, 255);
			}
			else if(cRead=='t'){
				DrawPixel4(X+x, Y+y, 100, 50, 0);
			}
			else if(cRead=='u'){
				DrawPixel4(X+x, Y+y, 200, 150, 0);
			}
			else if(cRead=='v'){
				DrawPixel4(X+x, Y+y, 255, 200, 0);
			}
		}
	}
}

void DrawXLine(int X, int Y, int X1, Uint8 R, Uint8 G, Uint8 B){
	for (int i = X;i<=X1;i++){
		DrawPixel4(i,Y, R,G,B);
	}
}

void DrawYLine(int X, int Y, int Y1, Uint8 R, Uint8 G, Uint8 B){
	for (int i = Y;i<=Y1;i++){
		DrawPixel4(X,i, R,G,B);
	}
}

void DrawWord(int lang, char* szText,int X, int Y, char color){
	char rc;
	for (int i = 0;i<strlen(szText);i++){
		rc = szText[i];
		DrawSym(lang,rc,X+(i*7),Y,color);
	}
}

void DeMultyColor(char cMatrix[][8],char fC0, char nc0, char fc1, char nc1){
	MatrixDeColor(cMatrix, fC0 ,nc0);
	MatrixDeColor(cMatrix, fc1 ,nc1);
}

void DeMultyColor(char cMatrix[][16],char fC0, char nc0, char fc1, char nc1){
	MatrixDeColor(cMatrix, fC0 ,nc0);
	MatrixDeColor(cMatrix, fc1 ,nc1);
}

void DeMultyColor(char cMatrix[][32],char fC0, char nc0, char fc1, char nc1){
	MatrixDeColor(cMatrix, fC0 ,nc0);
	MatrixDeColor(cMatrix, fc1 ,nc1);
}


void DeMultyColor(char cMatrix[][8],char fC0, char nc0, char fc1, char nc1, char fc2, char nc2){
	MatrixDeColor(cMatrix, fC0 ,nc0);
	MatrixDeColor(cMatrix, fc1 ,nc1);
	MatrixDeColor(cMatrix, fc2 ,nc2);
}

void DeMultyColor(char cMatrix[][16],char fC0, char nc0, char fc1, char nc1, char fc2, char nc2){
	MatrixDeColor(cMatrix, fC0 ,nc0);
	MatrixDeColor(cMatrix, fc1 ,nc1);
	MatrixDeColor(cMatrix, fc2 ,nc2);
}

void DeMultyColor(char cMatrix[][32],char fC0, char nc0, char fc1, char nc1, char fc2, char nc2){
	MatrixDeColor(cMatrix, fC0 ,nc0);
	MatrixDeColor(cMatrix, fc1 ,nc1);
	MatrixDeColor(cMatrix, fc2 ,nc2);
}

void DeMultyColor(char cMatrix[][8],char fC0, char nc0, char fc1, 
					char nc1, char fc2, char nc2, char fC3, char nc3){
	MatrixDeColor(cMatrix, fC0 ,nc0);
	MatrixDeColor(cMatrix, fc1 ,nc1);
	MatrixDeColor(cMatrix, fc2 ,nc2);
	MatrixDeColor(cMatrix, fC3 ,nc3);
}

void DeMultyColor(char cMatrix[][16],char fC0, char nc0, char fc1, 
					char nc1, char fc2, char nc2, char fC3, char nc3){
	MatrixDeColor(cMatrix, fC0 ,nc0);
	MatrixDeColor(cMatrix, fc1 ,nc1);
	MatrixDeColor(cMatrix, fc2 ,nc2);
	MatrixDeColor(cMatrix, fC3 ,nc3);
}

void DeMultyColor(char cMatrix[][32],char fC0, char nc0, char fc1, 
					char nc1, char fc2, char nc2, char fC3, char nc3){
	MatrixDeColor(cMatrix, fC0 ,nc0);
	MatrixDeColor(cMatrix, fc1 ,nc1);
	MatrixDeColor(cMatrix, fc2 ,nc2);
	MatrixDeColor(cMatrix, fC3 ,nc3);
}

void DeMultyColor(char cMatrix[][8],char fC0, char nc0, char fc1, 
					char nc1, char fc2, char nc2, char fC3, char nc3, 
					char fc4, char nc4){
	MatrixDeColor(cMatrix, fC0 ,nc0);
	MatrixDeColor(cMatrix, fc1 ,nc1);
	MatrixDeColor(cMatrix, fc2 ,nc2);
	MatrixDeColor(cMatrix, fC3 ,nc3);
	MatrixDeColor(cMatrix, fc4 ,nc4);
}

void DeMultyColor(char cMatrix[][16],char fC0, char nc0, char fc1, 
					char nc1, char fc2, char nc2, char fC3, char nc3, 
					char fc4, char nc4){
	MatrixDeColor(cMatrix, fC0 ,nc0);
	MatrixDeColor(cMatrix, fc1 ,nc1);
	MatrixDeColor(cMatrix, fc2 ,nc2);
	MatrixDeColor(cMatrix, fC3 ,nc3);
	MatrixDeColor(cMatrix, fc4 ,nc4);
}

void DeMultyColor(char cMatrix[][32],char fC0, char nc0, char fc1, 
					char nc1, char fc2, char nc2, char fC3, char nc3, 
					char fc4, char nc4){
	MatrixDeColor(cMatrix, fC0 ,nc0);
	MatrixDeColor(cMatrix, fc1 ,nc1);
	MatrixDeColor(cMatrix, fc2 ,nc2);
	MatrixDeColor(cMatrix, fC3 ,nc3);
	MatrixDeColor(cMatrix, fc4 ,nc4);
}

void DeMultyColor(char cMatrix[][8],char fC0, char nc0, char fc1, 
					char nc1, char fc2, char nc2, char fC3, char nc3, 
					char fc4, char nc4, char fc5, char nc5){
	MatrixDeColor(cMatrix, fC0 ,nc0);
	MatrixDeColor(cMatrix, fc1 ,nc1);
	MatrixDeColor(cMatrix, fc2 ,nc2);
	MatrixDeColor(cMatrix, fC3 ,nc3);
	MatrixDeColor(cMatrix, fc4 ,nc4);
	MatrixDeColor(cMatrix, fc5 ,nc5);
}

void DeMultyColor(char cMatrix[][16],char fC0, char nc0, char fc1, 
					char nc1, char fc2, char nc2, char fC3, char nc3, 
					char fc4, char nc4, char fc5, char nc5){
	MatrixDeColor(cMatrix, fC0 ,nc0);
	MatrixDeColor(cMatrix, fc1 ,nc1);
	MatrixDeColor(cMatrix, fc2 ,nc2);
	MatrixDeColor(cMatrix, fC3 ,nc3);
	MatrixDeColor(cMatrix, fc4 ,nc4);
	MatrixDeColor(cMatrix, fc5 ,nc5);
}

void DeMultyColor(char cMatrix[][32],char fC0, char nc0, char fc1, 
					char nc1, char fc2, char nc2, char fC3, char nc3, 
					char fc4, char nc4, char fc5, char nc5){
	MatrixDeColor(cMatrix, fC0 ,nc0);
	MatrixDeColor(cMatrix, fc1 ,nc1);
	MatrixDeColor(cMatrix, fc2 ,nc2);
	MatrixDeColor(cMatrix, fC3 ,nc3);
	MatrixDeColor(cMatrix, fc4 ,nc4);
	MatrixDeColor(cMatrix, fc5 ,nc5);
}

void DrawSym(int lang, char sym,int x, int y, char color){
	if (lang==0){
		switch(sym){
			case 'A':{char cSym[8][8]={
						{'s','s','s','W','s','s','s','s'},
						{'s','s','W','s','W','s','s','s'},
						{'s','s','W','s','W','s','s','s'},
						{'s','W','s','s','s','W','s','s'},
						{'s','W','W','W','W','W','s','s'},
						{'s','W','s','s','s','W','s','s'},
						{'s','W','s','s','s','W','s','s'},
						{'s','W','s','s','s','W','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'B':{char cSym[8][8]={
						{'s','W','W','W','W','s','s','s'},
						{'s','W','s','s','s','W','s','s'},
						{'s','W','s','s','s','W','s','s'},
						{'s','W','s','W','W','s','s','s'},
						{'s','W','s','W','W','s','s','s'},
						{'s','W','s','s','s','W','s','s'},
						{'s','W','s','s','s','W','s','s'},
						{'s','W','W','W','W','s','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'C':{char cSym[8][8]={
						{'s','s','s','W','W','s','s','s'},
						{'s','s','W','s','s','W','s','s'},
						{'s','W','s','s','s','s','s','s'},
						{'s','W','s','s','s','s','s','s'},
						{'s','W','s','s','s','s','s','s'},
						{'s','W','s','s','s','s','s','s'},
						{'s','s','W','s','s','W','s','s'},
						{'s','s','s','W','W','s','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'D':{char cSym[8][8]={
						{'s','W','W','W','s','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','W','s','s','s','W','s'},
						{'s','W','s','s','s','W','s'},
						{'s','W','s','s','s','W','s'},
						{'s','W','s','s','s','W','s'},
						{'s','W','s','s','W','s','s'},
						{'s','W','W','W','s','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'E':{char cSym[8][8]={
						{'s','W','W','W','W','W','s'},
						{'s','W','s','s','s','s','s'},
						{'s','W','s','s','s','s','s'},
						{'s','W','W','W','W','W','s'},
						{'s','W','s','s','s','s','s'},
						{'s','W','s','s','s','s','s'},
						{'s','W','s','s','s','s','s'},
						{'s','W','W','W','W','W','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'F':{char cSym[8][8]={
						{'s','W','W','W','W','W','s'},
						{'s','W','s','s','s','s','s'},
						{'s','W','s','s','s','s','s'},
						{'s','W','W','W','W','W','s'},
						{'s','W','s','s','s','s','s'},
						{'s','W','s','s','s','s','s'},
						{'s','W','s','s','s','s','s'},
						{'s','W','s','s','s','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'G':{char cSym[8][8]={
						{'s','s','s','W','W','W','s','s'},
						{'s','s','W','s','s','s','W','s'},
						{'s','W','s','s','s','s','s','s'},
						{'s','W','s','s','s','s','s','s'},
						{'s','W','s','s','W','W','W','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','s','W','s','s','s','W','s'},
						{'s','s','s','W','W','W','s','s'}};

				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'H':{char cSym[8][8]={
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','W','W','W','W','W','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','s','W','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'I':{char cSym[8][8]={
						{'s','W','W','W','W','W','s','s'},
						{'s','s','s','W','s','s','s','s'},
						{'s','s','s','W','s','s','s','s'},
						{'s','s','s','W','s','s','s','s'},
						{'s','s','s','W','s','s','s','s'},
						{'s','s','s','W','s','s','s','s'},
						{'s','s','s','W','s','s','s','s'},
						{'s','W','W','W','W','W','s','s'}};

				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'J':{char cSym[8][8]={
						{'s','W','W','W','s','s','s','s'},
						{'s','s','W','s','s','s','s','s'},
						{'s','s','W','s','s','s','s','s'},
						{'s','s','W','s','s','s','s','s'},
						{'s','s','W','s','s','s','s','s'},
						{'s','s','W','s','s','s','s','s'},
						{'s','s','W','s','s','s','s','s'},
						{'s','W','s','s','s','s','s','s'}};


				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'K':{char cSym[8][8]={
						{'s','W','W','W','s','s','W','s'},
						{'s','s','W','s','s','W','s','s'},
						{'s','s','W','s','W','s','s','s'},
						{'s','s','W','W','s','s','s','s'},
						{'s','s','W','W','s','s','s','s'},
						{'s','s','W','s','W','s','s','s'},
						{'s','s','W','s','s','W','s','s'},
						{'s','W','W','W','s','s','W','s'}};

				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'L':{char cSym[8][8]={
						{'s','W','W','W','s','s','s','s'},
						{'s','s','W','s','s','s','s','s'},
						{'s','s','W','s','s','s','s','s'},
						{'s','s','W','s','s','s','s','s'},
						{'s','s','W','s','s','s','s','s'},
						{'s','s','W','s','s','s','s','s'},
						{'s','s','W','s','s','s','s','s'},
						{'s','W','W','W','W','W','W','s'}};

				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'M':{char cSym[8][8]={
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','W','s','s','W','W','s'},
						{'s','W','s','W','W','s','W','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','s','W','s'}};

				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'N':{char cSym[8][8]={
						{'s','W','s','s','s','s','W','s'},
						{'s','W','W','s','s','s','W','s'},
						{'s','W','s','W','s','s','W','s'},
						{'s','W','s','s','W','s','W','s'},
						{'s','W','s','s','s','W','W','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','s','W','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'O':{char cSym[8][8]={
						{'s','s','s','W','W','s','s','s'},
						{'s','s','W','s','s','W','s','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','s','W','s','s','W','s','s'},
						{'s','s','s','W','W','s','s','s'}};

				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'P':{char cSym[8][8]={
						{'s','W','W','W','W','s','s','s'},
						{'s','W','s','s','s','W','s','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','W','s','s'},
						{'s','W','W','W','W','s','s','s'},
						{'s','W','s','s','s','s','s','s'},
						{'s','W','s','s','s','s','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'Q':{char cSym[8][8]={
						{'s','s','s','W','W','s','s','s'},
						{'s','s','W','s','s','W','s','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','s','W','s','s','W','s','s'},
						{'s','s','s','W','W','s','W','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'R':{char cSym[8][8]={
						{'s','W','W','W','W','s','s','s'},
						{'s','W','s','s','s','W','s','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','W','s','s'},
						{'s','W','W','W','W','s','s','s'},
						{'s','W','s','s','s','W','s','s'},
						{'s','W','s','s','s','s','W','s'}};

				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'S':{char cSym[8][8]={
						{'s','s','W','W','W','s','s'},
						{'s','W','s','s','s','W','s'},
						{'s','W','s','s','s','s','s'},
						{'s','s','W','W','W','s','s'},
						{'s','s','s','s','s','W','s'},
						{'s','s','s','s','s','W','s'},
						{'s','W','s','s','s','W','s'},
						{'s','s','W','W','W','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'T':{char cSym[8][8]={
						{'s','W','W','W','W','W','s','s'},
						{'s','W','s','W','s','W','s','s'},
						{'s','s','s','W','s','s','s','s'},
						{'s','s','s','W','s','s','s','s'},
						{'s','s','s','W','s','s','s','s'},
						{'s','s','s','W','s','s','s','s'},
						{'s','s','s','W','s','s','s','s'},
						{'s','s','W','W','W','s','s','s'}};

				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'U':{char cSym[8][8]={
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','s','W','W','W','W','s','s'}};

				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'V':{char cSym[8][8]={
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','s','W','s','s','W','s','s'},
						{'s','s','s','W','W','s','s','s'}};

				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'W':{char cSym[8][8]={
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','W','W','s','W','s'},
						{'s','s','W','s','s','W','s','s'}};

				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'X':{char cSym[8][8]={
						{'s','W','s','s','s','s','W','s'},
						{'s','s','W','s','s','W','s','s'},
						{'s','s','W','s','s','W','s','s'},
						{'s','s','s','W','W','s','s','s'},
						{'s','s','s','W','W','s','s','s'},
						{'s','s','W','s','s','W','s','s'},
						{'s','s','W','s','s','W','s','s'},
						{'s','W','s','s','s','s','W','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'Y':{char cSym[8][8]={
						{'s','W','s','s','s','W','s','s'},
						{'s','W','s','s','s','W','s','s'},
						{'s','W','s','s','s','W','s','s'},
						{'s','s','W','s','W','s','s','s'},
						{'s','s','s','W','s','s','s','s'},
						{'s','s','s','W','s','s','s','s'},
						{'s','s','s','W','s','s','s','s'},
						{'s','s','s','W','s','s','s','s'}};

				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'Z':{char cSym[8][8]={
						{'s','W','W','W','W','W','W','s'},
						{'s','s','s','s','s','s','W','s'},
						{'s','s','s','s','s','W','s','s'},
						{'s','s','s','s','W','s','s','s'},
						{'s','s','s','W','s','s','s','s'},
						{'s','s','W','s','s','s','s','s'},
						{'s','W','s','s','s','s','s','s'},
						{'s','W','W','W','W','W','W','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'a':{char cSym[8][8]={
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','W','W','W','s','s','s'},
						{'s','s','s','s','W','s','s'},
						{'s','s','W','W','W','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','s','W','W','s','W','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'b':{char cSym[8][8]={
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','W','W','W','s','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','W','W','W','s','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','W','W','W','s','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'c':{char cSym[8][8]={
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','s','W','W','s','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','W','s','s','s','s','s'},
						{'s','W','s','s','s','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','s','W','W','s','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'd':{char cSym[8][8]={
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','W','s','s'},
						{'s','s','W','W','W','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','s','W','W','W','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'e':{char cSym[8][8]={
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','s','W','W','s','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','W','W','W','s','s','s'},
						{'s','W','s','s','s','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','s','W','W','s','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'f':{char cSym[8][8]={
						{'s','s','s','s','s','s','s'},
						{'s','s','s','W','s','s','s'},
						{'s','s','W','s','s','s','s'},
						{'s','s','W','s','s','s','s'},
						{'s','W','W','W','s','s','s'},
						{'s','s','W','s','s','s','s'},
						{'s','s','W','s','s','s','s'},
						{'s','s','W','s','s','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'g':{char cSym[8][8]={
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','s','W','W','s','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','W','s','s','s','s','s'},
						{'s','W','s','W','W','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','s','W','W','s','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'h':{char cSym[8][8]={
						{'s','s','s','s','s','s','s'},
						{'s','W','s','s','s','s','s'},
						{'s','W','s','s','s','s','s'},
						{'s','W','W','W','s','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','W','s','s','W','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'i':{char cSym[8][8]={
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','s','s','W','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','s','s','W','s','s','s'},
						{'s','s','s','W','s','s','s'},
						{'s','s','s','W','s','s','s'},
						{'s','s','s','W','s','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'j':{char cSym[8][8]={
						{'s','s','s','W','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','s','s','W','s','s','s'},
						{'s','s','s','W','s','s','s'},
						{'s','s','s','W','s','s','s'},
						{'s','s','s','W','s','s','s'},
						{'s','s','s','W','s','s','s'},
						{'s','s','W','s','s','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'k':{char cSym[8][8]={
						{'s','s','s','s','s','s','s'},
						{'s','W','s','s','s','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','W','s','W','s','s','s'},
						{'s','W','W','s','s','s','s'},
						{'s','W','s','W','s','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','W','s','s','W','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'l':{char cSym[8][8]={
						{'s','s','s','s','s','s','s'},
						{'s','s','W','W','s','s','s'},
						{'s','s','s','W','s','s','s'},
						{'s','s','s','W','s','s','s'},
						{'s','s','s','W','s','s','s'},
						{'s','s','s','W','s','s','s'},
						{'s','s','s','W','s','s','s'},
						{'s','s','s','s','W','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'm':{char cSym[8][8]={
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','W','W','s','W','s','s'},
						{'s','W','s','W','s','W','s'},
						{'s','W','s','W','s','W','s'},
						{'s','W','s','W','s','W','s'},
						{'s','W','s','W','s','W','s'},
						{'s','W','s','W','s','W','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);;
			} break;
			case 'n':{char cSym[8][8]={
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','W','W','W','s','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','W','s','s','W','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'o':{char cSym[8][8]={
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','s','W','W','s','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','s','W','W','s','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'p':{char cSym[8][8]={
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','W','W','W','s','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','W','W','W','s','s','s'},
						{'s','W','s','s','s','s','s'},
						{'s','W','s','s','s','s','s'},
						{'s','W','s','s','s','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'q':{char cSym[8][8]={
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','s','W','W','s','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','s','W','W','s','W','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'r':{char cSym[8][8]={
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','s','W','W','s','s','s'},
						{'s','s','W','s','W','s','s'},
						{'s','s','W','W','s','s','s'},
						{'s','s','W','W','s','s','s'},
						{'s','s','W','s','W','s','s'},
						{'s','s','W','s','W','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 's':{char cSym[8][8]={
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','s','W','W','W','s','s'},
						{'s','W','s','s','s','s','s'},
						{'s','s','W','W','s','s','s'},
						{'s','s','s','s','W','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','s','W','W','s','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 't':{char cSym[8][8]={
						{'s','s','s','s','s','s','s'},
						{'s','s','W','s','s','s','s'},
						{'s','s','W','s','s','s','s'},
						{'s','W','W','W','s','s','s'},
						{'s','s','W','s','s','s','s'},
						{'s','s','W','s','s','s','s'},
						{'s','s','W','s','s','s','s'},
						{'s','s','s','W','s','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'u':{char cSym[8][8]={
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','W','s','s','s','W','s'},
						{'s','W','s','s','s','W','s'},
						{'s','W','s','s','s','W','s'},
						{'s','W','s','s','s','W','s'},
						{'s','W','s','s','s','W','s'},
						{'s','s','W','W','W','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'v':{char cSym[8][8]={
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','W','s','s','s','W','s'},
						{'s','W','s','s','s','W','s'},
						{'s','W','s','s','s','W','s'},
						{'s','s','W','s','W','s','s'},
						{'s','s','W','s','W','s','s'},
						{'s','s','s','W','s','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'w':{char cSym[8][8]={
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','W','s','s','s','W','s'},
						{'s','W','s','s','s','W','s'},
						{'s','W','s','s','s','W','s'},
						{'s','W','s','W','s','W','s'},
						{'s','W','s','W','s','W','s'},
						{'s','s','W','s','W','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'x':{char cSym[8][8]={
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','W','s','s','s','W','s'},
						{'s','s','W','s','W','s','s'},
						{'s','s','s','W','s','s','s'},
						{'s','s','W','s','W','s','s'},
						{'s','W','s','s','s','W','s'},
						{'s','W','s','s','s','W','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'y':{char cSym[8][8]={
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','W','s','s','s','W','s'},
						{'s','s','W','s','W','s','s'},
						{'s','s','s','W','s','s','s'},
						{'s','s','s','W','s','s','s'},
						{'s','s','s','W','s','s','s'},
						{'s','s','s','W','s','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'z':{char cSym[8][8]={
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','W','W','W','W','s','s'},
						{'s','s','s','s','W','s','s'},
						{'s','s','s','W','s','s','s'},
						{'s','s','W','s','s','s','s'},
						{'s','W','s','s','s','s','s'},
						{'s','W','W','W','W','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case ':':{char cSym[8][8]={
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','s','W','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','s','W','s','s','s','s'},
						{'s','s','s','s','s','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case '-':{char cSym[8][8]={
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','W','W','W','W','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case '+':{char cSym[8][8]={
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','s','s','W','s','s','s'},
						{'s','s','s','W','s','s','s'},
						{'s','W','W','W','W','W','s'},
						{'s','s','s','W','s','s','s'},
						{'s','s','s','W','s','s','s'},
						{'s','s','s','s','s','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case '=':{char cSym[8][8]={
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','W','W','W','W','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','W','W','W','W','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case ' ':{char cSym[8][8]={
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case '.':{char cSym[8][8]={
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','s','W','s','s','s','s'},
						{'s','s','s','s','s','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case ',':{char cSym[8][8]={
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','s','W','s','s','s','s'},
						{'s','W','s','s','s','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case '/':{char cSym[8][8]={
						{'s','s','s','s','s','W','s'},
						{'s','s','s','s','W','s','s'},
						{'s','s','s','s','W','s','s'},
						{'s','s','s','W','s','s','s'},
						{'s','s','s','W','s','s','s'},
						{'s','s','W','s','s','s','s'},
						{'s','s','W','s','s','s','s'},
						{'s','W','s','s','s','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case '?':{char cSym[8][8]={
						{'s','s','W','W','W','s','s'},
						{'s','W','s','s','s','W','s'},
						{'s','s','s','s','s','W','s'},
						{'s','s','s','s','W','s','s'},
						{'s','s','s','W','s','s','s'},
						{'s','s','s','W','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','s','s','W','s','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case '!':{char cSym[8][8]={
						{'s','s','s','W','s','s','s'},
						{'s','s','s','W','s','s','s'},
						{'s','s','s','W','s','s','s'},
						{'s','s','s','W','s','s','s'},
						{'s','s','s','W','s','s','s'},
						{'s','s','s','W','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','s','s','W','s','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case '@':{char cSym[8][8]={
						{'s','s','s','W','W','s','s','s'},
						{'s','s','W','s','s','W','s','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','W','W','s','W','s'},
						{'s','W','s','W','W','s','W','s'},
						{'s','W','s','W','W','s','W','s'},
						{'s','W','s','s','W','W','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case '#':{char cSym[8][8]={
						{'s','s','W','s','s','W','s','s'},
						{'s','W','W','W','W','W','W','s'},
						{'s','s','W','s','s','W','s','s'},
						{'s','s','W','s','s','W','s','s'},
						{'s','s','W','s','s','W','s','s'},
						{'s','s','W','s','s','W','s','s'},
						{'s','W','W','W','W','W','W','s'},
						{'s','s','W','s','s','W','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case '$':{char cSym[8][8]={
						{'s','s','s','W','s','s','s','s'},
						{'s','W','W','W','W','s','s','s'},
						{'s','s','s','W','s','W','s','s'},
						{'s','s','s','W','s','W','s','s'},
						{'s','s','W','W','W','s','s','s'},
						{'s','W','s','W','s','s','s','s'},
						{'s','W','s','W','s','s','s','s'},
						{'s','s','W','W','W','W','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case '%':{char cSym[8][8]={
						{'s','s','s','s','W','s','s','s'},
						{'s','W','s','s','W','s','s','s'},
						{'s','W','s','W','s','s','s','s'},
						{'s','s','s','W','s','s','s','s'},
						{'s','s','W','s','s','s','s','s'},
						{'s','s','W','s','W','s','s','s'},
						{'s','W','s','s','W','s','s','s'},
						{'s','W','s','s','s','s','s','s'}};

				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case '^':{char cSym[8][8]={
						{'s','s','s','s','W','s','s','s'},
						{'s','s','s','W','s','W','s','s'},
						{'s','s','W','s','s','s','W','s'},
						{'s','s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s','s'}};

				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case '&':{char cSym[8][8]={
						{'s','s','s','W','W','W','s','s'},
						{'s','s','W','s','s','s','W','s'},
						{'s','s','W','s','s','s','s','s'},
						{'s','s','s','W','s','s','s','s'},
						{'s','s','W','s','W','s','W','s'},
						{'s','W','s','s','s','W','s','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','s','W','W','W','W','s','s'}};

				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case '*':{char cSym[8][8]={
						{'s','s','s','s','s','s','s','s'},
						{'s','W','s','W','s','W','s','s'},
						{'s','s','W','W','W','s','s','s'},
						{'s','s','s','W','s','s','s','s'},
						{'s','s','W','W','W','s','s','s'},
						{'s','W','s','W','s','W','s','s'},
						{'s','s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s','s'}};


				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case '[':{char cSym[8][8]={
						{'s','s','W','W','W','s','s'},
						{'s','s','W','s','s','s','s'},
						{'s','s','W','s','s','s','s'},
						{'s','s','W','s','s','s','s'},
						{'s','s','W','s','s','s','s'},
						{'s','s','W','s','s','s','s'},
						{'s','s','W','s','s','s','s'},
						{'s','s','W','W','W','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case ']':{char cSym[8][8]={
						{'s','s','W','W','W','s','s'},
						{'s','s','s','s','W','s','s'},
						{'s','s','s','s','W','s','s'},
						{'s','s','s','s','W','s','s'},
						{'s','s','s','s','W','s','s'},
						{'s','s','s','s','W','s','s'},
						{'s','s','s','s','W','s','s'},
						{'s','s','W','W','W','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case '0':{char cSym[8][8]={
						{'s','s','s','W','s','s','s'},
						{'s','s','W','s','W','s','s'},
						{'s','W','s','s','s','W','s'},
						{'s','W','s','s','s','W','s'},
						{'s','W','s','s','s','W','s'},
						{'s','W','s','s','s','W','s'},
						{'s','s','W','s','W','s','s'},
						{'s','s','s','W','s','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case '1':{char cSym[8][8]={
						{'s','s','s','W','s','s','s'},
						{'s','s','W','W','s','s','s'},
						{'s','s','s','W','s','s','s'},
						{'s','s','s','W','s','s','s'},
						{'s','s','s','W','s','s','s'},
						{'s','s','s','W','s','s','s'},
						{'s','s','s','W','s','s','s'},
						{'s','s','W','W','W','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case '2':{char cSym[8][8]={
						{'s','s','W','W','s','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','s','s','s','W','s','s'},
						{'s','s','s','W','s','s','s'},
						{'s','s','W','s','s','s','s'},
						{'s','W','s','s','s','s','s'},
						{'s','W','s','s','s','s','s'},
						{'s','W','W','W','W','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case '3':{char cSym[8][8]={
						{'s','s','W','W','s','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','s','s','s','W','s','s'},
						{'s','s','W','W','s','s','s'},
						{'s','s','s','s','W','s','s'},
						{'s','s','s','s','W','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','s','W','W','s','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case '4':{char cSym[8][8]={
						{'s','s','s','s','W','s','s'},
						{'s','s','s','W','W','s','s'},
						{'s','s','W','s','W','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','W','W','W','W','W','s'},
						{'s','s','s','s','W','s','s'},
						{'s','s','s','s','W','s','s'},
						{'s','s','s','s','W','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case '5':{char cSym[8][8]={
						{'s','W','W','W','W','s','s'},
						{'s','W','s','s','s','s','s'},
						{'s','W','s','s','s','s','s'},
						{'s','W','W','W','s','s','s'},
						{'s','s','s','s','W','s','s'},
						{'s','s','s','s','W','s','s'},
						{'s','s','s','s','W','s','s'},
						{'s','W','W','W','s','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case '6':{char cSym[8][8]={
						{'s','s','W','W','s','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','W','s','s','s','s','s'},
						{'s','W','s','s','s','s','s'},
						{'s','W','W','W','s','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','s','W','W','s','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case '7':{char cSym[8][8]={
						{'s','W','W','W','W','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','s','s','W','s','s','s'},
						{'s','s','s','W','s','s','s'},
						{'s','s','W','s','s','s','s'},
						{'s','s','W','s','s','s','s'},
						{'s','W','s','s','s','s','s'},
						{'s','W','s','s','s','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case '8':{char cSym[8][8]={
						{'s','s','W','W','s','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','s','W','W','s','s','s'},
						{'s','s','W','W','s','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','s','W','W','s','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case '9':{char cSym[8][8]={
						{'s','s','W','W','s','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','s','W','W','W','s','s'},
						{'s','s','s','s','W','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','s','W','W','s','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
		}
	}
	else if (lang==1){
		switch(sym){
			case 'A':{char cSym[8][8]={
						{'s','s','s','W','s','s','s','s'},
						{'s','s','W','s','W','s','s','s'},
						{'s','s','W','s','W','s','s','s'},
						{'s','W','s','s','s','W','s','s'},
						{'s','W','W','W','W','W','s','s'},
						{'s','W','s','s','s','W','s','s'},
						{'s','W','s','s','s','W','s','s'},
						{'s','W','s','s','s','W','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'B':{char cSym[8][8]={
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','W','W','s'},
						{'s','W','s','s','W','s','W','s'},
						{'s','W','s','W','s','s','W','s'},
						{'s','W','W','s','s','s','W','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','s','W','s'}};

				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'C':{char cSym[8][8]={
						{'s','s','s','W','W','s','s','s'},
						{'s','s','W','s','s','W','s','s'},
						{'s','W','s','s','s','s','s','s'},
						{'s','W','s','s','s','s','s','s'},
						{'s','W','s','s','s','s','s','s'},
						{'s','W','s','s','s','s','s','s'},
						{'s','s','W','s','s','W','s','s'},
						{'s','s','s','W','W','s','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'D':{char cSym[8][8]={
						{'s','W','W','W','W','s','s'},
						{'s','W','s','s','s','W','s'},
						{'s','W','s','s','s','W','s'},
						{'s','W','W','W','W','s','s'},
						{'s','W','s','s','s','W','s'},
						{'s','W','s','s','s','W','s'},
						{'s','W','s','s','s','W','s'},
						{'s','W','W','W','W','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'E':{char cSym[8][8]={
						{'s','W','W','W','W','W','s'},
						{'s','W','s','s','s','s','s'},
						{'s','W','s','s','s','s','s'},
						{'s','W','W','W','W','W','s'},
						{'s','W','s','s','s','s','s'},
						{'s','W','s','s','s','s','s'},
						{'s','W','s','s','s','s','s'},
						{'s','W','W','W','W','W','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'F':{char cSym[8][8]={
						{'s','W','W','W','W','W','s'},
						{'s','W','s','s','s','s','s'},
						{'s','W','s','s','s','s','s'},
						{'s','W','W','W','W','W','s'},
						{'s','W','s','s','s','s','s'},
						{'s','W','s','s','s','s','s'},
						{'s','W','s','s','s','s','s'},
						{'s','W','s','s','s','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'G':{char cSym[8][8]={
						{'s','W','W','W','W','W','W','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','s','W','s'}};

				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'H':{char cSym[8][8]={
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','W','W','W','W','W','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','s','W','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'I':{char cSym[8][8]={
						{'s','W','W','W','W','W','s','s'},
						{'s','s','s','W','s','s','s','s'},
						{'s','s','s','W','s','s','s','s'},
						{'s','s','s','W','s','s','s','s'},
						{'s','s','s','W','s','s','s','s'},
						{'s','s','s','W','s','s','s','s'},
						{'s','s','s','W','s','s','s','s'},
						{'s','W','W','W','W','W','s','s'}};

				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'J':{char cSym[8][8]={
						{'s','s','s','W','W','s','s','s'},
						{'s','s','W','s','s','W','s','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','s','W','s','s','W','s','s'},
						{'s','s','s','W','W','s','s','s'}};


				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'K':{char cSym[8][8]={
						{'s','W','W','W','s','s','W','s'},
						{'s','s','W','s','s','W','s','s'},
						{'s','s','W','s','W','s','s','s'},
						{'s','s','W','W','s','s','s','s'},
						{'s','s','W','W','s','s','s','s'},
						{'s','s','W','s','W','s','s','s'},
						{'s','s','W','s','s','W','s','s'},
						{'s','W','W','W','s','s','W','s'}};

				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'L':{char cSym[8][8]={
						{'s','W','W','W','s','s','s','s'},
						{'s','s','W','s','s','s','s','s'},
						{'s','s','W','s','s','s','s','s'},
						{'s','s','W','s','s','s','s','s'},
						{'s','s','W','s','s','s','s','s'},
						{'s','s','W','s','s','s','s','s'},
						{'s','s','W','s','s','s','s','s'},
						{'s','W','W','W','W','W','W','s'}};

				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'M':{char cSym[8][8]={
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','W','s','s','W','W','s'},
						{'s','W','s','W','W','s','W','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','s','W','s'}};

				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'N':{char cSym[8][8]={
						{'s','W','s','s','s','s','W','s'},
						{'s','W','W','s','s','s','W','s'},
						{'s','W','s','W','s','s','W','s'},
						{'s','W','s','s','W','s','W','s'},
						{'s','W','s','s','s','W','W','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','s','W','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'O':{char cSym[8][8]={
						{'s','s','s','W','W','s','s','s'},
						{'s','s','W','s','s','W','s','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','s','W','s','s','W','s','s'},
						{'s','s','s','W','W','s','s','s'}};

				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'P':{char cSym[8][8]={
						{'s','W','W','W','W','s','s','s'},
						{'s','W','s','s','s','W','s','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','W','s','s'},
						{'s','W','W','W','W','s','s','s'},
						{'s','W','s','s','s','s','s','s'},
						{'s','W','s','s','s','s','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'Q':{char cSym[8][8]={
						{'s','s','s','W','W','s','s','s'},
						{'s','s','W','s','s','W','s','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','s','W','s','s','W','s','s'},
						{'s','s','s','W','W','s','W','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'R':{char cSym[8][8]={
						{'s','W','W','W','W','s','s','s'},
						{'s','W','s','s','s','W','s','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','W','s','s'},
						{'s','W','W','W','W','s','s','s'},
						{'s','W','s','s','s','W','s','s'},
						{'s','W','s','s','s','s','W','s'}};

				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'S':{char cSym[8][8]={
						{'s','s','W','W','W','s','s'},
						{'s','W','s','s','s','W','s'},
						{'s','W','s','s','s','s','s'},
						{'s','s','W','W','W','s','s'},
						{'s','s','s','s','s','W','s'},
						{'s','s','s','s','s','W','s'},
						{'s','W','s','s','s','W','s'},
						{'s','s','W','W','W','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'T':{char cSym[8][8]={
						{'s','W','W','W','W','W','s','s'},
						{'s','W','s','s','s','s','s','s'},
						{'s','W','s','s','s','s','s','s'},
						{'s','W','W','W','W','W','s','s'},
						{'s','W','s','s','s','s','s','s'},
						{'s','W','s','s','s','s','s','s'},
						{'s','W','s','s','s','s','s','s'},
						{'s','W','W','W','W','W','s','s'}};

				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'U':{char cSym[8][8]={
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','s','W','W','W','W','s','s'}};

				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'V':{char cSym[8][8]={
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','s','W','s','s','W','s','s'},
						{'s','s','s','W','W','s','s','s'}};

				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'W':{char cSym[8][8]={
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','W','W','s','W','s'},
						{'s','s','W','s','s','W','s','s'}};

				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'X':{char cSym[8][8]={
						{'s','W','s','s','s','s','W','s'},
						{'s','s','W','s','s','W','s','s'},
						{'s','s','W','s','s','W','s','s'},
						{'s','s','s','W','W','s','s','s'},
						{'s','s','s','W','W','s','s','s'},
						{'s','s','W','s','s','W','s','s'},
						{'s','s','W','s','s','W','s','s'},
						{'s','W','s','s','s','s','W','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'Y':{char cSym[8][8]={
						{'s','W','s','s','s','W','s','s'},
						{'s','W','s','s','s','W','s','s'},
						{'s','W','s','s','s','W','s','s'},
						{'s','s','W','s','W','s','s','s'},
						{'s','s','s','W','s','s','s','s'},
						{'s','s','s','W','s','s','s','s'},
						{'s','s','s','W','s','s','s','s'},
						{'s','s','s','W','s','s','s','s'}};

				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'Z':{char cSym[8][8]={
						{'s','W','W','W','W','W','W','s'},
						{'s','s','s','s','s','s','W','s'},
						{'s','s','s','s','s','W','s','s'},
						{'s','s','s','s','W','s','s','s'},
						{'s','s','s','W','s','s','s','s'},
						{'s','s','W','s','s','s','s','s'},
						{'s','W','s','s','s','s','s','s'},
						{'s','W','W','W','W','W','W','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'a':{char cSym[8][8]={
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','W','W','W','s','s','s'},
						{'s','s','s','s','W','s','s'},
						{'s','s','W','W','W','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','s','W','W','s','W','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'b':{char cSym[8][8]={
						{'s','s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s','s'},
						{'s','W','s','s','s','W','s','s'},
						{'s','W','s','s','W','W','s','s'},
						{'s','W','s','W','s','W','s','s'},
						{'s','W','W','s','s','W','s','s'},
						{'s','W','s','s','s','W','s','s'},
						{'s','W','s','s','s','W','s','s'}};

				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'c':{char cSym[8][8]={
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','s','W','W','s','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','W','s','s','s','s','s'},
						{'s','W','s','s','s','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','s','W','W','s','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'd':{char cSym[8][8]={
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','W','W','W','s','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','W','W','W','s','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','W','W','W','s','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'e':{char cSym[8][8]={
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','s','W','W','W','s','s'},
						{'s','s','s','s','W','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','s','W','W','s','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'f':{char cSym[8][8]={
						{'s','s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s','s'},
						{'s','s','W','W','W','W','s','s'},
						{'s','W','s','s','s','W','s','s'},
						{'s','W','s','s','s','W','s','s'},
						{'s','W','s','s','s','W','s','s'},
						{'s','W','s','s','s','W','s','s'},
						{'s','s','W','W','W','s','W','s'}};

				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'g':{char cSym[8][8]={
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','W','W','W','W','W','s'},
						{'s','W','s','s','s','W','s'},
						{'s','W','s','s','s','W','s'},
						{'s','W','s','s','s','W','s'},
						{'s','W','s','s','s','W','s'},
						{'s','W','s','s','s','W','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'h':{char cSym[8][8]={
						{'s','s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s','s'},
						{'s','W','W','W','W','s','s','s'},
						{'s','W','s','s','s','W','s','s'},
						{'s','W','s','s','s','W','s','s'},
						{'s','W','W','W','W','s','s','s'},
						{'s','W','s','s','s','s','s','s'},
						{'s','W','s','s','s','s','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'i':{char cSym[8][8]={
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','s','s','W','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','s','s','W','s','s','s'},
						{'s','s','s','W','s','s','s'},
						{'s','s','s','W','s','s','s'},
						{'s','s','s','W','s','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'j':{char cSym[8][8]={
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','s','W','W','W','s','s'},
						{'s','W','s','s','s','W','s'},
						{'s','W','s','s','s','W','s'},
						{'s','W','s','s','s','W','s'},
						{'s','W','s','s','s','W','s'},
						{'s','s','W','W','W','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'k':{char cSym[8][8]={
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','s','s','W','s','s','s'},
						{'s','s','s','W','s','s','s'},
						{'s','s','W','s','W','s','s'},
						{'s','s','W','s','W','s','s'},
						{'s','s','W','s','W','s','s'},
						{'s','W','s','s','s','W','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'l':{char cSym[8][8]={
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','s','s','W','s','s','s'},
						{'s','s','W','s','W','s','s'},
						{'s','s','W','s','W','s','s'},
						{'s','s','W','s','W','s','s'},
						{'s','W','W','W','W','W','s'},
						{'s','W','s','s','s','W','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'm':{char cSym[8][8]={
						{'s','s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s','s'},
						{'s','s','W','s','s','s','s','s'},
						{'s','s','W','s','s','s','s','s'},
						{'s','s','W','W','W','s','s','s'},
						{'s','s','W','s','s','W','s','s'},
						{'s','s','W','s','s','W','s','s'},
						{'s','s','W','W','W','s','s','s'}};

				DrawMatrixDeColor(cSym,x,y,'W',color);;
			} break;
			case 'n':{char cSym[8][8]={
						{'s','s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s','s'},
						{'s','W','W','W','W','W','s','s'},
						{'s','s','s','W','s','s','s','s'},
						{'s','s','s','W','s','s','s','s'},
						{'s','s','s','W','s','s','s','s'},
						{'s','s','s','W','s','s','s','s'},
						{'s','s','s','W','s','s','s','s'}};

				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'o':{char cSym[8][8]={
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','s','W','W','s','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','s','W','W','s','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'p':{char cSym[8][8]={
						{'s','s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s','s'},
						{'s','W','W','W','W','s','s','s'},
						{'s','s','s','s','s','W','s','s'},
						{'s','W','W','W','W','s','s','s'},
						{'s','s','s','s','s','W','s','s'},
						{'s','s','s','s','s','W','s','s'},
						{'s','W','W','W','W','s','s','s'}};

				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'q':{char cSym[8][8]={
						{'s','s','w','W','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','W','s','W','W','s','s'},
						{'s','W','W','s','W','s','s'},
						{'s','W','s','s','W','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'r':{char cSym[8][8]={
						{'s','s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s','s'},
						{'s','s','W','s','s','W','s','s'},
						{'s','s','W','s','W','s','s','s'},
						{'s','s','W','W','s','s','s','s'},
						{'s','s','W','s','W','s','s','s'},
						{'s','s','W','s','s','W','s','s'},
						{'s','s','W','s','s','W','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 's':{char cSym[8][8]={
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','W','s','s','s','W','s'},
						{'s','W','s','s','s','W','s'},
						{'s','W','W','s','s','W','s'},
						{'s','W','s','W','s','W','s'},
						{'s','W','s','W','s','W','s'},
						{'s','W','W','s','s','W','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 't':{char cSym[8][8]={
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','s','W','W','s','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','W','W','W','s','s','s'},
						{'s','W','s','s','s','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','s','W','W','s','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'u':{char cSym[8][8]={
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','W','W','W','W','W','s'},
						{'s','W','s','s','s','s','s'},
						{'s','W','s','s','s','s','s'},
						{'s','W','s','s','s','s','s'},
						{'s','W','s','s','s','s','s'},
						{'s','W','s','s','s','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'v':{char cSym[8][8]={
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','W','s','s','s','W','s'},
						{'s','W','W','s','W','W','s'},
						{'s','W','s','W','s','W','s'},
						{'s','W','s','s','s','W','s'},
						{'s','W','s','s','s','W','s'},
						{'s','W','s','s','s','W','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'w':{char cSym[8][8]={
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','W','s','s','s','W','s'},
						{'s','W','s','s','s','W','s'},
						{'s','W','s','s','s','W','s'},
						{'s','W','s','W','s','W','s'},
						{'s','W','s','W','s','W','s'},
						{'s','s','W','s','W','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'x':{char cSym[8][8]={
						{'s','s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s','s'},
						{'s','W','s','s','s','W','s','s'},
						{'s','W','s','s','s','W','s','s'},
						{'s','W','W','W','W','W','s','s'},
						{'s','s','s','s','s','W','s','s'},
						{'s','s','s','s','s','W','s','s'},
						{'s','s','s','s','s','W','s','s'}};

				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'y':{char cSym[8][8]={
						{'s','s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s','s'},
						{'s','W','s','s','s','W','s','s'},
						{'s','W','s','s','s','W','s','s'},
						{'s','W','W','W','W','W','s','s'},
						{'s','W','s','s','s','W','s','s'},
						{'s','W','s','s','s','W','s','s'},
						{'s','W','s','s','s','W','s','s'}};

				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case 'z':{char cSym[8][8]={
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','W','W','W','W','s','s'},
						{'s','s','s','s','W','s','s'},
						{'s','s','s','W','s','s','s'},
						{'s','s','W','s','s','s','s'},
						{'s','W','s','s','s','s','s'},
						{'s','W','W','W','W','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case ':':{char cSym[8][8]={
						{'s','s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s','s'},
						{'s','W','s','W','s','W','s','s'},
						{'s','s','W','W','W','s','s','s'},
						{'s','s','s','W','s','s','s','s'},
						{'s','s','s','W','s','s','s','s'},
						{'s','s','W','W','W','s','s','s'},
						{'s','W','s','W','s','W','s','s'}};

				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case '-':{char cSym[8][8]={
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','W','W','W','W','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case '+':{char cSym[8][8]={
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','s','s','W','s','s','s'},
						{'s','s','s','W','s','s','s'},
						{'s','W','W','W','W','W','s'},
						{'s','s','s','W','s','s','s'},
						{'s','s','s','W','s','s','s'},
						{'s','s','s','s','s','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case '=':{char cSym[8][8]={
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','W','W','W','W','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','W','W','W','W','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case ' ':{char cSym[8][8]={
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case '.':{char cSym[8][8]={
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','s','W','s','s','s','s'},
						{'s','s','s','s','s','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case ',':{char cSym[8][8]={
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','s','W','s','s','s','s'},
						{'s','W','s','s','s','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case '/':{char cSym[8][8]={
						{'s','s','s','s','s','W','s'},
						{'s','s','s','s','W','s','s'},
						{'s','s','s','s','W','s','s'},
						{'s','s','s','W','s','s','s'},
						{'s','s','s','W','s','s','s'},
						{'s','s','W','s','s','s','s'},
						{'s','s','W','s','s','s','s'},
						{'s','W','s','s','s','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case '?':{char cSym[8][8]={
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','W','W','s','s','s','s'},
						{'s','W','W','s','s','s','s'},
						{'s','s','W','s','s','s','s'},
						{'s','W','s','s','s','s','s'}};
				DrawMatrixDeColor(cSym,x,y+2,'W',color);
			} break;
			case '!':{char cSym[8][8]={
						{'s','s','s','W','s','s','s'},
						{'s','s','s','W','s','s','s'},
						{'s','s','s','W','s','s','s'},
						{'s','s','s','W','s','s','s'},
						{'s','s','s','W','s','s','s'},
						{'s','s','s','W','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','s','s','W','s','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case '@':{char cSym[8][8]={
						{'s','s','s','W','W','s','s','s'},
						{'s','s','W','s','s','W','s','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','W','s','W','W','s','W','s'},
						{'s','W','s','W','W','s','W','s'},
						{'s','W','s','W','W','s','W','s'},
						{'s','W','s','s','W','W','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case '#':{char cSym[8][8]={
						{'s','s','W','s','s','W','s','s'},
						{'s','W','W','W','W','W','W','s'},
						{'s','s','W','s','s','W','s','s'},
						{'s','s','W','s','s','W','s','s'},
						{'s','s','W','s','s','W','s','s'},
						{'s','s','W','s','s','W','s','s'},
						{'s','W','W','W','W','W','W','s'},
						{'s','s','W','s','s','W','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case '$':{char cSym[8][8]={
						{'s','s','s','W','s','s','s','s'},
						{'s','W','W','W','W','s','s','s'},
						{'s','s','s','W','s','W','s','s'},
						{'s','s','s','W','s','W','s','s'},
						{'s','s','W','W','W','s','s','s'},
						{'s','W','s','W','s','s','s','s'},
						{'s','W','s','W','s','s','s','s'},
						{'s','s','W','W','W','W','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case '%':{char cSym[8][8]={
						{'s','s','s','s','W','s','s','s'},
						{'s','W','s','s','W','s','s','s'},
						{'s','W','s','W','s','s','s','s'},
						{'s','s','s','W','s','s','s','s'},
						{'s','s','W','s','s','s','s','s'},
						{'s','s','W','s','W','s','s','s'},
						{'s','W','s','s','W','s','s','s'},
						{'s','W','s','s','s','s','s','s'}};

				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case '^':{char cSym[8][8]={
						{'s','s','s','s','W','s','s','s'},
						{'s','s','s','W','s','W','s','s'},
						{'s','s','W','s','s','s','W','s'},
						{'s','s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s','s'}};

				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case '&':{char cSym[8][8]={
						{'s','s','s','W','W','W','s','s'},
						{'s','s','W','s','s','s','W','s'},
						{'s','s','W','s','s','s','s','s'},
						{'s','s','s','W','s','s','s','s'},
						{'s','s','W','s','W','s','W','s'},
						{'s','W','s','s','s','W','s','s'},
						{'s','W','s','s','s','s','W','s'},
						{'s','s','W','W','W','W','s','s'}};

				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case '*':{char cSym[8][8]={
						{'s','s','s','s','s','s','s','s'},
						{'s','W','s','W','s','W','s','s'},
						{'s','s','W','W','W','s','s','s'},
						{'s','s','s','W','s','s','s','s'},
						{'s','s','W','W','W','s','s','s'},
						{'s','W','s','W','s','W','s','s'},
						{'s','s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s','s'}};


				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case ';':{char cSym[8][8]={
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','W','s','W','s','W','s'},
						{'s','W','s','W','s','W','s'},
						{'s','s','W','W','W','s','s'},
						{'s','W','s','W','s','W','s'},
						{'s','W','s','W','s','W','s'},
						{'s','W','s','W','s','W','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case '[':{char cSym[8][8]={
						{'s','s','W','W','W','s','s'},
						{'s','s','W','s','s','s','s'},
						{'s','s','W','s','s','s','s'},
						{'s','s','W','s','s','s','s'},
						{'s','s','W','s','s','s','s'},
						{'s','s','W','s','s','s','s'},
						{'s','s','W','s','s','s','s'},
						{'s','s','W','W','W','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case ']':{char cSym[8][8]={
						{'s','s','W','W','W','s','s'},
						{'s','s','s','s','W','s','s'},
						{'s','s','s','s','W','s','s'},
						{'s','s','s','s','W','s','s'},
						{'s','s','s','s','W','s','s'},
						{'s','s','s','s','W','s','s'},
						{'s','s','s','s','W','s','s'},
						{'s','s','W','W','W','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case '0':{char cSym[8][8]={
						{'s','s','s','W','s','s','s'},
						{'s','s','W','s','W','s','s'},
						{'s','W','s','s','s','W','s'},
						{'s','W','s','s','s','W','s'},
						{'s','W','s','s','s','W','s'},
						{'s','W','s','s','s','W','s'},
						{'s','s','W','s','W','s','s'},
						{'s','s','s','W','s','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case '1':{char cSym[8][8]={
						{'s','s','s','W','s','s','s'},
						{'s','s','W','W','s','s','s'},
						{'s','s','s','W','s','s','s'},
						{'s','s','s','W','s','s','s'},
						{'s','s','s','W','s','s','s'},
						{'s','s','s','W','s','s','s'},
						{'s','s','s','W','s','s','s'},
						{'s','s','W','W','W','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case '2':{char cSym[8][8]={
						{'s','s','W','W','s','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','s','s','s','W','s','s'},
						{'s','s','s','W','s','s','s'},
						{'s','s','W','s','s','s','s'},
						{'s','W','s','s','s','s','s'},
						{'s','W','s','s','s','s','s'},
						{'s','W','W','W','W','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case '3':{char cSym[8][8]={
						{'s','s','W','W','s','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','s','s','s','W','s','s'},
						{'s','s','W','W','s','s','s'},
						{'s','s','s','s','W','s','s'},
						{'s','s','s','s','W','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','s','W','W','s','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case '4':{char cSym[8][8]={
						{'s','s','s','s','W','s','s'},
						{'s','s','s','W','W','s','s'},
						{'s','s','W','s','W','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','W','W','W','W','W','s'},
						{'s','s','s','s','W','s','s'},
						{'s','s','s','s','W','s','s'},
						{'s','s','s','s','W','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case '5':{char cSym[8][8]={
						{'s','W','W','W','W','s','s'},
						{'s','W','s','s','s','s','s'},
						{'s','W','s','s','s','s','s'},
						{'s','W','W','W','s','s','s'},
						{'s','s','s','s','W','s','s'},
						{'s','s','s','s','W','s','s'},
						{'s','s','s','s','W','s','s'},
						{'s','W','W','W','s','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case '6':{char cSym[8][8]={
						{'s','s','W','W','s','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','W','s','s','s','s','s'},
						{'s','W','s','s','s','s','s'},
						{'s','W','W','W','s','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','s','W','W','s','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case '7':{char cSym[8][8]={
						{'s','W','W','W','W','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','s','s','W','s','s','s'},
						{'s','s','s','W','s','s','s'},
						{'s','s','W','s','s','s','s'},
						{'s','s','W','s','s','s','s'},
						{'s','W','s','s','s','s','s'},
						{'s','W','s','s','s','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case '8':{char cSym[8][8]={
						{'s','s','W','W','s','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','s','W','W','s','s','s'},
						{'s','s','W','W','s','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','s','W','W','s','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
			case '9':{char cSym[8][8]={
						{'s','s','W','W','s','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','s','W','W','W','s','s'},
						{'s','s','s','s','W','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','s','W','W','s','s','s'}};
				DrawMatrixDeColor(cSym,x,y,'W',color);
			} break;
		}
	}
}

void DrawRect(int X, int Y, int X1, int Y1,Uint8 R, Uint8 G, Uint8 B){
	DrawXLine(X, Y, X1, R, G, B);
	DrawXLine(X, Y1, X1, R, G, B);
	DrawYLine(X, Y, Y1, R, G, B);
	DrawYLine(X1, Y, Y1, R, G, B);
}

void DrawFillRect(int X, int Y, int X1, int Y1, Uint8 R, Uint8 G, Uint8 B){
	for (int j=Y;j<Y1;j++){
		DrawXLine(X,j,X1,R,G,B);
	}
}

int Init(){
    SDL_Init( SDL_INIT_VIDEO);
    atexit(SDL_Quit);
    screen = SDL_SetVideoMode(800, 600, 24,SDL_HWSURFACE|SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Monochrome","Monochrome");
    return 0;
}
//----------------------------GAME--------------------------------------
int main ( int argc, char** argv ){
	Init();
	
	megu.SetMode(1);
	megu.SetPostion(248/2,173/2);
	
	rRooms.nRoom = 1;
    
    while (!done)
    {
        Events();
        Draw();
    } 
    return 0;
}

void Events(){
    while (SDL_PollEvent(&event))
    {
       switch (event.type)
       {
          case SDL_QUIT:
              done = true;
              break;
          case SDL_KEYDOWN:
          {
              if (event.key.keysym.sym == SDLK_ESCAPE)
                  done = true;
                  break;
               
          }
       } 
    }
}

void Draw(){
    SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));
	{
		//megu.Draw();
		rRooms.Draw();
	}
    SDL_Flip(screen);
}

