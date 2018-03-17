#include "Personaggio.h"

#include <iostream>
using namespace std;

int Personaggio::GRAVITA=40;// DEFAULT 40
Mix_Chunk* Personaggio::suono=0;

Personaggio::Personaggio(const int&x,const int&y,SDL_Renderer*rende):
    OggStmp(100),vivo(1),centro(x,y),vel(0),xvel(0){
        SDL_Surface* su=IMG_Load("Risorse/tea.png");
        if(!su)cout<<"ERRORE"<<endl;
        SDL_SetColorKey(su,SDL_TRUE,SDL_MapRGB(su->format,0,0,0));
        pic=SDL_CreateTextureFromSurface(rende,su);
        SDL_FreeSurface(su);
        if(!suono){
            suono=suono=Mix_LoadWAV("Risorse/atterraggio.wav");
        }
    }

Personaggio::~Personaggio(){
    SDL_DestroyTexture(pic);
    }

Punto Personaggio::getPos()const{
    return centro;
    }

int Personaggio::getVel()const{
    return vel;
    }

int Personaggio::getXVel()const{
    return xvel;
    }


bool Personaggio::getVivo()const{
    return vivo;
    }

void Personaggio::increaseVel(const int&v,const int&xv){
    vel+=v;
    xvel+=xv;
    }

void Personaggio::uccidi(){
    vivo=0;
    }

void Personaggio::risorgi(){
    vivo=1;
    }

void Personaggio::stampa(SDL_Renderer*rende)const{
    SDL_Rect quad={centro.getX()-15,centro.getY()-90,100,100};
    SDL_RenderCopyEx(rende,pic,0,&quad,0,0,SDL_FLIP_NONE);
    }

void Personaggio::trasla(const int&dx,const int&dy){
    centro.trasla(dx,dy);
    }

void Personaggio::setVel(const int&v,int xv){
    vel=v;
    xvel=xv;
    }

void Personaggio::eventi(){
    if(xvel!=0 || vel!=0)trasla(xvel,vel/5);
    if(vel<GRAVITA)increaseVel();
    if(centro.getX()<-100 || centro.getY()>800)uccidi();
    }

