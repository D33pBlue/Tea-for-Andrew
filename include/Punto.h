#ifndef PUNTO_H
#define PUNTO_H

#include<SDL.h>

class Punto
{
private:
    SDL_Point pos;
public:
    Punto(const int&x,const int&y);
    void trasla(const int& dx,const int&dy);
    int getX()const;
    int getY()const;
};

#endif // PUNTO_H
