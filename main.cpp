#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <ctime>
#include <random>
#include <sstream>
#include <string>
#include <cstdlib>

#include "OggStmp.h"
#include "Personaggio.h"
#include "Mappa.h"
#include "MareDiLava.h"
#include "Scrittore.h"

using namespace std;

//funzioni
void game(SDL_Renderer*rende,bool&chiudi);
void vittoria(SDL_Renderer*rende,bool& c);
void gameover(SDL_Renderer*rende);
void intro(SDL_Renderer*rende);
void entra(SDL_Renderer*rende);

int main(int argc,char**args){
/// Inizializzazioni..
SDL_Init(SDL_INIT_VIDEO| SDL_INIT_AUDIO);
TTF_Init();
IMG_Init(IMG_INIT_PNG);
Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048);
Mix_VolumeMusic(50);

//creazione finestra e renderer
SDL_Window *w=SDL_CreateWindow("Tea-for-Andrew-lava-Game",10,50,1024,640,SDL_WINDOW_INPUT_FOCUS);
SDL_Renderer *rende=SDL_CreateRenderer(w,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);


//flag per terminare la sessione di gioco
bool chiudi=false;

//inizializzazione seme per funzione rand()
srand(time(0));

//viene mostrata l'introduzione
intro(rende);

//ciclo esterno del programma
//riapre il gioco fino a che non viene chiusa la finestra
while(!chiudi){
game(rende,chiudi);//avvia la sessione di gioco
SDL_Delay(1000);
}

//pulizia della memoria
SDL_DestroyRenderer(rende);
SDL_DestroyWindow(w);

//saluti finali
for(int i=0;i<100;i++)cout<<endl;
    cout<<"\t\tTEA FOR ANDREW "<<endl;
    cout<<"\t\t               LAVA GAME"<<endl<<
    "\t\t---------------------------------------------------"<<endl<<endl;
    cout<<"\t\t"<<endl<<endl;
    cout<<"\t\tTHANKS for playing"<<endl<<endl<<endl;
    cout<<"\t\t"<<endl;
    cout<<"\t\t"<<endl<<endl<<endl<<endl<<endl;
    cout<<endl<<endl;
    system("pause");

return 0;
}



// funzione GAME che gestisce il gioco
void game(SDL_Renderer*rende,bool &chiudi){
//inizializzazione variabili ambiente
Isola::xvel=-2;
Mappa::max_distanza=200;
Uint32 startTime=SDL_GetTicks(),actTime=0;
Scrittore *scriv=new Scrittore(50,600,25);
//creazione del personaggio e dell'ambiente
Personaggio* persona=new Personaggio(200,70,rende);
Mappa *mappa=new Mappa(rende);
MareDiLava *lava=new MareDiLava(rende);

//Wallpaper
SDL_Texture* wallpaper=0;
SDL_Surface* suw=IMG_Load("Risorse/wallp.jpg");
SDL_SetColorKey(suw,SDL_TRUE,SDL_MapRGB(suw->format,0,0,0));
wallpaper=SDL_CreateTextureFromSurface(rende,suw);
SDL_FreeSurface(suw);
SDL_Rect quadWallp={0,0,1200,640};

//musica
Mix_Music* ost=Mix_LoadMUS("Risorse/ost.ogg");
Mix_PlayMusic(ost,-1);

int lastvchange=0;
SDL_Event ev;
bool stop=0;
// Ciclo di gioco
while(!stop && persona->getVivo() && actTime<300){
    while(SDL_PollEvent(&ev)){//gestione interazione
        if(ev.type==SDL_QUIT){stop=1;chiudi=1;}
        if(ev.type==SDL_KEYDOWN && ev.key.keysym.sym==SDLK_ESCAPE && ev.key.repeat==0){stop=1;chiudi=1;}
        if(ev.type==SDL_KEYDOWN && ev.key.keysym.sym==SDLK_SPACE && ev.key.repeat==0){
           mappa->attivaGeisers(1);
        }
        if(ev.type==SDL_KEYUP && ev.key.keysym.sym==SDLK_SPACE && ev.key.repeat==0){
            mappa->attivaGeisers(0);
        }
    }

// Gestione eventi
    actTime=(SDL_GetTicks()-startTime)/1000;
    if(actTime!=lastvchange && actTime%20==0){
            Isola::xvel=-1*(rand()%6)-2;
            lastvchange=actTime;
            if(actTime%60==0)Mappa::max_distanza+=10;
        }

    persona->eventi();
    mappa->evento(persona,rende);
    lava->evento(persona);

    stringstream ss;
    ss<<"Remaining time: "<<300-actTime<<"\t\tPSI= "<<Isola::psi<<" bar";
    scriv->scrivi(ss.str(),rende);

// Rendering
    SDL_SetRenderDrawColor(rende,0,0,0,0);
        SDL_RenderClear(rende);
        SDL_RenderCopyEx(rende,wallpaper,0,&quadWallp,0,0,SDL_FLIP_NONE);

        mappa->stampa(rende);
        persona->stampa(rende);
        lava->stampa(rende);
        scriv->stampa(rende);

        SDL_RenderPresent(rende);
    }

// Pulizia della memoria
    Mix_PauseMusic();
    delete ost;
    delete persona;
    delete scriv;
    delete lava;
    delete mappa;
    delete Scrittore::font;
    Scrittore::font=0;
    SDL_DestroyTexture(wallpaper);
    if(actTime<300)gameover(rende);//300
    else vittoria(rende,chiudi);
}


