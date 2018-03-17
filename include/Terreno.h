#ifndef TERRENO_H
#define TERRENO_H


#include "Personaggio.h"
#include "Punto.h"

enum Fisicita{terra,lava};

class Terreno
{
private:
    Fisicita tipo;
    Punto x1,x2;
    double m;
    bool collide(Personaggio*p)const;
    bool scontro(Personaggio*p)const;
public:
    Terreno(const Punto& x1,const Punto&x2,Fisicita t=terra);
    Terreno(const int&x1=0,const int&y1=0,const int&x2=0,const int&y2=0,const Fisicita& t=terra);
    void evento(Personaggio*p);
    void trasla(const int&dx,const int&dy);
    bool inRange(const int&x)const;
    int f(const int&x)const;
    void stampa(SDL_Renderer*rende)const;
};

#endif // TERRENO_H
