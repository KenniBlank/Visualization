#include "common2.h"

void Update(void) {
    // Bubble Sort with frame control
    static int i = 0;       // Track the outer loop index
    static int j = 0;       // Track the inner loop index
    int changes = 0;

    while (i < totalPoints - 1 && changes < changePerFrame) {
        if (j < totalPoints - i - 1) {
            if (lines[j].y < lines[j + 1].y) {
                int temp = lines[j].y;
                lines[j].y = lines[j + 1].y;
                lines[j + 1].y = temp;
                changes++;
            }
            j++; // Move to the next element in the inner loop
        } else {
            j = 0;
            i++;
        }
    }

    // Reset `i` and `j` when sorting is complete
    if (i >= totalPoints - 1) {
        i = 0;
        j = 0;
    }
}