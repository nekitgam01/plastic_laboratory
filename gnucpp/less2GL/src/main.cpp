#include <SDL2/SDL.h> // Библиотека SDL 2
#include <SDL2/SDL_image.h>

#include <GL/gl.h> // Библиотека OpenGL
#include <GL/glu.h> // Библиотека GLU
#include <GL/glut.h>
#include <stdio.h>
#include <iostream>

using namespace std;

//ГЛОБАЛЬНЫЕ ПЕРМЕННЫЕ
SDL_Window *window; // задаем окно для SDL
const int width = 640;  // ширина окна
const int height = 480; // высота окна
bool running = true;    //Выключатель игры
SDL_Event event; // события SDL
float xrot=0.0f;
float yrot=0.0f;
float xspeed = 0.0f;
float yspeed = 0.0f;
float z = -5.0f;

float rtri = 0.0f;
float rquad = 0.0f;
bool fullscreen = true;
bool light;             //Свет вкл/выкл
bool lp;                //L нажата
bool fp;                //F нажата

GLuint filter = 0; //Какой фильтр использовать, неарест, сглаженный, качественный
GLuint Texture[3]; //Место для одной текстуры

float LightAmbient[] = {0.2f,0.2f,0.2f,1.0f};   //Фоновый йцвет
float LightDiffuse[] = {1.0f,1.0f,1.0f,1.0f};   //Диффузный цвет

float LightPosition[] = {0.0f,0.0f,2.0f,1.0f};  //Позиция света

SDL_DisplayMode displayMode;

//ПРЕДОБЪЯВЛЕНИЕ
void init();
void drawGLSCene();
void Events();
int LoadGLTextures();

void Events(){
	while ( SDL_PollEvent(&event) ){ // начинаем обработку событий
		switch(event.type){ // смотрим:
			case SDL_QUIT: // если произошло событие закрытия окна, то завершаем работу программы
				running = false;
			break;

			case SDL_KEYDOWN: // если нажата клавиша
				switch(event.key.keysym.sym){ // смотрим какая
					case SDLK_ESCAPE: // клавиша ESC
						running = false;            // завершаем работу программы
					break;
					case SDLK_UP:
						z+=0.7f;
					break;
					case SDLK_DOWN:
						z-=0.6f;
					break;
					case SDLK_LEFT:
						yspeed -= 1.0f;
					break;
					case SDLK_RIGHT:
						yspeed += 1.0f;
					break;
					case SDLK_PAGEUP:
						xspeed -= 1.0f;
					break;
					case SDLK_PAGEDOWN:
						xspeed += 1.0f;
					break;
					case SDLK_f:
					
					break;
				}
			break;
			case SDL_KEYUP: // если нажата клавиша
			switch(event.key.keysym.sym){ // смотрим какая
				case SDLK_UP:

				break;
				case SDLK_DOWN:

				break;
				case SDLK_LEFT:

				break;
				case SDLK_RIGHT:

				break;
				case SDLK_F11:
					if (fullscreen==true)
						fullscreen = false;
					else
						fullscreen = true;
				break;
				case SDLK_l:
					if (light)
						light = false;
					else
						light = true;
				break;
				case SDLK_f:
					if (filter == 1)
						filter = 0;
					else if (filter == 0)
						filter = 1;
				break;
			}
		break;
		} 

		if (!light)               // Если не свет	
		{
			glDisable(GL_LIGHTING);  // Запрет освещения
	  }
		else                      // В противном случае
		{
			glEnable(GL_LIGHTING);   // Разрешить освещение
		}

		//if (fullscreen)
		
	}
}

