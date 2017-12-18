#include "graph.h"

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

void DrawMatrixDeColor(SDL_Surface *screen, char cMatrix[][8],int X, int Y, char cFColor ,char NColor){
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
	DrawMatrix(screen,cMatrix,X,Y);
}

void DrawMatrix(SDL_Surface *screen, char cMatrix[][8],int X, int Y){
	char cRead;
	int w = 8;
	int h = 8;
	for (int y=0;y<h;y++){
		for (int x=0;x<w;x++){
			cRead = cMatrix[y][x];
			if (cRead=='s'){}
			else if(cRead=='r'){
				DrawPixel4(screen,X+x, Y+y, 255, 0, 0);
			}
			else if(cRead=='g'){
				DrawPixel4(screen,X+x, Y+y, 0, 255, 0);
			}
			else if(cRead=='b'){
				DrawPixel4(screen,X+x, Y+y, 0, 0, 255);
			}
			else if(cRead=='W'){
				DrawPixel4(screen,X+x, Y+y, 255, 255, 255);
			}
			else if(cRead=='B'){
				DrawPixel4(screen,X+x, Y+y, 0, 0, 0);
			}
			else if(cRead=='G'){
				DrawPixel4(screen,X+x, Y+y, 100, 100, 100);
			}
			else if(cRead=='0'){
				DrawPixel4(screen,X+x, Y+y, 50, 50, 50);
			}
			else if(cRead=='1'){
				DrawPixel4(screen,X+x, Y+y, 150, 150, 150);
			}
			else if(cRead=='2'){
				DrawPixel4(screen,X+x, Y+y, 200, 200, 200);
			}
			else if(cRead=='3'){
				DrawPixel4(screen,X+x, Y+y, 50, 0, 0);
			}
			else if(cRead=='4'){
				DrawPixel4(screen,X+x, Y+y, 150, 0, 0);
			}
			else if(cRead=='5'){
				DrawPixel4(screen,X+x, Y+y, 200, 0, 0);
			}
			else if(cRead=='6'){
				DrawPixel4(screen,X+x, Y+y, 0, 50, 0);
			}
			else if(cRead=='7'){
				DrawPixel4(screen,X+x, Y+y, 0, 150, 0);
			}
			else if(cRead=='8'){
				DrawPixel4(screen,X+x, Y+y, 0, 200, 0);
			}
			else if(cRead=='9'){
				DrawPixel4(screen,X+x, Y+y, 0, 0, 50);
			}
			else if(cRead=='a'){
				DrawPixel4(screen,X+x, Y+y, 0, 0, 150);
			}
			else if(cRead=='c'){
				DrawPixel4(screen,X+x, Y+y, 0, 0, 200);
			}
			else if(cRead=='y'){
				DrawPixel4(screen,X+x, Y+y, 255, 255, 0);
			}
			else if(cRead=='d'){
				DrawPixel4(screen,X+x, Y+y, 50, 50, 0);
			}
			else if(cRead=='e'){
				DrawPixel4(screen,X+x, Y+y, 150, 150, 0);
			}
			else if(cRead=='f'){
				DrawPixel4(screen,X+x, Y+y, 200, 200, 0);
			}
			else if(cRead=='h'){
				DrawPixel4(screen,X+x, Y+y, 0, 50, 50);
			}
			else if(cRead=='k'){
				DrawPixel4(screen,X+x, Y+y, 0, 150, 150);
			}
			else if(cRead=='l'){
				DrawPixel4(screen,X+x, Y+y, 0, 200, 200);
			}
			else if(cRead=='m'){
				DrawPixel4(screen,X+x, Y+y, 0, 255, 255);
			}
			else if(cRead=='n'){
				DrawPixel4(screen,X+x, Y+y, 50, 0, 50);
			}
			else if(cRead=='o'){
				DrawPixel4(screen,X+x, Y+y, 150, 0, 150);
			}
			else if(cRead=='p'){
				DrawPixel4(screen,X+x, Y+y, 200, 0, 200);
			}
			else if(cRead=='q'){
				DrawPixel4(screen,X+x, Y+y, 255, 0, 255);
			}
			else if(cRead=='t'){
				DrawPixel4(screen,X+x, Y+y, 100, 50, 0);
			}
			else if(cRead=='u'){
				DrawPixel4(screen,X+x, Y+y, 200, 150, 0);
			}
			else if(cRead=='v'){
				DrawPixel4(screen,X+x, Y+y, 255, 200, 0);
			}
		}
	}
}

