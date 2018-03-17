#include "Terreno.h"
#include <climits>
#include <iostream>
using namespace std;

Terreno::Terreno(const Punto& _x1,const Punto& _x2,Fisicita t):
    x1(_x1),x2(_x2),tipo(t){
        if((_x2.getX()-_x1.getX())==0)m=INT_MAX;
        else m=((double)(_x2.getY()-_x1.getY()))/(_x2.getX()-_x1.getX());
    }

Terreno::Terreno(const int&_x1,const int&y1,const int&_x2,const int&y2,const Fisicita& t):
    x1(_x1,y1),x2(_x2,y2),tipo(t){
        if((_x2-_x1)==0)m=INT_MAX;
        else m=((double)(y2-y1))/(_x2-_x1);
    }

bool Terreno::collide(Personaggio*p)const{
    if(!p)return false;
    int xp=p->getPos().getX(),yp=p->getPos().getY();
    if(xp+80 < x1.getX())return false;
    if(xp > x2.getX())return false;
    int fx=x1.getY()+m*(xp-x1.getX());
    if(yp < fx)return false;
    return true;
    }

void Terreno::trasla(const int&dx,const int&dy){
    x1.trasla(dx,dy);
    x2.trasla(dx,dy);
    }

void Terreno::evento(Personaggio*p){
    if(tipo!=lava && scontro(p)){
        p->trasla(x1.getX()-p->getPos().getX()-80,0);
    }
    else if(collide(p)){
        if(tipo==lava){
            p->uccidi();
        }
        else{
            int fx=x1.getY()+m*(p->getPos().getX()-x1.getX());
            if(p->getVel()>20)Mix_PlayChannel(-1,Personaggio::suono,0);
            p->setVel(0,p->getXVel());
            p->trasla(0,fx-p->getPos().getY());
        }
    }
    }

bool Terreno::inRange(const int&x)const{
    if(x<x1.getX())return false;
    if(x>x2.getX())return false;
    return true;
    }

int Terreno::f(const int&x)const{
    return x1.getY()+m*(x);
    }


void Terreno::stampa(SDL_Renderer*rende)const{
    if(tipo==lava)SDL_SetRenderDrawColor(rende,255,0,0,255);
    else SDL_SetRenderDrawColor(rende,0,255,0,255);
    SDL_RenderDrawLine(rende,x1.getX(),x1.getY(),x2.getX(),x2.getY());
    }

bool Terreno::scontro(Personaggio*p)const{
    if(!p)return false;
    int xp=p->getPos().getX()+80,yp=p->getPos().getY()-50;
    if(xp < x1.getX())return false;
    if(xp > x2.getX())return false;
    int fx=x1.getY()+m*(xp-x1.getX());
    if(yp < fx)return false;
    return (yp >= fx);
    }

