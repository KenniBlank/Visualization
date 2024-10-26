#include <SDL2/SDL.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_events.h>
#include <math.h>
#include <stdio.h>
#include <stdbool.h>

#define WINDOW_WIDTH (600)
#define WINDOW_HEIGHT (600)
#define Pie 3.14159265358979323846
#define frameRate (60)

float frame_time = 0, frame_start_time = 0;
bool play = true;
bool gameIsRunning = true;

SDL_Window* Window = NULL;
SDL_Renderer* Renderer = NULL;


int setup(void){
    if (frameRate > 0)
        frame_time = 1000 / frameRate;

    // Initialize Everything
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
        fprintf(stderr,"Error: %s",SDL_GetError());
        return false;
    }

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

void limitFrames(void){
    // Limiting the frames
    if ((SDL_GetTicks() - frame_start_time) < frame_time)
        SDL_Delay(frame_time - (SDL_GetTicks() - frame_start_time));
    frame_start_time = SDL_GetTicks();
}

void DestroyWindow(void){
    SDL_DestroyWindow(Window);
    SDL_DestroyRenderer(Renderer);
}