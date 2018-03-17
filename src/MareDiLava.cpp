#include "MareDiLava.h"


MareDiLava::MareDiLava(SDL_Renderer*rende):first(costru(rende,3,-20,640)),scostamento(0){}

MareDiLava::~MareDiLava(){
    if(first)delete first;
    }

Lava* MareDiLava::costru(SDL_Renderer *rende,int k,int x,int y){
    if(k<=0)return 0;
    return new Lava(x,y,rende,costru(rende,k-1,x+640,y));
    }

void MareDiLava::stampa(SDL_Renderer*rende)const{
    Lava*l=first;
    while(l){
        l->stampa(rende);
        l=l->getNext();
    }
    }

void MareDiLava::evento(Personaggio*p){
    Lava* l=first;
    while(l){
        l->evento(p);
        if(scostamento<5)l->trasla(1,0);
        else l->trasla(-1,0);
        l=l->getNext();
    }
    scostamento++;
    if(scostamento==10)scostamento=0;
    }
