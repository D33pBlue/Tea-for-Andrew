#include "Isola.h"

#include <iostream>
#include <random>

using namespace std;


int Isola::psi=200;
double Isola::incrpsi=0.0;
int Isola::xvel=-2;

Isola::nodoG::nodoG(int x,int y,int v,int h,SDL_Renderer*rende,nodoG*n):
    g(x,y,v,h,rende),next(n){}

Isola::Isola(int x,int y,int tipo,SDL_Renderer*rende):
    pos(x,y),t(costruisciTerr(tipo,x,y)),_tipo(tipo),geisers(0){
        SDL_Surface*su=0;
        switch(tipo){
        case 1:
            su=IMG_Load("Risorse/t1.png");
            break;
        case 2:
            su=IMG_Load("Risorse/t2.png");
            break;
        case 3:
            su=IMG_Load("Risorse/t3.png");
            break;
        case 4:
            su=IMG_Load("Risorse/t4.png");
            break;
        case 5:
            su=IMG_Load("Risorse/t2.png");
            break;
        }
        SDL_SetColorKey(su,SDL_TRUE,SDL_MapRGB(su->format,0,0,0));
        pic=SDL_CreateTextureFromSurface(rende,su);
        SDL_FreeSurface(su);
        geisers=costruisciGeis(rand()%100,5,rende);
    }

Isola::~Isola(){
    SDL_DestroyTexture(pic);
    liberamemo(geisers);
    }

void Isola::liberamemo(nodoG*n){
    if(n){
        liberamemo(n->next);
        delete n;
    }
    }

Terreno Isola::costruisciTerr(int tipo,int x,int y){
    if(tipo==1)
        return Terreno(x,y-470,x+640,y-470,terra);
    if(tipo==2)
        return Terreno(x,y-165,x+640,y-317,terra);
    if(tipo==3)
        return Terreno(x,y-172,x+640,y-199,terra);
    if(tipo==4)
        return Terreno(x,y-308,x+640,y-316,terra);
    return Terreno(x,y-317,x+640,y-165,terra);
    }


Isola::nodoG* Isola::costruisciGeis(int x,int lim,SDL_Renderer*rende){
    if(lim==0)return new nodoG(pos.getX()+610,t.f(610)+20,-8,400,rende,0);
    int v=-1*(rand()%5)-3,h=40+rand()%300,x2=x+64+rand()%64;
    return new nodoG(pos.getX()+x,t.f(x)+20,v,h,rende,costruisciGeis(x2,lim-1,rende));
    }

void Isola::trasla(int dx,int dy){
    pos.trasla(dx,dy);
    t.trasla(dx,dy);
    nodoG* i=geisers;
    while(i){
        i->g.trasla(dx,dy);
        i=i->next;
    }
    }

void Isola::stampa(SDL_Renderer*rende)const{
    SDL_Rect quadB={pos.getX(),pos.getY()-480,640,480};
    if(_tipo==5)SDL_RenderCopyEx(rende,pic,0,&quadB,0,0,SDL_FLIP_HORIZONTAL);
    else SDL_RenderCopyEx(rende,pic,0,&quadB,0,0,SDL_FLIP_NONE);
    nodoG* i=geisers;
    while(i){
        i->g.stampa(rende);
        i=i->next;
        }
    }

void Isola::evento(Personaggio *p){
    t.evento(p);
    nodoG* i=geisers;
    while(i){
        i->g.evento(p,psi);
        i=i->next;
    }
    if(psi<600)psi++;
    if(psi<=0)trasla(xvel,1);
    else{
        if(pos.getY()>640){
                trasla(xvel,-1);
            }
        else trasla(xvel,0);
        }
    }

void Isola::attivaGeisers(bool stato){
    nodoG* i=geisers;
    while(i){
        i->g.setStato(stato);
        i=i->next;
    }
    }

Punto Isola::getPos()const{
    return pos;
    }

int Isola::getTipo()const{
    return _tipo;
    }

