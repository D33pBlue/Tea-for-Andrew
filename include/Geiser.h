#ifndef GEISER_H
#define GEISER_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "Punto.h"
#include "OggStmp.h"
#include "Personaggio.h"

class Geiser:public OggStmp
{
private:
    Punto pos;//centro basso +20px x lato
    int vel,h;
    SDL_Texture *picBase,*picGas;
    bool attivo;
    bool collide(Personaggio*p)const;
public:
    static int ngeis,totgeis;
    static Mix_Chunk*suono;
    static Uint32 suonoON;
    Geiser(const int&x,const int&y,const int&_vel,const int&_h,SDL_Renderer*rende);
    Geiser();
    ~Geiser();
    Punto getPos()const;
    bool getAttivo()const;
    void setStato(bool s);
    void stampa(SDL_Renderer*rende)const;
    void trasla(const int&dx,const int&dy);
    void evento(Personaggio*p,int& psi);
};

#endif // GEISER_H
