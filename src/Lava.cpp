#include "Lava.h"

#include <iostream>
using namespace std;

SDL_Texture* Lava::pic=0;

Lava::Lava(int x,int y,SDL_Renderer*rende,Lava*n):
    pos(x,y),next(n),t(x,y-128,x+640,y-143,lava){
        if(!pic){
            SDL_Surface* su;
            su=IMG_Load("Risorse/lava.png");
            SDL_SetColorKey(su,SDL_TRUE,SDL_MapRGB(su->format,0,0,0));
            pic=SDL_CreateTextureFromSurface(rende,su);
            SDL_FreeSurface(su);
        }
    }

Lava::~Lava(){
    if(next)delete next;
    }

void Lava::stampa(SDL_Renderer*rende)const{
    SDL_Rect quadB={pos.getX(),pos.getY()-480,640,480};
    SDL_RenderCopyEx(rende,pic,0,&quadB,0,0,SDL_FLIP_NONE);
    }

void Lava::evento(Personaggio*p){
    t.evento(p);
    }

void Lava::trasla(int dx,int dy){
    pos.trasla(dx,dy);
    t.trasla(dx,dy);
    }

Lava* Lava::getNext(){
    return next;
    }