void init(){

	// Инициализация SDL
	if ( SDL_Init(SDL_INIT_VIDEO) < 0 ){ 
	 	cout << "Unable to init SDL, error: " << SDL_GetError() << endl;
	 	exit(1);
	} 
	
	// Включаем двойной буфер, настраиваем цвета

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 6);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);

	// Создаем окно с заголовком "Cube", размером 640х480 и расположенным по центру экрана.

	window = SDL_CreateWindow("Cube", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	
	SDL_GLContext glcontext = SDL_GL_CreateContext(window);              // создаем контекст OpenGL
	
	if(window == NULL){	
		exit(1);
	}

	// Инициализация OpenGL
	int nNull = LoadGLTextures();
	glEnable(GL_TEXTURE_2D);                                             //Включаем работу с текстурами

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);                                // устанавливаем фоновый цвет на черный
	glClearDepth(1.0);
	glDepthFunc(GL_LESS);                                              //Z
	glEnable(GL_DEPTH_TEST);                                             // включаем тест глубины
	glShadeModel(GL_SMOOTH);    
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NEAREST);                                         //Сглаживание

	glLightfv(GL_LIGHT1, GL_AMBIENT,LightAmbient); //Установка фонового цвета
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse); //Установка диффузногоц вета
	glLightfv(GL_LIGHT1,GL_POSITION, LightPosition); //Устанавливаем положение светового источника.

	glEnable(GL_LIGHT1);

	glMatrixMode(GL_PROJECTION);
	//glBlendFunc(GL_SRC_ALPHA,GL_ONE);
	//glHINT(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);                 //Улучшенные вычисления перспективы
	//glDepthFunc(GL_LEQUAL);                                              //Тип теста глубины
	glLoadIdentity();
	gluPerspective(45.0f, (float) width / (float) height, 0.1f, 100.0f); // настраиваем трехмерную перспективу
	glMatrixMode(GL_MODELVIEW);                                          // переходим в трехмерный режим
	glLoadIdentity();
}

int main(int argc, char *argv[]){   

	init();                                                              // инициализация

	while(running){ 
		Events();                                                          //Читаем события
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);                //Очищаем экран и буфер глубины
		glLoadIdentity();                                                  //Сброс просмотра
		drawGLSCene();                                                     //Отрисовываем сцену
		glFlush();                                                         //Перерисовываем буфер
		SDL_GL_SwapWindow(window);                                         //Отрисовываем буфер в контексте
	}

	SDL_Quit();                                                          // завершаем работу SDL и выходим
	exit(0);
}

void drawGLSCene(){

	glTranslatef(0.0f,0.0f,z);

	glRotatef(xrot,1.0f,0.0f,0.0f);
	glRotatef(yrot,0.0f,1.0f,0.0f);
	//glRotatef(zrot,0.0f,0.0f,1.0f);

	glBindTexture(GL_TEXTURE_2D,Texture[filter]);

	glBegin(GL_QUADS);
		glNormal3f(0.0f,0.0f,1.0f);  //Нормаль указывает на нас
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  -1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  -1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, 1.0f,  1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f,  1.0f);

		glNormal3f(0.0f,1.0f,0.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  -1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		
		glNormal3f(0.0f,0.0f,-1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f,  -1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f,  -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f,  1.0f);

		glNormal3f(0.0f,-1.0f,0.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, -1.0f,  -1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f,  -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, 1.0f,  1.0f);
		
		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, 1.0f,  -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, 1.0f,  -1.0f);
		
		glNormal3f( -1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f,  -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f,  -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, 1.0f,  -1.0f);
	glEnd();

	xrot+=xspeed;
	yrot+=yspeed;
}

/*Загрузка текстуры*/
int LoadGLTextures(/*int TexIndex, char szDir[]*/){
  /* Status indicator */
  int Status = false;

  /* Create storage space for the texture */
  SDL_Surface *TextureImage[1];

  // Load The Bitmap, Check For Errors, If Bitmap's Not Found Quit

  //if ( ( TextureImage[0] = SDL_LoadBMP( "cb1.bmp" ) ) )
  if ( ( TextureImage[0] = IMG_Load( "cb.png" ) ) )
	{
    /* Set the status to true */
    Status = true;

    /* Create The Texture */
    glGenTextures( 3, &Texture[0]);

    /* Typical Texture Generation Using Data From The Bitmap */
    glBindTexture( GL_TEXTURE_2D, Texture[0]);

    /* Generate The Texture */
    glTexImage2D( GL_TEXTURE_2D, 0, 3, TextureImage[0]->w,
          TextureImage[0]->h, 0, GL_RGB,
          GL_UNSIGNED_BYTE, TextureImage[0]->pixels );

    /* Linear Filtering */
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
		

		/* Typical Texture Generation Using Data From The Bitmap */
    glBindTexture( GL_TEXTURE_2D, Texture[1]);
		
		/* Generate The Texture */
		glTexImage2D( GL_TEXTURE_2D, 0, 3, TextureImage[0]->w,
					TextureImage[0]->h, 0, GL_RGB,
					GL_UNSIGNED_BYTE, TextureImage[0]->pixels );
		
		/* Linear Filtering */
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	
	}

  // Free up any memory we may have used
  if ( TextureImage[0] )
    SDL_FreeSurface( TextureImage[0] );

  return Status;
}
