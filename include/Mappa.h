#ifndef MAPPA_H
#define MAPPA_H

#include "Isola.h"
#include "Personaggio.h"
#include <SDL.h>
#include <SDL_image.h>


class Mappa{
private:
    class nodoI{
    public:
        Isola*iso;
        nodoI*next;
        nodoI(int x,int y,int tipo,SDL_Renderer*rende,nodoI*n=0);
    };
    nodoI *first,*last;
    static nodoI* costruisci(int x,int tipo,SDL_Renderer*rende);
public:
    static int max_distanza;
    Mappa(SDL_Renderer*rende);
    ~Mappa();
    void add(int x,int y,int tipo,SDL_Renderer*rende);
    void extract();
    void stampa(SDL_Renderer*rende)const;
    void evento(Personaggio*p,SDL_Renderer*rende);
    void attivaGeisers(bool stato);
};


#endif // MAPPA_H
