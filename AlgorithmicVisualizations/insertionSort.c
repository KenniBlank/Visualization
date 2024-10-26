#include "common2.h"
void Update() {
    // Insertion Sort with frame control
    static int i = 1; // Track position between frames
    static int j = 0; // Inner loop position
    int insertions = 0;

    while (i < halfWindowWidth && insertions < changePerFrame) {
        int key = lines[i].y;

        // If starting a new iteration, set j to i - 1
        if (j == 0)
            j = i - 1;

        while (j >= 0 && lines[j].y < key && insertions < changePerFrame) {
            lines[j + 1].y = lines[j].y;
            j--;
            insertions++;
        }
        
        lines[j + 1].y = key;
        i++;
        j = 0;
    }

    // Reset `i` and `j` when sorting is complete
    if (i >= halfWindowWidth) {
        i = 1;
        j = 0;
    }
}


int main(void){
    setup();
    localSetup();
    while (gameIsRunning){
        ProcessInput();
        if (play){
            Update();
            Render();
        }
    }
    DestroyWindow();
}