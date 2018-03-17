#ifndef PERSONAGGIO_H
#define PERSONAGGIO_H

#include "Punto.h"
#include "OggStmp.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

class Personaggio: public OggStmp
{
private:
    bool vivo;
    Punto centro;
    int vel,xvel;
    SDL_Texture *pic;
    static int GRAVITA;

public:
    static Mix_Chunk* suono;
    Personaggio(const int&x,const int&y,SDL_Renderer*rende);
    ~Personaggio();
    Punto getPos()const;
    int getVel()const;
    int getXVel()const;
    bool getVivo()const;
    void increaseVel(const int&v=1,const int&xv=0);
    void uccidi();
    void setVel(const int&v,int xv=0);
    void stampa(SDL_Renderer*rende)const;
    void trasla(const int&dx,const int&dy);
    void eventi();
    void risorgi();
};



#endif // PERSONAGGIO_H
