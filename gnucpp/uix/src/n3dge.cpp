#include "n3dge.h"
#include <SDL2/SDL.h> // Библиотека SDL 2
#include <SDL2/SDL_image.h>

#include <GL/gl.h> // Библиотека OpenGL
#include <GL/glu.h> // Библиотека GLU
#include <GL/glut.h>

TCube::TCube(){
  xm = 0.0f;
  ym = 0.0f;
  zm = 0.0f;

  x = 0.0f;
  y = 0.0f;
  z = 0.0f;

  r = 1.0f;
  g = 1.0f;
  b = 1.0f;
}

TCube::~TCube(){

}

void TCube::Color(float R,float G,float B){
  r=R;
  g=G;
  b=B;
}

void TCube::Turn(float Y){
  glRotatef(Y,0.0f,1.0f,0.0f);
}

void TCube::Draw(){

  glColor3f(r,g,b);
  glTranslatef(0.0f,0.0f,0.0f);

  glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex3f( x-1.0f,  y-1.0f,  z+1.0f );
    glTexCoord2f(1.0f, 1.0f); glVertex3f( x+1.0f,  y-1.0f,  z+1.0f );
    glTexCoord2f(1.0f, 0.0f); glVertex3f( x+1.0f, y+1.0f,  z+1.0f );
    glTexCoord2f(0.0f, 0.0f); glVertex3f( x-1.0f, y+1.0f,  z+1.0f);

    glTexCoord2f(0.0f, 1.0f); glVertex3f( x-1.0f,  y+1.0f,  z+1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( x-1.0f,  y+1.0f,  z-1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( x-1.0f, y-1.0f,  z-1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f( x-1.0f, y-1.0f,  z+1.0f);
    
    glTexCoord2f(0.0f, 1.0f); glVertex3f( x-1.0f, y-1.0f,  z+1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( x-1.0f, y-1.0f,  z-1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( x+1.0f, y-1.0f,  z-1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f( x+1.0f, y-1.0f,  z+1.0f);

    glTexCoord2f(0.0f, 1.0f); glVertex3f( x+1.0f, y-1.0f,  z+1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( x+1.0f, y-1.0f,  z-1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( x+1.0f, y+1.0f,  z-1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f( x+1.0f, y+1.0f,  z+1.0f);
    
    glTexCoord2f(0.0f, 1.0f); glVertex3f( x+1.0f, y+1.0f,  z+1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( x-1.0f, y+1.0f,  z+1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( x-1.0f, y+1.0f,  z-1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f( x+1.0f, y+1.0f,  z-1.0f);
    
    glTexCoord2f(0.0f, 1.0f); glVertex3f( x-1.0f, y+1.0f,  z-1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( x-1.0f, y-1.0f, z-1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( x+1.0f, y-1.0f,  z-1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f( x+1.0f, y+1.0f,  z-1.0f);
  glEnd();

  glLoadIdentity();

}

void TCube::Position(float X, float Y, float Z){
  x=X;
  y=Y;
  z=Z;
}