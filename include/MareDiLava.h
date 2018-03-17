#ifndef MAREDILAVA_H
#define MAREDILAVA_H

#include "Lava.h"
#include <SDL.h>
#include "Personaggio.h"


class MareDiLava
{
private:
    Lava *first;
    int scostamento;
    static Lava* costru(SDL_Renderer*rende,int k,int x,int y);
public:
    MareDiLava(SDL_Renderer *rende);
    ~MareDiLava();
    void stampa(SDL_Renderer *rende)const;
    void evento(Personaggio *p);
};

#endif // MAREDILAVA_H
