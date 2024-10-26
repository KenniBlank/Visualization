#include "../common.h"
#define halfWindowWidth (WINDOW_WIDTH / 2)

int changePerFrame = 1;
typedef struct{
    int x, y;
} Lines;

Lines lines[halfWindowWidth];

void localSetup(void){
    srand(69); // Setting sameSeed for all 

    // random Points of spawn for all points
    lines[0].x = 0;
    int addFactor = WINDOW_WIDTH/halfWindowWidth;
    for (int i = 1; i < halfWindowWidth; i++){
        lines[i].x = lines[i - 1].x + addFactor;
        lines[i].y = rand() % WINDOW_HEIGHT;
    }
}

void Render(void){
    SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255); // Black Background
    SDL_RenderClear(Renderer);

    SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255); // White Color Selected
    for (int i = 0; i < halfWindowWidth; i++){
        SDL_RenderDrawLine(Renderer, lines[i].x, lines[i].y, lines[i].x, WINDOW_HEIGHT); // From said Point to end
    }
    SDL_RenderPresent(Renderer);
}

void ProcessInput(void){
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        switch (event.type) {
            case SDL_QUIT:
                gameIsRunning = false;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        gameIsRunning = false;
                        break;
                    case SDLK_p:
                        play = play == true? false: true;
                        break;
                    case SDLK_UP:
                        changePerFrame++;
                        break;
                    case SDLK_DOWN:
                        changePerFrame--;
                        break;
                    default:
                        break;
                }
                break;
            case SDL_KEYUP:
                break;
            default:
                break;
        }
    }
}


