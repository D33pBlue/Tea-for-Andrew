#include "Geiser.h"
#include <iostream>
using namespace std;

Mix_Chunk* Geiser::suono=0;
int Geiser::ngeis=0;
int Geiser::totgeis=0;
Uint32 Geiser::suonoON=0;

Geiser::Geiser():OggStmp(0),pos(0,0),vel(0),h(0),attivo(0){}


Geiser::Geiser(const int&x,const int&y,const int&_vel,const int&_h,SDL_Renderer*rende):
    OggStmp(200),pos(x,y),vel(_vel),h(_h),attivo(0){
        SDL_Surface* su=IMG_Load("Risorse/geiserBase.png");
        SDL_SetColorKey(su,SDL_TRUE,SDL_MapRGB(su->format,0,0,0));
        picBase=SDL_CreateTextureFromSurface(rende,su);
        SDL_FreeSurface(su);
        su=IMG_Load("Risorse/geiserGas.png");
        SDL_SetColorKey(su,SDL_TRUE,SDL_MapRGB(su->format,0,0,0));
        picGas=SDL_CreateTextureFromSurface(rende,su);
        SDL_FreeSurface(su);
        ngeis++;
        totgeis++;
        //cout<<"geiser #"<<ngeis<<": "<<pos.getX()<<" , "<<pos.getY()<<" ci sono "<<totgeis<<" geis"<<endl;
        if(!suono){
            suono=Mix_LoadWAV("Risorse/geiser.wav");
        }
        }


Geiser::~Geiser(){
    SDL_DestroyTexture(picBase);
    SDL_DestroyTexture(picGas);
    totgeis--;
    }

Punto Geiser::getPos()const{
    return pos;
    }

bool Geiser::getAttivo()const{
    return attivo;
    }

void Geiser::setStato(bool s){
    attivo=s;
    }

void Geiser::stampa(SDL_Renderer*rende)const{
    SDL_Rect quadB={pos.getX()-20,pos.getY()-10,40,15};
    //SDL_Point c={pos.getX(),pos.getY()};
    SDL_RenderCopyEx(rende,picBase,0,&quadB,0,0,SDL_FLIP_NONE);
    if(attivo){
        SDL_Rect quad={pos.getX()-30,pos.getY()-h,60,h};
        //SDL_Point c={pos.getX(),pos.getY()};
        SDL_RenderCopyEx(rende,picGas,0,&quad,0,0,SDL_FLIP_NONE);
        }
    }

void Geiser::trasla(const int&dx,const int &dy){
    pos.trasla(dx,dy);
    }

bool Geiser::collide(Personaggio*p)const{
    if(!p)return false;
    int xp=p->getPos().getX(),yp=p->getPos().getY();//raggio sx=15 raggio dx=85;
    if(xp+85 < pos.getX()-20)return false;
    if(xp-15 > pos.getX()+20)return false;
    if(yp < pos.getY()-h)return false;
    if(yp-100 > pos.getY())return false;
    return true;
    }

void Geiser::evento(Personaggio*p,int& psi){
    if(attivo){//default vel -20
            if(collide(p) && p->getVel()>-30){
                p->increaseVel(vel,0);
            }
            psi-=1;
    if(SDL_GetTicks()-suonoON>90){
            Mix_PlayChannel(-1,suono,0);
            suonoON=SDL_GetTicks();
        }
    }
    }
