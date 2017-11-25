#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include <SDL/SDL.h>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

//----------------------------FORWARD-----------------------------------
int Init();
void Events();
void Draw();
void DrawPixel(SDL_Surface *screen, int x, int y, Uint8 R, Uint8 G, Uint8 B);
void DrawPixel4(int X, int Y, Uint8 R, Uint8 G, Uint8 B);
void DrawXLine(int X, int Y, int X1, Uint8 R, Uint8 G, Uint8 B);
void DrawYLine(int X, int Y, int Y1, Uint8 R, Uint8 G, Uint8 B);
void DrawMatrix8(char cMatrix[][8],int X, int Y);
void DrawMatrix16(char cMatrix[][16],int X, int Y);
void DrawMatrix32(char cMatrix[][32],int X, int Y);
void DrawSym(int lang, char sym,int x, int y);
void DrawWord(int lang, char* szText,int X, int Y);
void DrawRect(int X, int Y, int X1, int Y1,Uint8 R, Uint8 G, Uint8 B);
void DrawFillRect(int X, int Y, int X1, int Y1, Uint8 R, Uint8 G, Uint8 B);

//--------------------------VARIABLES-----------------------------------
SDL_Surface* screen;
SDL_Event event;
bool done = false;

//----------------------------CLASSES-----------------------------------

class Canvas{
	public:
		char c8[8][8]={
		{'s','s','s','s','s','s','s','s'},
		{'s','s','s','s','s','s','s','s'},
		{'s','s','s','s','s','s','s','s'},
		{'s','s','s','s','s','s','s','s'},
		{'s','s','s','s','s','s','s','s'},
		{'s','s','s','s','s','s','s','s'},
		{'s','s','s','s','s','s','s','s'},
		{'s','s','s','s','s','s','s','s'}};
		char c16[16][16]={
		{'s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s'},
		{'s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s'},
		{'s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s'},
		{'s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s'},
		{'s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s'},
		{'s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s'},
		{'s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s'},
		{'s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s'},
		{'s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s'},
		{'s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s'},
		{'s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s'},
		{'s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s'},
		{'s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s'},
		{'s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s'},
		{'s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s'},
		{'s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s'}};
		char c32[32][32]={
		{'s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s'},
		{'s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s'},
		{'s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s'},
		{'s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s'},
		{'s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s'},
		{'s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s'},
		{'s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s'},
		{'s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s'},
		{'s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s'},
		{'s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s'},
		{'s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s'},
		{'s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s'},
		{'s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s'},
		{'s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s'},
		{'s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s'},
		{'s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s'},
		{'s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s'},
		{'s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s'},
		{'s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s'},
		{'s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s'},
		{'s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s'},
		{'s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s'},
		{'s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s'},
		{'s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s'},
		{'s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s'},
		{'s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s'},
		{'s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s'},
		{'s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s'},
		{'s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s'},
		{'s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s'},
		{'s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s'},
		{'s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s','s'}};
		int x;
		int y;
		int nMode;
		int nColor;

		Canvas(){
				nMode = 0;
				x = 0;
				y = 0;
				nColor = 0;
		};
		~Canvas(){

		};

		void SetPos(int X, int Y){
			x = X;
			y = Y;
		};

		void SetMode(int MODE){
			nMode = MODE;
		};

		void DrawPixel(char color){
			if (nMode==0){
				c8[y][x] = color;
			}
			if (nMode==1){
				c16[y][x] = color;
			}
			if (nMode==2){
				c32[y][x] = color;
			}
		};

