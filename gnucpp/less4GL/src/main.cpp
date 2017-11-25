#include <SDL2/SDL.h> // Библиотека SDL 2
#include <SDL2/SDL_image.h>

#include <GL/gl.h> // Библиотека OpenGL
#include <GL/glu.h> // Библиотека GLU
#include <GL/glut.h>
#include <stdio.h>
#include <iostream>

using namespace std;

//ГЛОБАЛЬНЫЕ ПЕРМЕННЫЕ

const int width = 640;  // ширина окна
const int height = 480; // высота окна
const int num = 50; //Количество звезд

bool light;             //Свет вкл/выкл
bool blend = false;
bool running = true;    //Выключатель игры
bool twinkle = false;   //Возвращающиеся звезды

GLuint filter = 0; //Какой фильтр использовать, неарест, сглаженный, качественный
GLuint Texture[3]; //Место для одной текстуры
int loop;

float LightAmbient[] = {0.2f,0.2f,0.2f,1.0f};   //Фоновый йцвет
float LightDiffuse[] = {1.0f,1.0f,1.0f,1.0f};   //Диффузный цвет
float LightPosition[] = {0.0f,0.0f,2.0f,1.0f};  //Позиция света

float zoom = -15.0f;
float tilt = 90.0f;
float spin = 0.0f;

SDL_Event event; // события SDL
SDL_DisplayMode displayMode;
SDL_Window *window; // задаем окно для SDL

//СТРУКТУРЫ
typedef struct{                   //Создаем структуру для звезд
	int r,g,b;                      	//Цвет звезды
	float dist;                     	//Растояние от центра
	float angle;                     	//Текущий угол звезды
} stars;                          //Им структыр stars
stars star[num];                   //Массив звезд (струткр)


//ПРЕДОБЪЯВЛЕНИЕ
void init();
void drawGLSCene();
void Events();
int LoadGLTextures(char szDir[]);




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
						tilt-=0.5f;             // Вращаем экран вверх
					break;
					case SDLK_DOWN:
						tilt+=0.5f;             // Вращаем экран вниз
					break;
					case SDLK_LEFT:

					break;
					case SDLK_RIGHT:

					break;
					case SDLK_PAGEUP:
						zoom-=0.2f;             // Уменьшаем
					break;
					case SDLK_PAGEDOWN:
						zoom+=0.2f;             // Увеличиваем
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
				case SDLK_b:
					if (blend==true)
						blend = false;
					else
						blend = true;
				break;
				case SDLK_F11:

				break;
				case SDLK_t:
					twinkle=!twinkle;       // Меняем значение twinkle на обратное
				break;
				case SDLK_f:

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
		if(blend)                        // blend TRUE?
		{
			glEnable(GL_BLEND);        // Включаем смешивание
			glDisable(GL_DEPTH_TEST);  // Выключаем тест глубины
		}
		else                            
		{
			glDisable(GL_BLEND);        // Выключаем смешивание
			glEnable(GL_DEPTH_TEST);    // Включаем тест глубины
		}
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
	char dr[] = "data/star.png"; 
	int nNull = LoadGLTextures(dr);
	glEnable(GL_TEXTURE_2D);                                             //Включаем работу с текстурами

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);                                // устанавливаем фоновый цвет на черный
	glClearDepth(1.0);
	//glDepthFunc(GL_LESS);                                              //Z
	//glEnable(GL_DEPTH_TEST);                                             // включаем тест глубины
	glShadeModel(GL_SMOOTH);    
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NEAREST);                                         //Сглаживание

	glColor4f(1.0f,1.0f,1.0f,0.5f);   // Полная яркость, 50% альфа (НОВОЕ)
	glBlendFunc(GL_SRC_ALPHA,GL_ONE); // Функция смешивания для непрозрачности,
																		// базирующаяся на значении альфы(НОВОЕ)
  glEnable(GL_BLEND);        // Включаем смешивание

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

	for (loop=0;loop<num; loop++){
		star[loop].angle = 0.0f;   //Устанавливаем все углы равными 0
		star[loop].dist = (float(loop)/num*5); //Устанавливаем расстояние отцентра
		star[loop].r = rand()%256;  //присваиваем случайное значение красного
		star[loop].g = rand()%256;  //зел
		star[loop].b = rand()%256;  //синий
	}
}

