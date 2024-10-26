#include "common.h"

long double x[] = {WINDOW_WIDTH / 2, WINDOW_WIDTH/2 + 100, WINDOW_WIDTH / 2, WINDOW_WIDTH/ 2 - 100};
long double y[] = {WINDOW_HEIGHT / 2 - 100, WINDOW_HEIGHT / 2, WINDOW_HEIGHT / 2 + 100, WINDOW_HEIGHT /2};


// Function Definition
void ProcessInput(void);
void Update(void);
void Render(void);

int totalPointOfX_Y;
int angleIncrement = 10;

int main(){
    totalPointOfX_Y = sizeof(x) / sizeof(x[0]);
    setup();
    while (gameIsRunning){
        // Limit the frames of the game to the frame cap
        limitFrames();
        ProcessInput();
        if (play){
            Update();
            Render();
        }
    }
    DestroyWindow();
    return 0; // 0 Signifizes success
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
                        angleIncrement ++;
                        break;
                    case SDLK_DOWN:
                        angleIncrement --;
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


void Update(void){
    int centerX = WINDOW_WIDTH / 2;
    int centerY = WINDOW_HEIGHT / 2;

    double angle = angleIncrement * Pie / 180; // Convert angle to radians

    for(int i = 0; i < totalPointOfX_Y; i++){
        double originalX = x[i] - centerX;
        double originalY = y[i] - centerY;
        x[i] = centerX + originalX * cos(angle) - originalY * sin(angle);
        y[i] = centerY + originalX * sin(angle) + originalY * cos(angle);
    }
}

void Render(void){
    SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255); // Set background color to black
    SDL_RenderClear(Renderer);

    SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255); // Set draw color to red

    // Axis
    SDL_RenderDrawLine(Renderer, WINDOW_WIDTH / 2, 0, WINDOW_WIDTH / 2, WINDOW_HEIGHT);
    SDL_RenderDrawLine(Renderer, 0, WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT / 2);

    // draw Box:
    for (int i = 0; i < totalPointOfX_Y; i ++){
        SDL_RenderDrawLine(Renderer, x[i], y[i], x[i+1 < totalPointOfX_Y? i + 1: 0], y[i+1 < totalPointOfX_Y? i + 1: 0]);
        SDL_RenderDrawLine(Renderer, x[i], y[i], WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    }
    SDL_RenderPresent(Renderer);
}