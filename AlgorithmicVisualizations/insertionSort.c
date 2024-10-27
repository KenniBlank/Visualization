#include "common2.h"

void Update() {
    int insertions = 0;
    static int i = 1; // Track position between frames
    static int j = 0; // Inner loop position

    while (i < totalPoints && insertions < changePerFrame) {
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
    if (i >= totalPoints) {
        i = 1;
        j = 0;
    }
}