int main(int argc, char *argv[]){   

	init();                                                              // инициализация

	while(running){ 
		Events();                                                          //Читаем события
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);                //Очищаем экран и буфер глубины
		//glLoadIdentity();                                                  //Сброс просмотра
		drawGLSCene();                                                     //Отрисовываем сцену
		glFlush();                                                         //Перерисовываем буфер
		SDL_GL_SwapWindow(window);                                         //Отрисовываем буфер в контексте
	}

	SDL_Quit();                                                          // завершаем работу SDL и выходим
	exit(0);
}

void drawGLSCene(){
	// Очищаем буфер цвета и глубины
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Выбираем нашу текстуру
	glBindTexture(GL_TEXTURE_2D, Texture[0]);

	for (loop=0; loop<num; loop++)               // Цикл по всем звездам
	{
					// Обнуляем видовую матрицу (Model Matrix) перед каждой звездой
					glLoadIdentity();
					// Переносим по оси z на 'zoom'
					glTranslatef(0.0f,0.0f,zoom);
					// Вращаем вокруг оси x на угол 'tilt'
					glRotatef(tilt,1.0f,0.0f,0.0f);

					// Поворачиваем на угол звезды вокруг оси y
					glRotatef(star[loop].angle,0.0f,1.0f,0.0f);
					// Двигаемся вперед по оси x
					glTranslatef(star[loop].dist,0.0f,0.0f);

					glRotatef(-star[loop].angle,0.0f,1.0f,0.0f);
					// Отменяет текущий поворот звезды
					glRotatef(-tilt,1.0f,0.0f,0.0f);        // Отменяет поворот экрана

					if (twinkle)                            // Если Twinkling включен 
					{
									// Данный цвет использует байты
									glColor4ub(star[(num-loop)-1].r,star[(num-loop)-1].g,
									star[(num-loop)-1].b,255);
									glBegin(GL_QUADS);// Начинаем рисовать текстурированый квадрат
													glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,-1.0f, 0.0f);
													glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,-1.0f, 0.0f);
													glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f, 1.0f, 0.0f);
													glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 0.0f);
									glEnd();                                // Закончили рисовать
					}

					glRotatef(spin,0.0f,0.0f,1.0f);// Поворачиваем звезду по оси z
					// Цвет использует байты
					glColor4ub(star[loop].r,star[loop].g,star[loop].b,255);
					glBegin(GL_QUADS);              // Начинаем рисовать текстурный квадрат
									glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,-1.0f, 0.0f);
									glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,-1.0f, 0.0f);
									glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f, 1.0f, 0.0f);
									glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 0.0f);
					glEnd();  

					spin+=0.01f;                    // Используется для вращения звезды
					star[loop].angle+=float(loop)/num;// Меняем угол звезды
					star[loop].dist-=0.01f; // Меняем растояние до центра

					if (star[loop].dist<0.0f)    // Звезда в центре экрана?
					{
									star[loop].dist+=5.0f;  // Перемещаем на 5 единиц от центра
									// Новое значение красной компоненты цвета
									star[loop].r=rand()%256;
									// Новое значение зеленной компоненты цвета
									star[loop].g=rand()%256;
									// Новое значение синей компоненты цвета
									star[loop].b=rand()%256;
					}
	}
}

/*Загрузка текстуры*/
int LoadGLTextures(char szDir[]){
  /* Status indicator */
  int Status = false;

  /* Create storage space for the texture */
  SDL_Surface *TextureImage[1];

  // Load The Bitmap, Check For Errors, If Bitmap's Not Found Quit

  //if ( ( TextureImage[0] = SDL_LoadBMP( "cb1.bmp" ) ) )
  if ( ( TextureImage[0] = IMG_Load( szDir ) ) )
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
