#ifndef OGGSTMP_H
#define OGGSTMP_H

#include <SDL.h>

class OggStmp
{
    private:
        int l;
    public:
        OggStmp(const int&);
        int getLiv()const;
        virtual void stampa(SDL_Renderer*rende)const=0;
};

#endif // OGGSTMP_H
