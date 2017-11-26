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
//--------------------------VARIABLES-----------------------------------
SDL_Surface* screen;
SDL_Event event;
bool done = false;

//--------------------------CONSTANTS-----------------------------------

//----------------------------CLASSES-----------------------------------

//----------------------------OBJECTS-----------------------------------

//----------------------------ROOMS-------------------------------------

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

int Init(){
    SDL_Init( SDL_INIT_VIDEO);
    atexit(SDL_Quit);
    screen = SDL_SetVideoMode(800, 600, 24,SDL_HWSURFACE|SDL_DOUBLEBUF);
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

	}
    SDL_Flip(screen);
}