		void DrawMatrix8(char cMatrix[][8],int X, int Y){
			char cRead;
			int w = 8;
			int h = 8;
			for (int y=0;y<h;y++){
				for (int x=0;x<w;x++){
					cRead = cMatrix[y][x];
					if (cRead=='s'){}
					else if(cRead=='r'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 255, 0, 0);
							}
						}
					}
					else if(cRead=='g'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 0, 255, 0);
							}
						}
					}
					else if(cRead=='b'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 0, 0, 255);
							}
						}
					}
					else if(cRead=='W'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 255, 255, 255);
							}
						}
					}
					else if(cRead=='B'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 0, 0, 0);
							}
						}
					}
					else if(cRead=='G'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 100, 100, 100);
							}
						}
					}
					else if(cRead=='0'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 50, 50, 50);
							}
						}
					}
					else if(cRead=='1'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 150, 150, 150);
							}
						}
					}
					else if(cRead=='2'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 200, 200, 200);
							}
						}
					}
					else if(cRead=='3'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 50, 0, 0);
							}
						}
					}
					else if(cRead=='4'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 150, 0, 0);
							}
						}
					}
					else if(cRead=='5'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 200, 0, 0);
							}
						}
					}
					else if(cRead=='6'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 0, 50, 0);
							}
						}
					}
					else if(cRead=='7'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 0, 150, 0);
							}
						}
					}
					else if(cRead=='8'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 0, 200, 0);
							}
						}
					}
					else if(cRead=='9'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 0, 0, 50);
							}
						}
					}
					else if(cRead=='a'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 0, 0, 150);
							}
						}
					}
					else if(cRead=='c'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 0, 0, 200);
							}
						}
					}
					else if(cRead=='y'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 255, 255, 0);
							}
						}
					}
					else if(cRead=='d'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 50, 50, 0);
							}
						}
					}
					else if(cRead=='e'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 150, 150, 0);
							}
						}
					}
					else if(cRead=='f'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 200, 200, 0);
							}
						}
					}
					else if(cRead=='h'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 0, 50, 50);
							}
						}
					}
					else if(cRead=='k'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 0, 150, 150);
							}
						}
					}
					else if(cRead=='l'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 0, 200, 200);
							}
						}
					}
					else if(cRead=='m'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 0, 250, 250);
							}
						}
					}
					else if(cRead=='n'){
						 for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 50, 0, 50);
							}
						}
					}
					else if(cRead=='o'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 150, 0, 150);
							}
						}
					}
					else if(cRead=='p'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 200, 0, 200);
							}
						}
					}
					else if(cRead=='q'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 255, 0, 255);
							}
						}
					}
					else if(cRead=='t'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 100, 50, 0);
							}
						}
					}
					else if(cRead=='u'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 200, 150, 0);
							}
						}
					}
					else if(cRead=='v'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 255, 200, 0);
							}
						}
					}
				}
			}
		};

		void DrawMatrix16(char cMatrix[][16],int X, int Y){
			char cRead;
			int w = 16;
			int h = 16;
			for (int y=0;y<h;y++){
				for (int x=0;x<w;x++){
					cRead = cMatrix[y][x];
					if (cRead=='s'){}
					else if(cRead=='r'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 255, 0, 0);
							}
						}
					}
					else if(cRead=='g'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 0, 255, 0);
							}
						}
					}
					else if(cRead=='b'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 0, 0, 255);
							}
						}
					}
					else if(cRead=='W'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 255, 255, 255);
							}
						}
					}
					else if(cRead=='B'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 0, 0, 0);
							}
						}
					}
					else if(cRead=='G'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 100, 100, 100);
							}
						}
					}
					else if(cRead=='0'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 50, 50, 50);
							}
						}
					}
					else if(cRead=='1'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 150, 150, 150);
							}
						}
					}
					else if(cRead=='2'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 200, 200, 200);
							}
						}
					}
					else if(cRead=='3'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 50, 0, 0);
							}
						}
					}
					else if(cRead=='4'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 150, 0, 0);
							}
						}
					}
					else if(cRead=='5'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 200, 0, 0);
							}
						}
					}
					else if(cRead=='6'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 0, 50, 0);
							}
						}
					}
					else if(cRead=='7'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 0, 150, 0);
							}
						}
					}
					else if(cRead=='8'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 0, 200, 0);
							}
						}
					}
					else if(cRead=='9'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 0, 0, 50);
							}
						}
					}
					else if(cRead=='a'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 0, 0, 150);
							}
						}
					}
					else if(cRead=='c'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 0, 0, 200);
							}
						}
					}
					else if(cRead=='y'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 255, 255, 0);
							}
						}
					}
					else if(cRead=='d'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 50, 50, 0);
							}
						}
					}
					else if(cRead=='e'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 150, 150, 0);
							}
						}
					}
					else if(cRead=='f'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 200, 200, 0);
							}
						}
					}
					else if(cRead=='h'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 0, 50, 50);
							}
						}
					}
					else if(cRead=='k'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 0, 150, 150);
							}
						}
					}
					else if(cRead=='l'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 0, 200, 200);
							}
						}
					}
					else if(cRead=='m'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 0, 250, 250);
							}
						}
					}
					else if(cRead=='n'){
						 for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 50, 0, 50);
							}
						}
					}
					else if(cRead=='o'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 150, 0, 150);
							}
						}
					}
					else if(cRead=='p'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 200, 0, 200);
							}
						}
					}
					else if(cRead=='q'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 255, 0, 255);
							}
						}
					}
					else if(cRead=='t'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 100, 50, 0);
							}
						}
					}
					else if(cRead=='u'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 200, 150, 0);
							}
						}
					}
					else if(cRead=='v'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 255, 200, 0);
							}
						}
					}
				}
			}
		};

		void DrawMatrix32(char cMatrix[][32],int X, int Y){
			char cRead;
			int w = 32;
			int h = 32;
			for (int y=0;y<h;y++){
				for (int x=0;x<w;x++){
					cRead = cMatrix[y][x];
					if (cRead=='s'){}
					else if(cRead=='r'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 255, 0, 0);
							}
						}
					}
					else if(cRead=='g'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 0, 255, 0);
							}
						}
					}
					else if(cRead=='b'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 0, 0, 255);
							}
						}
					}
					else if(cRead=='W'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 255, 255, 255);
							}
						}
					}
					else if(cRead=='B'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 0, 0, 0);
							}
						}
					}
					else if(cRead=='G'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 100, 100, 100);
							}
						}
					}
					else if(cRead=='0'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 50, 50, 50);
							}
						}
					}
					else if(cRead=='1'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 150, 150, 150);
							}
						}
					}
					else if(cRead=='2'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 200, 200, 200);
							}
						}
					}
					else if(cRead=='3'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 50, 0, 0);
							}
						}
					}
					else if(cRead=='4'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 150, 0, 0);
							}
						}
					}
					else if(cRead=='5'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 200, 0, 0);
							}
						}
					}
					else if(cRead=='6'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 0, 50, 0);
							}
						}
					}
					else if(cRead=='7'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 0, 150, 0);
							}
						}
					}
					else if(cRead=='8'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 0, 200, 0);
							}
						}
					}
					else if(cRead=='9'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 0, 0, 50);
							}
						}
					}
					else if(cRead=='a'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 0, 0, 150);
							}
						}
					}
					else if(cRead=='c'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 0, 0, 200);
							}
						}
					}
					else if(cRead=='y'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 255, 255, 0);
							}
						}
					}
					else if(cRead=='d'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 50, 50, 0);
							}
						}
					}
					else if(cRead=='e'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 150, 150, 0);
							}
						}
					}
					else if(cRead=='f'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 200, 200, 0);
							}
						}
					}
					else if(cRead=='h'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 0, 50, 50);
							}
						}
					}
					else if(cRead=='k'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 0, 150, 150);
							}
						}
					}
					else if(cRead=='l'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 0, 200, 200);
							}
						}
					}
					else if(cRead=='m'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 0, 250, 250);
							}
						}
					}
					else if(cRead=='n'){
						 for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 50, 0, 50);
							}
						}
					}
					else if(cRead=='o'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 150, 0, 150);
							}
						}
					}
					else if(cRead=='p'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 200, 0, 200);
							}
						}
					}
					else if(cRead=='q'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 255, 0, 255);
							}
						}
					}
					else if(cRead=='t'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 100, 50, 0);
							}
						}
					}
					else if(cRead=='u'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 200, 150, 0);
							}
						}
					}
					else if(cRead=='v'){
						for (int i=0;i<7;i++){
							for (int j=0;j<7;j++){
								DrawPixel4(X+(x*7)+i-1, Y+(y*7)+j-1, 255, 200, 0);
							}
						}
					}
				}
			}
		};
		
		void SaveMatrix(int size){
			if (size == 8){
				ofstream fout("matrix8.txt");
				fout << "{" << "\n";
				for (int i=0;i<8;i++){
					fout 
					<< "{'" << this->c8[i][0] << "','" << this->c8[i][1]
					<< "','" << this->c8[i][2] << "','" << this->c8[i][3]
					<< "','" << this->c8[i][4] << "','" << this->c8[i][5]
					<< "','" << this->c8[i][6] << "','" << this->c8[i][7] 
					<< "'},\n";
				}
				fout << "};" << "\n";
			}
			if (size == 16){
				ofstream fout("matrix16.txt");
				fout << "{" << "\n";
				for (int i=0;i<16;i++){
					fout 
					<< "{'" << this->c16[i][0] << "','" << this->c16[i][1]
					<< "','" << this->c16[i][2] << "','" << this->c16[i][3]
					<< "','" << this->c16[i][4] << "','" << this->c16[i][5]
					<< "','" << this->c16[i][6] << "','" << this->c16[i][7] 
					<< "','" << this->c16[i][8] << "','" << this->c16[i][9]
					<< "','" << this->c16[i][10] << "','" << this->c16[i][11]
					<< "','" << this->c16[i][12] << "','" << this->c16[i][13]
					<< "','" << this->c16[i][14] << "','" << this->c16[i][15]    
					<< "'},\n";
				}
				fout << "};" << "\n";
			}
			if (size == 32){
				ofstream fout("matrix32.txt");
				fout << "{" << "\n";
				for (int i=0;i<32;i++){
					fout 
					<< "{'" << this->c32[i][0] << "','" << this->c32[i][1]
					<< "','" << this->c32[i][2] << "','" << this->c32[i][3]
					<< "','" << this->c32[i][4] << "','" << this->c32[i][5]
					<< "','" << this->c32[i][6] << "','" << this->c32[i][7] 
					<< "','" << this->c32[i][8] << "','" << this->c32[i][9]
					<< "','" << this->c32[i][10] << "','" << this->c32[i][11]
					<< "','" << this->c32[i][12] << "','" << this->c32[i][13]
					<< "','" << this->c32[i][14] << "','" << this->c32[i][15]    
					<< "','" << this->c32[i][16] << "','" << this->c32[i][17]
					<< "','" << this->c32[i][18] << "','" << this->c32[i][19]
					<< "','" << this->c32[i][20] << "','" << this->c32[i][21]
					<< "','" << this->c32[i][22] << "','" << this->c32[i][23]
					<< "','" << this->c32[i][24] << "','" << this->c32[i][25]
					<< "','" << this->c32[i][26] << "','" << this->c32[i][27]
					<< "','" << this->c32[i][28] << "','" << this->c32[i][29]
					<< "','" << this->c32[i][30] << "','" << this->c32[i][31]            
					<< "'},\n";
				}
				fout << "};" << "\n";
			}
		};

		void DrawGrid(){
			switch(nMode){
				case 2:
					for (int i = 1; i<33;i++){
						for (int j = 1; j<33;j++){
							DrawRect(i*7,j*7,(i*7)+7,(j*7)+7,240,240,240);
						}
					}
					if ((x<32) && (y<32)){
						DrawRect(7+x*7,7+y*7,7+(x*7)+7,7+(y*7)+7,200,0,0);
					}
					this->DrawMatrix32(c32,7,7);
					if ((x<32) && (y<32)){
						DrawRect(7+x*7-1,7+y*7-1,7+(x*7)-1+7,7+(y*7)+7-1,255,0,0);
					}
					break;
				case 1:for (int i = 1; i<17;i++){
					for (int j = 1; j<17;j++){
						DrawRect(i*7,j*7,(i*7)+7,(j*7)+7,240,240,240);
					}
					if ((x<16) && (y<16)){
						DrawRect(7+x*7,7+y*7,7+(x*7)+7,7+(y*7)+7,200,0,0);
					}
					this->DrawMatrix16(c16,7,7);
					if ((x<16) && (y<16)){
						DrawRect(7+x*7-1,7+y*7-1,7+(x*7)+7-1,7+(y*7)+7-1,255,0,0);
					}
				} break;
				case 0:
					for (int i = 1; i<9;i++){
						for (int j = 1; j<9;j++){
							DrawRect(i*7,j*7,(i*7)+7,(j*7)+7,240,240,240);
						}
					}
					if ((x<8) && (y<8)){
						DrawRect(7+x*7,7+y*7,7+(x*7)+7,7+(y*7)+7,200,0,0);
					}
					this->DrawMatrix8(c8,7,7);
					if ((x<8) && (y<8)){
						DrawRect(7+(x*7)-1,7+(y*7)-1,7+(x*7)+7-1,7+(y*7)+7-1,255,0,0);
					}
					break;
			}
		};

};


