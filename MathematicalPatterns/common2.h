#include "../common.h"

#define Pie 3.14159265358979323846
#define frameRate (60)
float frame_time = 0, frame_start_time = 0;

bool LocalSetup(void){
    if (frameRate > 0)
        frame_time = 1000 / frameRate;

    // Initialize Everything
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
        fprintf(stderr,"Error: %s",SDL_GetError());
        return false;
    };
    return true;
}

void limitFrames(void){
    // Limiting the frames
    if ((SDL_GetTicks() - frame_start_time) < frame_time)
        SDL_Delay(frame_time - (SDL_GetTicks() - frame_start_time));
    frame_start_time = SDL_GetTicks();
}
