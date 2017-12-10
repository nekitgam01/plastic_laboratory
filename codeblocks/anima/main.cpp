#include <cstdlib>
#include <SDL/SDL.h>
#include <SDL/SDL_audio.h>
#include <iostream>
#include <fstream>
#include <cstring>

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
void DrawMatrixDeColor(char cMatrix[][8],int X, int Y, char cFColor ,char NColor);
void DrawMatrixDeColor(char cMatrix[][16],int X, int Y, char cFColor ,char NColor);
void DrawMatrixDeColor(char cMatrix[][32],int X, int Y, char cFColor ,char NColor);
void DrawMatrix(char cMatrix[][8],int X, int Y);
void DrawMatrix(char cMatrix[][16],int X, int Y);
void DrawMatrix(char cMatrix[][32],int X, int Y);
void MatrixDeColor(char cMatrix[][32], char cFColor ,char NColor);
void MatrixDeColor(char cMatrix[][16], char cFColor ,char NColor);
void MatrixDeColor(char cMatrix[][8], char cFColor ,char NColor);
void DrawSym(int lang, char sym,int x, int y, char color);
void DrawWord(int lang, char* szText,int X, int Y, char color);
void MainMenu();
void SaveData(char dir[], char data[]);
char* LoadData(char dir[], char data[]);
//--------------------------VARIABLES-----------------------------------
SDL_Surface* screen;
SDL_Event event;
bool done = false;
int Room = 0;
int nScreenSize = 2; //1024x768
//--------------------------CONSTANTS-----------------------------------
const int ADOWN = 0;
const int ALEFT = 1;
const int AUP = 2;
const int ARIGHT = 3;
const int ASTOPDOWN = 4;
const int ASTOPLEFT = 5;
const int ASTOPUP = 6;
const int ASTOPRIGHT = 7;

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
class NImage{
    private:
        SDL_Surface* bmp;
        SDL_Rect dstrect;
    public:
        //var
        int x;
        int y;
        //func
        NImage(){
            x = 0;
            y = 0;
        };
        ~NImage(){
            //SDL_FreeSurface(bmp);
        }
        NImage(char dir[]){
            x = 0;
            y = 0;
            this->LoadBmp(dir);
        };
        NImage(char dir[], int X, int Y){
            x = X;
            y = Y;
            this->LoadBmp(dir);
        };
        NImage(char dir[], int X, int Y, SDL_Surface* parnt){
            x = X;
            y = Y;
            this->LoadBmp(dir);
        };
        void Transparent(){
            SDL_SetColorKey(bmp, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(bmp->format, 0xFF, 0xFF,0xFF));
        }
        int LoadBmp(char dir[]){
            bmp = SDL_LoadBMP(dir);
            return 0;
        };
        void Position(int X, int Y){
            x = X;
            y = Y;
        }
        void Draw(){
            dstrect.x = x;
            dstrect.y = y;
            SDL_BlitSurface(bmp, 0, screen, &dstrect);
        }
        void Draw(int X, int Y){
            x = X;
            y = Y;
            dstrect.x = x;
            dstrect.y = y;
            SDL_BlitSurface(bmp, 0, screen, &dstrect);
        }
        void Draw(SDL_Surface* prnt,int X, int Y){
            x = X;
            y = Y;
            dstrect.x = x;
            dstrect.y = y;
            SDL_BlitSurface(bmp, 0, prnt, &dstrect);
        }
        //void Destroy(){
        //    SDL_FreeSurface(bmp);
        //   delete this;
        //}
};