//----------------------------OBJECTS-----------------------------------
Canvas cnv;
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

void DrawMatrix8(char cMatrix[][8],int X, int Y){
	char cRead;
	int w = 8;
	int h = 8;
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

void DrawMatrix16(char cMatrix[][16],int X, int Y){
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

void DrawMatrix32(char cMatrix[][32],int X, int Y){
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

void DrawSym(int lang, char sym,int x, int y){
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
				DrawMatrix8(cSym,x,y);
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
				DrawMatrix8(cSym,x,y);
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
				DrawMatrix8(cSym,x,y);
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
				DrawMatrix8(cSym,x,y);
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
				DrawMatrix8(cSym,x,y);
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
				DrawMatrix8(cSym,x,y);
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
				DrawMatrix8(cSym,x,y);
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
				DrawMatrix8(cSym,x,y);
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
				DrawMatrix8(cSym,x,y);
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
				DrawMatrix8(cSym,x,y);
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
				DrawMatrix8(cSym,x,y);
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
				DrawMatrix8(cSym,x,y);
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
				DrawMatrix8(cSym,x,y);
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
				DrawMatrix8(cSym,x,y);
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
				DrawMatrix8(cSym,x,y);
			} break;
			case 'x':{char cSym[8][8]={
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','W','s','s','s','W','s'},
						{'s','s','W','s','W','s','s'},
						{'s','s','s','W','s','s','s'},
						{'s','s','W','s','W','s','s'},
						{'s','W','s','s','s','W','s'},
						{'s','s','s','s','s','s','s'}};
				DrawMatrix8(cSym,x,y);
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
				DrawMatrix8(cSym,x,y);
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
				DrawMatrix8(cSym,x,y);
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
				DrawMatrix8(cSym,x,y);
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
				DrawMatrix8(cSym,x,y);
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
				DrawMatrix8(cSym,x,y);
			} break;
			case '[':{char cSym[8][8]={
						{'s','s','y','y','y','s','s'},
						{'s','s','y','s','s','s','s'},
						{'s','s','y','s','s','s','s'},
						{'s','s','y','s','s','s','s'},
						{'s','s','y','s','s','s','s'},
						{'s','s','y','s','s','s','s'},
						{'s','s','y','s','s','s','s'},
						{'s','s','y','y','y','s','s'}};
				DrawMatrix8(cSym,x,y);
			} break;
			case ']':{char cSym[8][8]={
						{'s','s','y','y','y','s','s'},
						{'s','s','s','s','y','s','s'},
						{'s','s','s','s','y','s','s'},
						{'s','s','s','s','y','s','s'},
						{'s','s','s','s','y','s','s'},
						{'s','s','s','s','y','s','s'},
						{'s','s','s','s','y','s','s'},
						{'s','s','y','y','y','s','s'}};
				DrawMatrix8(cSym,x,y);
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
				DrawMatrix8(cSym,x,y);
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
				DrawMatrix8(cSym,x,y);
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
				DrawMatrix8(cSym,x,y);
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
				DrawMatrix8(cSym,x,y);
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
				DrawMatrix8(cSym,x,y);
			} break;
			/*case 'B':{char cSym[8][8]={
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'}};
				DrawMatrix8(cSym,x,y);
			} break;*/
		}
	}
}

