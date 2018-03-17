#include "Mappa.h"

#include <random>
#include <iostream>
using namespace std;

int Mappa::max_distanza=180;

Mappa::nodoI::nodoI(int x,int y,int tipo,SDL_Renderer*rende,nodoI*n):
    iso(new Isola(x,y,tipo,rende)),next(n) {}

Mappa::Mappa(SDL_Renderer*rende):first(costruisci(0,1,rende)),last(0){
    nodoI*p=first;
    while(p->next){p=p->next;}
    last=p;
    }

Mappa::~Mappa(){
    while(first){
        extract();
    }
    }

Mappa::nodoI* Mappa::costruisci(int x,int tipo,SDL_Renderer*rende){
    if(x>1024)return 0;
    int x2=x+640+rand()%max_distanza,tipo2;
    if(tipo==1 || tipo==2 || tipo==4)tipo2=1+rand()%5;
    else if(tipo==3){
        int j=rand()%3;
        if(j==0)tipo2=2;
        else if(j==1)tipo2=3;
        else tipo2=4;
    }
    else{
        int j=rand()%2;
        if(j)tipo2=3;
        else tipo2=4;
    }
    return new nodoI(x,700,tipo,rende,costruisci(x2,tipo2,rende));
    }

void Mappa::add(int x,int y,int tipo,SDL_Renderer*rende){
        //first e' sempre definito qui
        last->next=new nodoI(x,y,tipo,rende,0);
        last=last->next;
    }

void Mappa::extract(){
    if(!first)return;
    nodoI*k=first;
    first=first->next;
    delete k->iso;
    k->next=0;
    delete k;
    }


void Mappa::stampa(SDL_Renderer*rende)const{
    nodoI *i=first;
    while(i){
        i->iso->stampa(rende);
        i=i->next;
    }
    }

void Mappa::attivaGeisers(bool stato){
    nodoI *i=first;
    while(i){
        i->iso->attivaGeisers(stato);
        i=i->next;
    }
    }


void Mappa::evento(Personaggio*p,SDL_Renderer*rende){
    nodoI *i=first;
    while(i){
        i->iso->evento(p);
        i=i->next;
    }
    if(last->iso->getPos().getX()<1024){
        int x=last->iso->getPos().getX(),y=last->iso->getPos().getY();
        int x2=x+640+rand()%max_distanza,tipo2;
        int tipo=last->iso->getTipo();
        if(tipo==1 || tipo==2 || tipo==4)tipo2=1+rand()%5;
        else if(tipo==3){
            int j=rand()%3;
            if(j==0)tipo2=2;
            else if(j==1)tipo2=3;
            else tipo2=4;
        }
        else{
            int j=rand()%2;
            if(j)tipo2=3;
            else tipo2=4;
        }
        add(x2,y,tipo2,rende);
    }
    if(first->iso->getPos().getX()<-700){
        extract();
    }
    }