class NPersonage{
    private:
        NImage imgPersonage[16];
        void AddPicStack(char dir[], char nam[], int index){
            int ln = strlen(dir);
            ln++;
            char ind[ln];
            for (int i = 0; i<ln;i++){
                ind[i] = dir[i];
            }
            strcat(ind,nam);
            imgPersonage[index].LoadBmp(ind);
            imgPersonage[index].Transparent();
        };
    public:
        int x;
        int y;
        int Iteration;
        NPersonage(){
            x = 0;
            y = 0;
            Iteration = -1;
        };
        void GenPer(){
            int r = 0;
            if (r == 0){
                LoadSprites("data/pers/0/");
            }
        }
        int LoadSprites(char dir[]){
                this->AddPicStack(dir, "d0.bmp",0);
                this->AddPicStack(dir, "d1.bmp",1);
                this->AddPicStack(dir, "d0.bmp",2);
                this->AddPicStack(dir, "d2.bmp",3);

                this->AddPicStack(dir, "l0.bmp",4);
                this->AddPicStack(dir, "l1.bmp",5);
                this->AddPicStack(dir, "l0.bmp",6);
                this->AddPicStack(dir, "l2.bmp",7);

                this->AddPicStack(dir, "u0.bmp",8);
                this->AddPicStack(dir, "u1.bmp",9);
                this->AddPicStack(dir, "u0.bmp",10);
                this->AddPicStack(dir, "u2.bmp",11);

                this->AddPicStack(dir, "r0.bmp",12);
                this->AddPicStack(dir, "r1.bmp",13);
                this->AddPicStack(dir, "r0.bmp",14);
                this->AddPicStack(dir, "r2.bmp",15);

            return 0;
        };
        void Position(int X, int Y){
            x = X;
            y = Y;
        };
        void Animate(int rot){
            if (rot == ASTOPUP) imgPersonage[8].Draw(x,y);
            else if (rot == ASTOPLEFT) imgPersonage[4].Draw(x,y);
            else if (rot == ASTOPDOWN) imgPersonage[0].Draw(x,y);
            else if (rot == ASTOPRIGHT) imgPersonage[12].Draw(x,y);

            Iteration++;
            if (rot == ADOWN){
                if ((Iteration>=0) and (Iteration<=9))
                    imgPersonage[0].Draw(x,y);
                if ((Iteration>=10) and (Iteration<=19))
                    imgPersonage[1].Draw(x,y);
                if ((Iteration>=20) and (Iteration<=29))
                    imgPersonage[2].Draw(x,y);
                if ((Iteration>=30) and (Iteration<=39))
                    imgPersonage[3].Draw(x,y);
            }
            else if (rot == ALEFT){
                if ((Iteration>=0) and (Iteration<=9))
                    imgPersonage[4].Draw(x,y);
                if ((Iteration>=10) and (Iteration<=19))
                    imgPersonage[5].Draw(x,y);
                if ((Iteration>=20) and (Iteration<=29))
                    imgPersonage[6].Draw(x,y);
                if ((Iteration>=30) and (Iteration<=39))
                    imgPersonage[7].Draw(x,y);
            }
            else if (rot == AUP){
                if ((Iteration>=0) and (Iteration<=9))
                    imgPersonage[8].Draw(x,y);
                if ((Iteration>=10) and (Iteration<=19))
                    imgPersonage[9].Draw(x,y);
                if ((Iteration>=20) and (Iteration<=29))
                    imgPersonage[10].Draw(x,y);
                if ((Iteration>=30) and (Iteration<=39))
                    imgPersonage[11].Draw(x,y);
            }
            else if (rot == ARIGHT){
                if ((Iteration>=0) and (Iteration<=9))
                    imgPersonage[12].Draw(x,y);
                if ((Iteration>=10) and (Iteration<=19))
                    imgPersonage[13].Draw(x,y);
                if ((Iteration>=20) and (Iteration<=29))
                    imgPersonage[14].Draw(x,y);
                if ((Iteration>=30) and (Iteration<=39))
                    imgPersonage[15].Draw(x,y);
            }
            if (Iteration == 39) Iteration = -1;

        }
        void Draw(int rot){
                this->Animate(rot);
        };
        void Motion(int rot){
            if (rot == AUP){
                y--;
            }
            else if (rot == ALEFT){
                x--;
            }
            else if (rot == ADOWN){
                y++;
            }
            else if (rot == ARIGHT){
                x++;
            }
            Draw(rot);
        };

};
//----------------------------OBJECTS-----------------------------------
NPersonage nn;
//----------------------------ROOMS-------------------------------------
//Menu and LOADER
class MMenu{
    private:
        NImage Background;
        NImage Panel0;
        NImage Panel1;
        NImage Button0;
        NImage Button1;
        NImage ModeButton0;
        int nSelected;
        int x;
        int y;
    public:
        MMenu(){
            x = 0;
            y = 0;
            nSelected = -1;
            Background.LoadBmp("data/interface/background.bmp");

            Panel0.LoadBmp("data/interface/normal_panel.bmp");
            Panel0.Position(6,570);
            Panel0.Transparent();

            Panel1.LoadBmp("data/interface/mid_panel.bmp");
            Panel1.Position(6,570);
            Panel1.Transparent();

            Button0.LoadBmp("data/interface/normal_button.bmp");
            Button0.Position(20,592);
            Button0.Transparent();

            Button1.LoadBmp("data/interface/normal_button.bmp");
            Button1.Transparent();

            ModeButton0.LoadBmp("data/interface/mode_button0.bmp");
            ModeButton0.Position(190,592);
            ModeButton0.Transparent();
        };
        ~MMenu(){

        }
        void Draw(){
            Background.Draw();
            if (Room == 0) {
                Panel0.Draw();

                if (nSelected!=0){
                    Button0.LoadBmp("data/interface/normal_button.bmp");
                    Button0.Position(20,592);
                    Button0.Transparent();
                } else if (nSelected==0) {
                    Button0.LoadBmp("data/interface/normal_button_on.bmp");
                    Button0.Position(20,592);
                    Button0.Transparent();
                }
                Button0.Draw();

                if (nSelected!=1){
                    Button1.LoadBmp("data/interface/normal_button.bmp");
                    Button1.Position(20,628);
                    Button1.Transparent();
                } else if (nSelected==1) {
                    Button1.LoadBmp("data/interface/normal_button_on.bmp");
                    Button1.Position(20,628);
                    Button1.Transparent();
                }
                Button1.Draw();

                ModeButton0.Draw();

                if (nSelected!=0)
                    DrawWord(1,"Jlbyjxyfz buhf",57,600,cWHITE);
                else if (nSelected==0)
                    DrawWord(1,"Jlbyjxyfz buhf",57,600,cBLACK);

                if (nSelected!=1)
                    DrawWord(1,"Yfcnhjqrb",67,636,cWHITE);
                else if (nSelected==1)
                    DrawWord(1,"Yfcnhjqrb",67,636,cBLACK);

                DrawWord(1,"Fkmaf dth. 0.0.1",240,735,cBLACK);
            }
            else if (Room == 99){
                if (nScreenSize==1){ //1024x768
                    Panel1.Draw(306,210);
                    Button0.Draw(314,220);
                    if (nScreenSize==1){
                        DrawWord(1,"Hfphtitybt^ 1024[768",323,230,cWHITE);
                    }
                    if (nScreenSize==2){
                        DrawWord(1,"Hfphtitybt^ 1366[768",323,230,cWHITE);
                    }
                }

                DrawWord(1,"Dckexft ghj,ktv c yfcnhjqrfvb? lkz c,hjcf dctulf hf,jnftn ryjgrf",10,758,cRED);
                DrawWord(0,"[F11]",464,758,cRED);
            }
        };

