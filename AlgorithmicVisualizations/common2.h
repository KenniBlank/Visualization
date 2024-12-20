#include "../common.h"
#include <time.h>
#define totalPoints (WINDOW_WIDTH)

int changePerFrame = 10;

typedef struct{
    int x, y;
} Lines;
Lines lines[totalPoints];

void localSetup(void){
    srand(69); // Setting sameSeed for all 

    float addFactor = (float) WINDOW_WIDTH / totalPoints;
    if (addFactor < 1)
        addFactor = 1;

    // random Points of spawn for all points
    lines[0].x = 0;
    lines[0].y = rand() % WINDOW_HEIGHT;
    for (int i = 1; i < totalPoints; i++){
        lines[i].x = lines[i - 1].x + addFactor;
        lines[i].y = rand() % WINDOW_HEIGHT;
    }
}

void Render(void){
    SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255); // Black Background
    SDL_RenderClear(Renderer);

    SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255); // White Color Selected
    for (int i = 0; i < totalPoints; i++){
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

void Update(void); // This should be your algorithm

bool isSorted() {
    for (int i = 1; i < totalPoints; i++)
        if (lines[i].y > lines[i - 1].y)
            return false;
    return true;
}

void fileHandling(float totalTime){
    // Writing in the data for future use
    FILE *file = fopen("data.md", "a");
    const char *AlgorithmName = strrchr(SOURCE, '/'); // Find last '/'
    if (AlgorithmName)
        AlgorithmName++; // Move past the '/'
    else
        AlgorithmName = SOURCE; // No '/' found, SOURCE is the filename

     // Create a modifiable copy of AlgorithmName for removing ".c"
    char formattedAlgorithmName[100];
    strncpy(formattedAlgorithmName, AlgorithmName, sizeof(formattedAlgorithmName) - 1);
    formattedAlgorithmName[sizeof(formattedAlgorithmName) - 1] = '\0'; // Ensure null-termination

    // Find and remove the .c extension if it exists
    char *dot = strrchr(formattedAlgorithmName, '.');
    if (dot && strcmp(dot, ".c") == 0) {
        *dot = '\0'; // Terminate the string at the .c extension
    }

    AlgorithmName = formattedAlgorithmName;
    fprintf(file, "%d, %d, %f, %s\n", totalPoints, changePerFrame, totalTime / 1000.0, AlgorithmName);
    fclose(file);
}

int main(void){
    static clock_t startTime = 0, endTime = 0;
    static long double totalTime = 0;
    static bool sorted = false;
    setup();
    localSetup();
    printf("\n\tTotal Values to sort: %d\n", totalPoints);
    while (gameIsRunning){
        ProcessInput();
        sorted = isSorted();
        if (play){
            if (!sorted){
                startTime = clock();
                Update();
                endTime = clock();
                totalTime += (double)(endTime - startTime) / CLOCKS_PER_SEC;
            }
            if (sorted){
                printf("\n\tTo sort %d values, it took %Lf seconds\n", totalPoints, (long double)totalTime / 1000.0);
                play = false;
            }
        }
        Render();
    }
    DestroyWindow();
    fileHandling(totalTime);
}