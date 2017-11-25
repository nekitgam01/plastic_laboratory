#ifndef N3DGE_H_
#define N3DGE_H_

using namespace std;

//Куб
class TCube
{
  private:
    float x,y,z,xm,ym,zm;
    float r,g,b;
  public:
    TCube();
    ~TCube();
    void Position(float X, float Y, float Z);
    void Draw();
    void Turn(float Y);
    void Color(float R,float G,float B);
  
};

#endif