        void Mouse(int X, int Y){
            x = X;
            y = Y;
            if (Room == 0){
                if (((x>=20) and (y>=592)) and ((x<=184) and (y<=617)))
                    nSelected = 0;
                else if (((x>=20) and (y>=628)) and ((x<=184) and (y<=655)))
                    nSelected = 1;
                else
                    nSelected = -1;
            }
            else if (Room == 99){

            }
        };
        void MouseDown(){
            if (nSelected == 0){
                Room = 1;
            } else if (nSelected == 1){
                Room = 99;
            }
        };
        void KeyDown(int nKey){

        };
        void Destroy(){
            delete this;
        }
};

class Pause{
    private:

    public:

};

class WorldAnalisator{
    private:
        int mx;
        int my;
        int px;
        int py;
        NImage wrender[4]; //Рендер 4 сторон видимых частей
    public:
        WorldAnalisator(){
            mx = 0;
            my = 0;
            px = 0;
            py = 0;
            wrender[0].LoadBmp("data/world/w0.bmp");
        };
        ~WorldAnalisator(){

        };
        void Draw(){
            //px++;
            //py++;
            wrender[0].Draw(px,py);
        };

        void Operate(){

        };
        void Mouse(int X, int Y){
            mx = X;
            my = Y;
        };
        void MouseDown(){

        };
        void MouseUp(){

        };
        void KeyDown(int key){

        }
        void KeyUp(int key){

        }
        void Destroy(){
            delete this;
        }
};
WorldAnalisator worlda;

