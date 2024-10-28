#include "common2.h"

void Update(void) {
    int changes = 0;
    static int i = 0;
    for (; i < totalPoints; i++) {
        int maximum = i;
        for (int j = i; j < totalPoints; j++) {
            if (lines[j].y >= lines[maximum].y) {
                maximum = j;
            }
        }
        if (maximum != i) {
            if (i != totalPoints - 1) {
                continue;
            } else {
                return;
            }
        } else {
            changes++;
            if (changes <= changePerFrame) {
                int temp = lines[i].y;
                lines[i].y = lines[maximum].y;
                lines[maximum].y = temp;
            }
        }
    }
}
