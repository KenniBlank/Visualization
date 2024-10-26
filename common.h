#include <SDL2/SDL.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_events.h>
#include <math.h>
#include <stdio.h>
#include <stdbool.h>

#define WINDOW_WIDTH (600)
#define WINDOW_HEIGHT (600)

bool play = true;
bool gameIsRunning = true;

SDL_Window* Window = NULL;
SDL_Renderer* Renderer = NULL;

int setup(void){
    SDL_Window* Window = SDL_CreateWindow("Dimensions",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        0);

    if (!Window){
        fprintf(stderr,"Error: %s",SDL_GetError());
        return false;
    }

    Renderer = SDL_CreateRenderer(Window, -1, 0);
    if (!Renderer){
        fprintf(stderr,"Error: %s",SDL_GetError());
        return false;
    }
    return 1;
}

void DestroyWindow(void){
    SDL_DestroyWindow(Window);
    SDL_DestroyRenderer(Renderer);
}