MMenu menu;
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
						{'s','W','W','W','W','W','s','s'},
						{'s','W','s','s','s','W','s','s'},
						{'s','W','s','s','s','W','s','s'},
						{'s','W','s','s','s','W','s','s'},
						{'s','W','s','s','s','W','s','s'}};

				DrawMatrixDeColor(cSym,x,y,'W',color);
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
				DrawMatrixDeColor(cSym,x,y,'W',color);
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
						{'s','W','s','W','s','W','s'},
						{'s','W','s','W','s','W','s'},
						{'s','W','s','W','s','W','s'},
						{'s','W','s','W','s','W','s'},
						{'s','W','s','W','s','W','s'},
						{'s','W','W','W','W','W','s'}};
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
						{'s','s','W','W','W','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','s','W','W','W','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','W','s','s','W','s','s'}};
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
						{'s','s','W','W','W','s','s'},
						{'s','W','s','s','s','s','s'},
						{'s','W','s','s','s','s','s'},
						{'s','W','W','W','s','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','W','s','s','W','s','s'},
						{'s','s','W','W','s','s','s'}};
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
						{'s','s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s','s'},
						{'s','s','s','W','s','s','s','s'},
						{'s','s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s','s'},
						{'s','s','s','W','s','s','s','s'},
						{'s','s','s','s','s','s','s','s'}};

				DrawMatrixDeColor(cSym,x,y,'W',color);
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
						{'s','s','s','s','s','s','s'},
						{'s','s','s','s','s','s','s'},
						{'s','W','s','s','s','W','s'},
						{'s','s','W','s','W','s','s'},
						{'s','s','s','W','s','s','s'},
						{'s','s','s','W','s','s','s'},
						{'s','s','W','s','W','s','s'},
						{'s','W','s','s','s','W','s'}};
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

void DrawWord(int lang, char* szText,int X, int Y, char color){
	char rc;
	for (int i = 0;i<strlen(szText);i++){
		rc = szText[i];
		DrawSym(lang,rc,X+(i*7),Y,color);
	}
}

void DrawPixel4(int X, int Y, Uint8 R, Uint8 G, Uint8 B){
	int x = X;
	int y = Y;
	DrawPixel(screen, x,y, R,G,B);
}

void SaveData(char dir[], char data[]){
    ofstream fout;
    fout << data << endl;
    fout.close();
}

char* LoadData(char dir[], char data[]){
    ifstream fin;
    char lData[256];
    fin.getline(lData,256);
    return lData;
}

int Init(){
    SDL_Init( SDL_INIT_VIDEO);
    atexit(SDL_Quit);
    if (nScreenSize == 1){
        screen = SDL_SetVideoMode(1024, 768, 24,SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_FULLSCREEN);
    }
    else if (nScreenSize == 2){
        screen = SDL_SetVideoMode(1366, 768, 24,SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_FULLSCREEN);
    }
    SDL_WM_SetCaption("Anima","Anima");
    return 0;
}
//----------------------------GAME--------------------------------------
int main ( int argc, char** argv ){
	Init();

    //Инициализация
    {

    }

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
              if (event.key.keysym.sym == SDLK_F12)
                  done = true;
                  break;
          }
          case SDL_MOUSEMOTION:
            {
                if (Room == 0){
                    menu.Mouse(event.motion.x, event.motion.y);
                }
                else if (Room == 1){
                    worlda.Mouse(event.motion.x, event.motion.y);
                }
                break;
            }
          case SDL_MOUSEBUTTONDOWN:
            {
                if (Room == 0){
                    menu.MouseDown();
                }
                else if (Room == 1){
                    worlda.MouseDown();
                }
                break;
            }
       }
    }
}

void Draw(){
    SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 100, 200));
	{
        if ((Room == 0) || (Room == 99)){
            menu.Draw();
        }
        else if (Room == 1){
            worlda.Draw();
        }
	}
    SDL_Flip(screen);
}

