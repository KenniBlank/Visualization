#include "common2.h"

void Update(void) {
    // Bubble Sort with frame control
    static int i = 0;       // Track the outer loop index
    static int j = 0;       // Track the inner loop index
    int changes = 0;

    while (i < halfWindowWidth - 1 && changes < changePerFrame) {
        // Perform the bubble sort swap
        if (j < halfWindowWidth - i - 1) {
            if (lines[j].y < lines[j + 1].y) {
                int temp = lines[j].y;
                lines[j].y = lines[j + 1].y;
                lines[j + 1].y = temp;
                changes++;
            }
            j++; // Move to the next element in the inner loop
        } else {
            // Reset inner loop and advance the outer loop
            j = 0;
            i++;
        }
    }

    // Reset `i` and `j` when sorting is complete
    if (i >= halfWindowWidth - 1) {
        i = 0;
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