#ifndef LAVA_H
#define LAVA_H

#include <SDL.h>
#include "Punto.h"
#include "Personaggio.h"
#include "Terreno.h"

class Lava
{
private:
    static SDL_Texture*pic;
    Punto pos;
    Lava* next;
    Terreno t;
public:
    Lava(int x,int y,SDL_Renderer*rende,Lava*n=0);
    ~Lava();
    void trasla(int dx,int dy);
    void stampa(SDL_Renderer* rende)const;
    void evento(Personaggio*p);
    Lava* getNext();
};

#endif // LAVA_H
