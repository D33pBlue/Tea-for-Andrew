#ifndef SCRITTORE_H
#define SCRITTORE_H

#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include "Punto.h"
#include <iostream>

using namespace std;

class Scrittore
{
private:
    SDL_Texture *pic;
    Punto pos;
    int _size,w,h;
    void liberaMemo();
public:
    static TTF_Font *font;
    Scrittore(int x,int y,int siz);
    ~Scrittore();
    void scrivi(string txt,SDL_Renderer*rende);
    void stampa(SDL_Renderer*rende)const;
};

#endif // SCRITTORE_H