void DrawRect(int X, int Y, int X1, int Y1,Uint8 R, Uint8 G, Uint8 B){
	DrawXLine(X, Y, X1, R, G, B);
	DrawXLine(X, Y1, X1, R, G, B);
	DrawYLine(X, Y, Y1, R, G, B);
	DrawYLine(X1, Y, Y1, R, G, B);
}

void DrawWord(int lang, char* szText,int X, int Y){
	char rc;
	for (int i = 0;i<strlen(szText);i++){
		rc = szText[i];
		DrawSym(0,rc,X+(i*7),Y);
	}
}


int Init(){
    SDL_Init( SDL_INIT_VIDEO);
    atexit(SDL_Quit);
    screen = SDL_SetVideoMode(640, 480, 24,SDL_HWSURFACE|SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Matrix Edit","Matrix Edit");
    return 0;
}

void DrawFillRect(int X, int Y, int X1, int Y1, Uint8 R, Uint8 G, Uint8 B){
	for (int j=Y;j<Y1;j++){
		DrawXLine(X,j,X1,R,G,B);
	}
}

//----------------------------GAME--------------------------------------
//VAR
int nRoom = 0;
int nMenu = 0;
bool bFullscreen = false;

int main ( int argc, char** argv ){
	Init();

	//SDL_EnableKeyRepeat(0.5,0.1);
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
                nRoom = 0;
             if (event.key.keysym.sym == SDLK_f){
				if (!bFullscreen){
					screen = SDL_SetVideoMode(640, 480, 24,SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_FULLSCREEN);
					bFullscreen = true;
				} 
				else {
					screen = SDL_SetVideoMode(640, 480, 24,SDL_HWSURFACE|SDL_DOUBLEBUF);
					bFullscreen = false;
				}
			}
             if (nRoom==0){
				if (event.key.keysym.sym == SDLK_UP)
					if (nMenu > 0) nMenu--;
				if (event.key.keysym.sym == SDLK_DOWN)
					if (nMenu < 2) nMenu++;
				if (event.key.keysym.sym == SDLK_RETURN){
					cnv.SetMode(nMenu);
					cnv.SetPos(0,0);
					nRoom = 1;
					cnv.nColor = 32;
				}
			}
			if (nRoom==1){
				if (cnv.nMode==0){
					if (event.key.keysym.sym == SDLK_s)
						cnv.SaveMatrix(8);
					if (event.key.keysym.sym == SDLK_BACKSPACE)
						cnv.c8[cnv.y][cnv.x] = 's'; 
					if (event.key.keysym.sym == SDLK_UP)
						if (cnv.y>0) cnv.y--;
					if (event.key.keysym.sym == SDLK_DOWN)
						if (cnv.y<7) cnv.y++;
					if (event.key.keysym.sym == SDLK_RIGHT)
						if (cnv.x<7) cnv.x++;
					if (event.key.keysym.sym == SDLK_LEFT)
						if (cnv.x>0) cnv.x--;
					if (event.key.keysym.sym == SDLK_RETURN){
						switch (cnv.nColor){
							case 0: 
								cnv.c8[cnv.y][cnv.x] = 'B'; 
								break;
							case 1: 
								cnv.c8[cnv.y][cnv.x] = 'W';
								break;
							case 2: 
								cnv.c8[cnv.y][cnv.x] = '0';
								break;
							case 3: 
								cnv.c8[cnv.y][cnv.x] = '1';
								break;
							case 4: 
								cnv.c8[cnv.y][cnv.x] = '2';
								break;
							case 5: 
								cnv.c8[cnv.y][cnv.x] = '3';
								break;
							case 6: 
								cnv.c8[cnv.y][cnv.x] = '4';
								break;
							case 7: 
								cnv.c8[cnv.y][cnv.x] = '5';
								break;
							case 8: 
								cnv.c8[cnv.y][cnv.x] = 'r';
								break;
							case 9: 
								cnv.c8[cnv.y][cnv.x] = '6';
								break;
							case 10: 
								cnv.c8[cnv.y][cnv.x] = '7';
								break;
							case 11: 
								cnv.c8[cnv.y][cnv.x] = '8';
								break;
							case 12: 
								cnv.c8[cnv.y][cnv.x] = 'g';
								break;
							case 13: 
								cnv.c8[cnv.y][cnv.x] = '9';
								break;
							case 14: 
								cnv.c8[cnv.y][cnv.x] = 'a';
								break;
							case 15: 
								cnv.c8[cnv.y][cnv.x] = 'c';
								break;
							case 16: 
								cnv.c8[cnv.y][cnv.x] = 'b';
								break;
							case 17: 
								cnv.c8[cnv.y][cnv.x] = 'd';
								break;
							case 18: 
								cnv.c8[cnv.y][cnv.x] = 'e';
								break;
							case 19: 
								cnv.c8[cnv.y][cnv.x] = 'f';
								break;
							case 20: 
								cnv.c8[cnv.y][cnv.x] = 'y';
								break;
							case 21: 
								cnv.c8[cnv.y][cnv.x] = 'h';
								break;
							case 22: 
								cnv.c8[cnv.y][cnv.x] = 'k';
								break;
							case 23: 
								cnv.c8[cnv.y][cnv.x] = 'l';
								break;
							case 24: 
								cnv.c8[cnv.y][cnv.x] = 'm';
								break;
							case 25: 
								cnv.c8[cnv.y][cnv.x] = 't';
								break;
							case 26: 
								cnv.c8[cnv.y][cnv.x] = 'u';
								break;
							case 27: 
								cnv.c8[cnv.y][cnv.x] = 'v';
								break;
							case 28: 
								cnv.c8[cnv.y][cnv.x] = 'n';
								break;
							case 29: 
								cnv.c8[cnv.y][cnv.x] = 'o';
								break;
							case 30: 
								cnv.c8[cnv.y][cnv.x] = 'p';
								break;
							case 31: 
								cnv.c8[cnv.y][cnv.x] = 'q';
								break;
							case 32: 
								cnv.c8[cnv.y][cnv.x] = 's';
								break;
							}
						}
				}
				if (cnv.nMode==1){
					if (event.key.keysym.sym == SDLK_s)
						cnv.SaveMatrix(16);
					if (event.key.keysym.sym == SDLK_BACKSPACE)
						cnv.c16[cnv.y][cnv.x] = 's'; 
					if (event.key.keysym.sym == SDLK_UP)
						if (cnv.y>0) cnv.y--;
					if (event.key.keysym.sym == SDLK_DOWN)
						if (cnv.y<15) cnv.y++;
					if (event.key.keysym.sym == SDLK_RIGHT)
						if (cnv.x<15) cnv.x++;
					if (event.key.keysym.sym == SDLK_LEFT)
						if (cnv.x>0) cnv.x--;
					if (event.key.keysym.sym == SDLK_RETURN){
						switch (cnv.nColor){
							case 0: 
								cnv.c16[cnv.y][cnv.x] = 'B'; 
								break;
							case 1: 
								cnv.c16[cnv.y][cnv.x] = 'W';
								break;
							case 2: 
								cnv.c16[cnv.y][cnv.x] = '0';
								break;
							case 3: 
								cnv.c16[cnv.y][cnv.x] = '1';
								break;
							case 4: 
								cnv.c16[cnv.y][cnv.x] = '2';
								break;
							case 5: 
								cnv.c16[cnv.y][cnv.x] = '3';
								break;
							case 6: 
								cnv.c16[cnv.y][cnv.x] = '4';
								break;
							case 7: 
								cnv.c16[cnv.y][cnv.x] = '5';
								break;
							case 8: 
								cnv.c16[cnv.y][cnv.x] = 'r';
								break;
							case 9: 
								cnv.c16[cnv.y][cnv.x] = '6';
								break;
							case 10: 
								cnv.c16[cnv.y][cnv.x] = '7';
								break;
							case 11: 
								cnv.c16[cnv.y][cnv.x] = '8';
								break;
							case 12: 
								cnv.c16[cnv.y][cnv.x] = 'g';
								break;
							case 13: 
								cnv.c16[cnv.y][cnv.x] = '9';
								break;
							case 14: 
								cnv.c16[cnv.y][cnv.x] = 'a';
								break;
							case 15: 
								cnv.c16[cnv.y][cnv.x] = 'c';
								break;
							case 16: 
								cnv.c16[cnv.y][cnv.x] = 'b';
								break;
							case 17: 
								cnv.c16[cnv.y][cnv.x] = 'd';
								break;
							case 18: 
								cnv.c16[cnv.y][cnv.x] = 'e';
								break;
							case 19: 
								cnv.c16[cnv.y][cnv.x] = 'f';
								break;
							case 20: 
								cnv.c16[cnv.y][cnv.x] = 'y';
								break;
							case 21: 
								cnv.c16[cnv.y][cnv.x] = 'h';
								break;
							case 22: 
								cnv.c16[cnv.y][cnv.x] = 'k';
								break;
							case 23: 
								cnv.c16[cnv.y][cnv.x] = 'l';
								break;
							case 24: 
								cnv.c16[cnv.y][cnv.x] = 'm';
								break;
							case 25: 
								cnv.c16[cnv.y][cnv.x] = 't';
								break;
							case 26: 
								cnv.c16[cnv.y][cnv.x] = 'u';
								break;
							case 27: 
								cnv.c16[cnv.y][cnv.x] = 'v';
								break;
							case 28: 
								cnv.c16[cnv.y][cnv.x] = 'n';
								break;
							case 29: 
								cnv.c16[cnv.y][cnv.x] = 'o';
								break;
							case 30: 
								cnv.c16[cnv.y][cnv.x] = 'p';
								break;
							case 31: 
								cnv.c16[cnv.y][cnv.x] = 'q';
								break;
							case 32: 
								cnv.c16[cnv.y][cnv.x] = 's';
								break;
							}
						}
				}
				if (cnv.nMode==2){
					if (event.key.keysym.sym == SDLK_s)
						cnv.SaveMatrix(32);
					if (event.key.keysym.sym == SDLK_BACKSPACE)
						cnv.c32[cnv.y][cnv.x] = 's'; 
					if (event.key.keysym.sym == SDLK_UP)
						if (cnv.y>0) cnv.y--;
					if (event.key.keysym.sym == SDLK_DOWN)
						if (cnv.y<31) cnv.y++;
					if (event.key.keysym.sym == SDLK_RIGHT)
						if (cnv.x<31) cnv.x++;
					if (event.key.keysym.sym == SDLK_LEFT)
						if (cnv.x>0) cnv.x--;
					if (event.key.keysym.sym == SDLK_RETURN){
						switch (cnv.nColor){
							case 0: 
								cnv.c32[cnv.y][cnv.x] = 'B'; 
								break;
							case 1: 
								cnv.c32[cnv.y][cnv.x] = 'W';
								break;
							case 2: 
								cnv.c32[cnv.y][cnv.x] = '0';
								break;
							case 3: 
								cnv.c32[cnv.y][cnv.x] = '1';
								break;
							case 4: 
								cnv.c32[cnv.y][cnv.x] = '2';
								break;
							case 5: 
								cnv.c32[cnv.y][cnv.x] = '3';
								break;
							case 6: 
								cnv.c32[cnv.y][cnv.x] = '4';
								break;
							case 7: 
								cnv.c32[cnv.y][cnv.x] = '5';
								break;
							case 8: 
								cnv.c32[cnv.y][cnv.x] = 'r';
								break;
							case 9: 
								cnv.c32[cnv.y][cnv.x] = '6';
								break;
							case 10: 
								cnv.c32[cnv.y][cnv.x] = '7';
								break;
							case 11: 
								cnv.c32[cnv.y][cnv.x] = '8';
								break;
							case 12: 
								cnv.c32[cnv.y][cnv.x] = 'g';
								break;
							case 13: 
								cnv.c32[cnv.y][cnv.x] = '9';
								break;
							case 14: 
								cnv.c32[cnv.y][cnv.x] = 'a';
								break;
							case 15: 
								cnv.c32[cnv.y][cnv.x] = 'c';
								break;
							case 16: 
								cnv.c32[cnv.y][cnv.x] = 'b';
								break;
							case 17: 
								cnv.c32[cnv.y][cnv.x] = 'd';
								break;
							case 18: 
								cnv.c32[cnv.y][cnv.x] = 'e';
								break;
							case 19: 
								cnv.c32[cnv.y][cnv.x] = 'f';
								break;
							case 20: 
								cnv.c32[cnv.y][cnv.x] = 'y';
								break;
							case 21: 
								cnv.c32[cnv.y][cnv.x] = 'h';
								break;
							case 22: 
								cnv.c32[cnv.y][cnv.x] = 'k';
								break;
							case 23: 
								cnv.c32[cnv.y][cnv.x] = 'l';
								break;
							case 24: 
								cnv.c32[cnv.y][cnv.x] = 'm';
								break;
							case 25: 
								cnv.c32[cnv.y][cnv.x] = 't';
								break;
							case 26: 
								cnv.c32[cnv.y][cnv.x] = 'u';
								break;
							case 27: 
								cnv.c32[cnv.y][cnv.x] = 'v';
								break;
							case 28: 
								cnv.c32[cnv.y][cnv.x] = 'n';
								break;
							case 29: 
								cnv.c32[cnv.y][cnv.x] = 'o';
								break;
							case 30: 
								cnv.c32[cnv.y][cnv.x] = 'p';
								break;
							case 31: 
								cnv.c32[cnv.y][cnv.x] = 'q';
								break;
							case 32: 
								cnv.c32[cnv.y][cnv.x] = 's';
								break;
							}
						}
				}
				if (event.key.keysym.sym == SDLK_x){
					cnv.nColor++;
					if (cnv.nColor==33) cnv.nColor = 0;
				}
				if (event.key.keysym.sym == SDLK_z){
					cnv.nColor--;
					if (cnv.nColor==-1) cnv.nColor = 32;
				}
				
			}
          } break;
       }
    }
}

