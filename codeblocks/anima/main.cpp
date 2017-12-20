#include <cstdlib>
#include <SDL/SDL.h>
#include <SDL/SDL_audio.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include "graph.h"

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
void MainMenu();
void SaveData(char dir[], char data[]);
void SaveData(char dir[], int data);
char* LoadData(char dir[]);
int SetScreenSize(int nSize);
//--------------------------VARIABLES-----------------------------------
SDL_Surface* screen;
SDL_Event event;
bool done = false;
int Room = 0;
int nScreenSize = 1; //1024x768
//--------------------------CONSTANTS-----------------------------------
const int ADOWN = 0;
const int ALEFT = 1;
const int AUP = 2;
const int ARIGHT = 3;
const int ASTOPDOWN = 4;
const int ASTOPLEFT = 5;
const int ASTOPUP = 6;
const int ASTOPRIGHT = 7;
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
        NImage BackgroundsMips[5];
        NImage ButtonTextures[2];
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
            

            Panel0.LoadBmp("data/interface/normal_panel.bmp");
            Panel0.Position(6,570);
            Panel0.Transparent();
            
            BackgroundsMips[0].LoadBmp("data/interface/background800.bmp");
            BackgroundsMips[1].LoadBmp("data/interface/background.bmp");
            BackgroundsMips[4].LoadBmp("data/interface/background1366.bmp");


            Panel1.LoadBmp("data/interface/mid_panel.bmp");
            Panel1.Position(6,570);
            Panel1.Transparent();
            
            ButtonTextures[0].LoadBmp("data/interface/normal_button.bmp");
            ButtonTextures[1].LoadBmp("data/interface/normal_button_on.bmp");

            Button0 = ButtonTextures[0];
            Button0.Position(20,592);
            Button0.Transparent();

            Button1 = ButtonTextures[0];
            Button1.Transparent();

            ModeButton0.LoadBmp("data/interface/mode_button0.bmp");
            ModeButton0.Position(190,592);
            ModeButton0.Transparent();

        };
        ~MMenu(){

        }
        void Draw(){
			if (nScreenSize == 0){
                Background = BackgroundsMips[0];
            }
            else if (nScreenSize == 1){
                Background = BackgroundsMips[1];
            }
            else if (nScreenSize == 4){
                Background = BackgroundsMips[4];
            }
            Background.Draw();
						//Room MAIN MENU
						if (Room == 0) {
							//if screensize 800x600
							if (nScreenSize == 0){
								//panel menu
								Panel0.Position(6,410);
								Panel0.Draw();
								//Button Start Load Sprite
								if (nSelected!=0){
										Button0 = ButtonTextures[0];
										Button0.Position(20,432);
										Button0.Transparent();
								} else if (nSelected==0) {
										Button0 = ButtonTextures[1];
										Button0.Position(20,432);
										Button0.Transparent();
								}
								Button0.Draw();
								
								//Button Settings Load Sprite
								if (nSelected!=1){
										Button1 = ButtonTextures[0];
										Button1.Position(20,468);
										Button1.Transparent();
								} else if (nSelected==1) {
										Button1 = ButtonTextures[1];
										Button1.Position(20,468);
										Button1.Transparent();
								}
								Button1.Draw();

								//Mode Button Position
								ModeButton0.Position(190,432);
								ModeButton0.Draw();
								
								//Fonts matrix draw in buttons 
								if (nSelected!=0)
										DrawWord(screen,1,"Jlbyjxyfz buhf",57,440,cWHITE);
								else if (nSelected==0)
										DrawWord(screen,1,"Jlbyjxyfz buhf",57,440,cBLACK);

								if (nSelected!=1)
										DrawWord(screen,1,"Yfcnhjqrb",67,476,cWHITE);
								else if (nSelected==1)
										DrawWord(screen,1,"Yfcnhjqrb",67,476,cBLACK);

								DrawWord(screen,1,"Fkmaf dth. 0.0.1",240,575,cBLACK);
							}
							//if screensize more (>) 800x600
							else if (nScreenSize >= 1){
								Panel0.Draw();

								if (nSelected!=0){
										Button0 = ButtonTextures[0];
										Button0.Position(20,592);
										Button0.Transparent();
								} else if (nSelected==0) {
										Button0 = ButtonTextures[1];
										Button0.Position(20,592);
										Button0.Transparent();
								}
								Button0.Draw();

								if (nSelected!=1){
										Button1 = ButtonTextures[0];
										Button1.Position(20,628);
										Button1.Transparent();
								} else if (nSelected==1) {
										Button1 = ButtonTextures[1];
										Button1.Position(20,628);
										Button1.Transparent();
								}
								Button1.Draw();

								ModeButton0.Draw();

								if (nSelected!=0)
										DrawWord(screen,1,"Jlbyjxyfz buhf",57,600,cWHITE);
								else if (nSelected==0)
										DrawWord(screen,1,"Jlbyjxyfz buhf",57,600,cBLACK);

								if (nSelected!=1)
										DrawWord(screen,1,"Yfcnhjqrb",67,636,cWHITE);
								else if (nSelected==1)
										DrawWord(screen,1,"Yfcnhjqrb",67,636,cBLACK);

								DrawWord(screen,1,"Fkmaf dth. 0.0.1",240,735,cBLACK);
							}
						}
						else if (Room == 99){
								if (nScreenSize==1){ //1024x768
										Panel1.Draw(306,210);
										Button0.Draw(314,220);
										DrawWord(screen,1,"Hfphtitybt^ 1024[768",323,230,cWHITE);
								}
								else if (nScreenSize==4){
										Panel1.Draw(506,210);
										Button0.Draw(514,220);
												DrawWord(screen,1,"Hfphtitybt^ 1366[768",523,230,cWHITE);
								}

								DrawWord(screen,1,"Dckexft ghj,ktv c yfcnhjqrfvb? lkz c,hjcf dctulf hf,jnftn ryjgrf",10,758,cRED);
								DrawWord(screen,0,"[F11]",464,758,cRED);
						}
				};

				void Mouse(int X, int Y){
						x = X;
						y = Y;
						if (Room == 0){
							if (nScreenSize == 0){
									if (((x>=20) and (y>=432)) and ((x<=184) and (y<=457)))
										nSelected = 0;
								else if (((x>=20) and (y>=469)) and ((x<=184) and (y<=494)))
										nSelected = 1;
								else
										nSelected = -1;
								}
							else{
								if (((x>=20) and (y>=592)) and ((x<=184) and (y<=617)))
										nSelected = 0;
								else if (((x>=20) and (y>=628)) and ((x<=184) and (y<=655)))
										nSelected = 1;
								else
										nSelected = -1;
							}
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


void SaveData(char dir[], char data[]){
    ofstream fout;
    fout.open(dir);
    fout << data << endl;
    fout.close();
}

void SaveData(char dir[], int data){
    ofstream fout;
    fout.open(dir);
    fout << data << endl;
    fout.close();
}

char* LoadData(char dir[]){
    ifstream fin;
    fin.open(dir);
    char lData[256];
    fin.getline(lData,256);
    return lData;
}


int SetScreenSize(int nSize){
    nScreenSize = nSize;
    ifstream fin;
    fin.open("data/settings.cfg");
    char lData[256];
    fin.getline(lData,256);
    fin.getline(lData,256);
    if (lData[6]=='1'){
        if (nScreenSize == 0){
            screen = SDL_SetVideoMode(800, 600, 24,SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_FULLSCREEN);
        }
        else if (nScreenSize == 1){
            screen = SDL_SetVideoMode(1024, 768, 24,SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_FULLSCREEN);
        }
        else if (nScreenSize == 2){
            screen = SDL_SetVideoMode(960, 540, 24,SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_FULLSCREEN);
        }
        else if (nScreenSize == 3){
            screen = SDL_SetVideoMode(1280, 720, 24,SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_FULLSCREEN);
        }
        else if (nScreenSize == 4){
            screen = SDL_SetVideoMode(1366, 768, 24,SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_FULLSCREEN);
        }
    }
    else {
        if (nScreenSize == 0){
            screen = SDL_SetVideoMode(800, 600, 24,SDL_HWSURFACE|SDL_DOUBLEBUF);
        }
        else if (nScreenSize == 1){
            screen = SDL_SetVideoMode(1024, 768, 24,SDL_HWSURFACE|SDL_DOUBLEBUF);
        }
        else if (nScreenSize == 2){
            screen = SDL_SetVideoMode(960, 540, 24,SDL_HWSURFACE|SDL_DOUBLEBUF);
        }
        else if (nScreenSize == 3){
            screen = SDL_SetVideoMode(1280, 720, 24,SDL_HWSURFACE|SDL_DOUBLEBUF);
        }
        else if (nScreenSize == 4){
            screen = SDL_SetVideoMode(1366, 768, 24,SDL_HWSURFACE|SDL_DOUBLEBUF);
        }
    }
    if (!screen){
        return 1;
    }
    return 0;
}


int Init(){
    ifstream fin;
    fin.open("data/settings.cfg");
    char sSize[256];
    fin.getline(sSize,256);
    fin.close();
    if (sSize[6]=='1'){
            nScreenSize = 1;
    }
    else if (sSize[6]=='0'){
            nScreenSize = 0;
    }
    else if (sSize[6]=='2'){
            nScreenSize = 2;
    }
    else if (sSize[6]=='3'){
            nScreenSize = 3;
    }
    else if (sSize[6]=='4'){
            nScreenSize = 4;
    }
    SDL_Init( SDL_INIT_VIDEO);
    atexit(SDL_Quit);
    SetScreenSize(nScreenSize);
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

