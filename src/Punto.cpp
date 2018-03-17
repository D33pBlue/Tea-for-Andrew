#include "Punto.h"

Punto::Punto(const int& x,const int&y){
    pos.x=x;
    pos.y=y;
    }

void Punto::trasla(const int& dx,const int& dy){
    pos.x+=dx;
    pos.y+=dy;
}

int Punto::getX()const{
    return pos.x;
}

int Punto::getY()const{
    return pos.y;
}
