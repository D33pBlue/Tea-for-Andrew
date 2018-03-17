#include "Scrittore.h"

TTF_Font* Scrittore::font=0;


Scrittore::Scrittore(int x,int y,int siz):pic(0),pos(x,y),_size(siz){
    if(!font){
        font=TTF_OpenFont("Risorse/font.ttf",siz);
        if(!font)cout<<"Errore caricamento font!"<<endl;
    }
    }

Scrittore::~Scrittore(){
    liberaMemo();
    }

void Scrittore::liberaMemo(){
    if(pic)SDL_DestroyTexture(pic);
    w=0;
    h=0;
    }

void Scrittore::scrivi(string txt,SDL_Renderer*rende){
    liberaMemo();
    SDL_Color colore={0,0,0,255};
    SDL_Surface *stx=TTF_RenderText_Solid(font,txt.c_str(),colore);
    pic=SDL_CreateTextureFromSurface(rende,stx);
    w=stx->w;
    h=stx->h;
    SDL_FreeSurface(stx);
    }

void Scrittore::stampa(SDL_Renderer*rende)const{
    SDL_Rect quadB={pos.getX(),pos.getY(),w,h};
    SDL_RenderCopyEx(rende,pic,0,&quadB,0,0,SDL_FLIP_NONE);
    }