void Draw(){
	SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));
	{
		if (nRoom == 0){
			DrawWord(0,"Select size:",1,1);

			DrawWord(0,"8x8",16,18);
			DrawWord(0,"16x16",16,28);
			DrawWord(0,"32x32",16,38);

			char cSel[8][8] = {
					{'s','s','s','s','s','s','s','s'},
					{'s','s','b','b','b','s','s','s'},
					{'s','b','s','s','s','b','s','s'},
					{'s','b','s','s','s','b','s','s'},
					{'s','b','s','s','s','b','s','s'},
					{'s','s','b','b','b','s','s','s'},
					{'s','s','s','s','s','s','s','s'},
					{'s','s','s','s','s','s','s','s'},
			};

			if (nMenu == 0){
				DrawMatrix8(cSel,6,18);
			}
			else if (nMenu == 1){
				DrawMatrix8(cSel,6,28);
			}
			else if (nMenu == 2){
				DrawMatrix8(cSel,6,38);
			}
		}
		else if (nRoom == 1){
			cnv.DrawGrid();
			DrawRect(34*7,7,45*7,7*33,255,255,255);
			DrawWord(0,"[S]ave",(34*7)+2,9);

			//DrawRect(43*7,23+14,(43*7)+7,23+14+7,255,255,255);
			DrawFillRect(43*7,23+7,(43*7)+7,23+7+7,255,255,255);
			DrawFillRect(43*7,23+14,(43*7)+7,23+7+14,50,50,50);
			DrawFillRect(43*7,23+21,(43*7)+7,23+7+21,150,150,150);
			DrawFillRect(43*7,23+28,(43*7)+7,23+7+28,200,200,200);
			DrawFillRect(43*7,23+35,(43*7)+7,23+7+35,50,0,0);
			DrawFillRect(43*7,23+42,(43*7)+7,23+7+42,150,0,0);
			DrawFillRect(43*7,23+49,(43*7)+7,23+7+49,200,0,0);
			DrawFillRect(43*7,23+56,(43*7)+7,23+7+56,255,0,0);
			DrawFillRect(43*7,23+63,(43*7)+7,23+7+63,0,50,0);
			DrawFillRect(43*7,23+70,(43*7)+7,23+7+70,0,150,0);
			DrawFillRect(43*7,23+77,(43*7)+7,23+7+77,0,200,0);
			DrawFillRect(43*7,23+84,(43*7)+7,23+7+84,0,255,0);
			DrawFillRect(43*7,23+91,(43*7)+7,23+7+91,0,0,50);
			DrawFillRect(43*7,23+98,(43*7)+7,23+7+98,0,0,150);
			DrawFillRect(43*7,23+105,(43*7)+7,23+7+105,0,0,200);
			DrawFillRect(43*7,23+112,(43*7)+7,23+7+112,0,0,255);
			DrawFillRect(43*7,23+119,(43*7)+7,23+7+119,50,50,0);
			DrawFillRect(43*7,23+126,(43*7)+7,23+7+126,150,150,0);
			DrawFillRect(43*7,23+133,(43*7)+7,23+7+133,200,200,0);
			DrawFillRect(43*7,23+140,(43*7)+7,23+7+140,255,255,0);
			DrawFillRect(43*7,23+147,(43*7)+7,23+7+147,0,50,50);
			DrawFillRect(43*7,23+154,(43*7)+7,23+7+154,0,150,150);
			DrawFillRect(43*7,23+161,(43*7)+7,23+7+161,0,200,200);
			DrawFillRect(43*7,23+168,(43*7)+7,23+7+168,0,255,255);
			DrawFillRect(43*7,23+175,(43*7)+7,23+7+175,100,50,0);
			DrawFillRect(43*7,23+182,(43*7)+7,23+7+182,150,100,0);
			DrawFillRect(43*7,23+189,(43*7)+7,23+7+189,200,150,0);
			//<--
			DrawFillRect(41*7+7,23+196,(41*7)+7+7,23+7+196,50,0,50);
			DrawFillRect(40*7+7,23+196,(40*7)+7+7,23+7+196,150,0,150);
			DrawFillRect(39*7+7,23+196,(39*7)+7+7,23+7+196,200,0,200);
			DrawFillRect(38*7+7,23+196,(38*7)+7+7,23+7+196,255,0,255);

			DrawFillRect(37*7+2+7,23+196+2,(37*7)+7-2+7,23+7+196-1,255,255,255);

			for (int i = 0;i<28;i++){
				DrawRect(43*7,23+(i*7),(43*7)+7,23+(i*7)+7,255,255,255);
			}
			for (int i=0;i<5;i++){
				DrawRect((42-i)*7,23+196,((42-i)*7)+7,23+7+196,255,255,255);
			}
			//Karet COlor
			if (cnv.nColor < 28) DrawRect(43*7-1,23+(cnv.nColor*7)-1,(43*7)+7+1,23+1+(cnv.nColor*7)+7,255,100,0);
			else DrawRect((42-(cnv.nColor-28))*7-1,23+196-1,((42-(cnv.nColor-28))*7)+7+1,23+1+196+7,255,100,0);
			
		}
	}
	SDL_Flip(screen);
}