void DrawSym(SDL_Surface *screen, int lang, char sym,int x, int y, char color){
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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

				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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

				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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


				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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

				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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

				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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

				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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

				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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

				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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

				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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

				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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

				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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

				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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

				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);;
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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

				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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

				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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

				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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


				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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

				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
			} break;
			case 'F':{char cSym[8][8]={
						{'s','s','s','W','s','s','s','s'},
						{'s','s','W','s','W','s','s','s'},
						{'s','s','W','s','W','s','s','s'},
						{'s','W','s','s','s','W','s','s'},
						{'s','W','W','W','W','W','s','s'},
						{'s','W','s','s','s','W','s','s'},
						{'s','W','s','s','s','W','s','s'},
						{'s','W','s','s','s','W','s','s'}};
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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

				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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

				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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


				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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

				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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

				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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

				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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

				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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

				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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

				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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

				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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

				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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

				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
			} break;
			case 'Y':{char cSym[8][8]={
						{'s','W','s','s','s','W','s','s'},
						{'s','W','s','s','s','W','s','s'},
						{'s','W','s','s','s','W','s','s'},
						{'s','W','W','W','W','W','s','s'},
						{'s','W','s','s','s','W','s','s'},
						{'s','W','s','s','s','W','s','s'},
						{'s','W','s','s','s','W','s','s'},
						{'s','W','s','s','s','W','s','s'}};

				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
			} break;
			case 'Z':{char cSym[8][8]={
						{'s','s','W','W','W','W','s','s'},
						{'s','W','s','s','s','W','s','s'},
						{'s','W','s','s','s','W','s','s'},
						{'s','W','s','s','S','W','s','s'},
						{'s','s','W','W','W','W','s','s'},
						{'s','s','W','s','s','W','s','s'},
						{'s','W','s','s','s','W','s','s'},
						{'s','W','S','S','S','W','W','s'}};
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
			} break;
			case 'a':{char cSym[8][8]={
						{'s','s','s','s','s','s','s'},
						{'s','s','s','W','s','s','s'},
						{'s','s','W','W','W','s','s'},
						{'s','W','s','W','s','W','s'},
						{'s','W','s','W','s','W','s'},
						{'s','s','W','W','W','s','s'},
						{'s','s','s','W','s','s','s'},
						{'s','s','s','W','s','s','s'}};
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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

				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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

				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
			} break;
			case 'i':{char cSym[8][8]={
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','W','s','W','s','W','s'},
						{'s','W','s','W','s','W','s'},
						{'s','W','s','W','s','W','s'},
						{'s','W','s','W','s','W','s'},
						{'s','W','s','W','s','W','s'},
						{'s','W','W','W','W','W','s'}};
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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

				DrawMatrixDeColor(screen,cSym,x,y,'W',color);;
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

				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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

				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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

				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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

				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
			} break;
			case 'z':{char cSym[8][8]={
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','s','W','W','W','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','s','W','W','W','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','W','s','s','W','s','s'}};
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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

				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
			} break;
			case ',':{char cSym[8][8]={
						{'s','s','s','s','s','s','s'},
						{'s','s','W','W','W','s','s'},
						{'s','W','s','s','s','s','s'},
						{'s','W','s','s','s','s','s'},
						{'s','W','W','W','s','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','s','W','W','s','s','s'}};
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y+2,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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

				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
			} break;
			case '^':{char cSym[8][8]={
						{'s','s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s','s'},
						{'s','s','s','W','s','s','s','s'},
						{'s','s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s','s'},
						{'s','s','s','W','s','s','s','s'},
						{'s','s','s','s','s','s','s','s'}};

				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
			} break;
			case '&':{char cSym[8][8]={
						{'s','s','W','W','W','s','s'},
						{'s','W','s','s','s','W','s'},
						{'s','s','s','s','s','W','s'},
						{'s','s','s','s','W','s','s'},
						{'s','s','s','W','s','s','s'},
						{'s','s','s','W','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','s','s','W','s','s','s'}};
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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


				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
			} break;
			case '[':{char cSym[8][8]={
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','W','s','s','s','W','s'},
						{'s','s','W','s','W','s','s'},
						{'s','s','s','W','s','s','s'},
						{'s','s','s','W','s','s','s'},
						{'s','s','W','s','W','s','s'},
						{'s','W','s','s','s','W','s'}};
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
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
				DrawMatrixDeColor(screen,cSym,x,y,'W',color);
			} break;
		}
	}
}

void DrawWord(SDL_Surface *screen, int lang, char* szText,int X, int Y, char color){
	char rc;
	for (int i = 0;i<strlen(szText);i++){
		rc = szText[i];
		DrawSym(screen,lang,rc,X+(i*7),Y,color);
	}
}

void DrawPixel4(SDL_Surface *screen,int X, int Y, Uint8 R, Uint8 G, Uint8 B){
	int x = X;
	int y = Y;
	DrawPixel(screen, x,y, R,G,B);
}
