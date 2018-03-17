#ifndef ISOLA_H
#define ISOLA_H

#include <SDL.h>
#include <SDL_image.h>
#include "Terreno.h"
#include "Geiser.h"
#include "Personaggio.h"
#include "Punto.h"
#include "OggStmp.h"

#include <SDL.h>
#include "Punto.h"
#include "Terreno.h"
#include "Personaggio.h"
#include "Geiser.h"

class Isola{
private:
    Punto pos;
    Terreno t;
    SDL_Texture *pic;
    int _tipo;
    class nodoG{
    public:
        Geiser g;
        nodoG* next;
        nodoG(int x,int y,int v,int h,SDL_Renderer*rende,nodoG*n=0);
    };
    nodoG* geisers;
    static Terreno costruisciTerr(int tipo,int x,int y);
    nodoG* costruisciGeis(int x,int lim,SDL_Renderer*rende);
    static void liberamemo(nodoG*n);
public:
    static int psi;
    static double incrpsi;
    static int xvel;

    Isola(int x,int y,int tipo,SDL_Renderer*rende);
    ~Isola();
    void trasla(int dx,int dy);
    void stampa(SDL_Renderer*rende)const;
    void evento(Personaggio*p);
    void attivaGeisers(bool stato);
    Punto getPos()const;
    int getTipo()const;
};


#endif // ISOLA_H
