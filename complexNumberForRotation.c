#include "common.h"

// Functions:
void ProcessInput(void);
void Update(void);
void Render(void);

int main(){
    setup();

    // Main Game Loop
    while (gameIsRunning){
        limitFrames();
        ProcessInput();
        if (play){
            Update();
            Render();
        }
    }

    DestroyWindow();
    return 0; // 0 means success
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
                }
        }
    }
}

void Update(void){

}

void Render(void){

}