//funzione VITTORIA per visualizzare il messaggio di vittoria
void vittoria(SDL_Renderer*rende,bool&c){
    c=1;
    Mix_Chunk *so=Mix_LoadWAV("Risorse/win.wav");
    Mix_PlayChannel(-1,so,0);
    SDL_Texture *pic;
    SDL_Surface* suw=IMG_Load("Risorse/andrew.png");
SDL_SetColorKey(suw,SDL_TRUE,SDL_MapRGB(suw->format,0,0,0));
pic=SDL_CreateTextureFromSurface(rende,suw);
SDL_FreeSurface(suw);
SDL_Rect quadWallp={50,200,300,420};

    SDL_SetRenderDrawColor(rende,0,150,40,0);
    SDL_RenderClear(rende);
    SDL_RenderCopyEx(rende,pic,0,&quadWallp,0,0,SDL_FLIP_NONE);
    Scrittore scriv(600,300,40);
    scriv.scrivi("So I got my tea!",rende);
    scriv.stampa(rende);
    SDL_RenderPresent(rende);
    SDL_Delay(5000);
    delete Scrittore::font;
    Scrittore::font=0;
    delete so;
    delete pic;
    }


//funzione GAMEOVER per segnalare la sconfitta
void gameover(SDL_Renderer*rende){
    Mix_Chunk *so=Mix_LoadWAV("Risorse/fuoco.wav");
    Mix_PlayChannel(-1,so,0);
    SDL_SetRenderDrawColor(rende,200,0,0,0);
    SDL_RenderClear(rende);
    Scrittore scriv(200,300,100);
    scriv.scrivi("Game over",rende);
    scriv.stampa(rende);
    SDL_RenderPresent(rende);
    SDL_Delay(1500);
    delete Scrittore::font;
    Scrittore::font=0;
    Mix_PausedMusic();
    delete so;
    }

//funzione INTRO per stampare a video l'introduzione
void intro(SDL_Renderer*rende){
    entra(rende);
    Mix_Music* ost=Mix_LoadMUS("Risorse/intro.ogg");
    Mix_PlayMusic(ost,-1);
    SDL_Texture *pic;
    SDL_Surface* suw=IMG_Load("Risorse/andrew.png");
SDL_SetColorKey(suw,SDL_TRUE,SDL_MapRGB(suw->format,0,0,0));
pic=SDL_CreateTextureFromSurface(rende,suw);
SDL_FreeSurface(suw);
SDL_Rect quadWallp={50,200,300,420};
    Scrittore scriv(350,300,40);
    int k=0;
    SDL_Event ev;
    bool chiudi=0;
    while(!chiudi && k<2000){
             while(SDL_PollEvent(&ev)){
        if(ev.type==SDL_QUIT)chiudi=1;
        if(ev.type==SDL_KEYDOWN && ev.key.keysym.sym==SDLK_ESCAPE && ev.key.repeat==0){chiudi=1;}
            }
    SDL_SetRenderDrawColor(rende,0,150,40,0);
    SDL_RenderClear(rende);
    SDL_RenderCopyEx(rende,pic,0,&quadWallp,0,0,SDL_FLIP_NONE);
    switch(k/250){
        case 0: scriv.scrivi("Andew hates people..",rende);
            break;
        case 1: scriv.scrivi("so he lives in a caste.",rende);
            break;
        case 3: scriv.scrivi("He would do anything for tea, but..",rende);
            break;
        case 4: scriv.scrivi("he has a bad problem:",rende);
            break;
        case 5: scriv.scrivi("the castle is surrounded..",rende);
            break;
        case 6: scriv.scrivi("surrounded by an ocean of lava!",rende);
            break;
        case 7: scriv.scrivi("enjoy the game",rende);
            break;
    }
    scriv.stampa(rende);
    SDL_RenderPresent(rende);
    k++;
    }
    delete Scrittore::font;
    Scrittore::font=0;
    delete pic;
    Mix_PauseMusic();
    delete ost;
    }


//funzione ENTRA per accertarsi di avere la finestra attiva
void entra(SDL_Renderer*rende){
    SDL_Event ev;
    bool chiudi=0;
    Scrittore scriv(20,300,40);
    while(!chiudi){
             while(SDL_PollEvent(&ev)){
        if(ev.type==SDL_KEYDOWN && ev.key.keysym.sym==SDLK_SPACE && ev.key.repeat==0){chiudi=1;}
            }

    SDL_SetRenderDrawColor(rende,0,10,90,0);
    SDL_RenderClear(rende);
    scriv.scrivi("Select the window and press space to start",rende);
    scriv.stampa(rende);
    SDL_RenderPresent(rende);
    }
    delete Scrittore::font;
    Scrittore::font=0;
    }
