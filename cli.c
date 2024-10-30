#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <sys/ioctl.h>
#include <unistd.h>

void Swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void Sort(int *array, int sizeOfArray){
    static int i = 0;
    for (i; i < sizeOfArray; i++){
        for (int j = i + 1; j < sizeOfArray; j++){
            if (array[i] < array[j]){
                Swap(&array[i], &array[j]);
                return;
            }
        }
    }
}

int main() {
    struct winsize terminalBounds;

    ioctl(STDIN_FILENO, TIOCGWINSZ, &terminalBounds);
    int terminalHeight = terminalBounds.ws_row, terminalWidth = terminalBounds.ws_col;

    // Randomizer
    srand(69);
    int lines[terminalWidth];
    lines[0] = rand() % terminalHeight;
    for (int i = 1; i < terminalWidth; i++)
        lines[i] = rand() % terminalHeight - 1;
    
    // Write C code here
    int greatest = 0;
    for (int i = 0; i < terminalWidth; i++)
        if (greatest < lines[i])
            greatest = lines[i];
    printf("\033[?25l");
    while(true){
        // Checking for terminal Size change
        ioctl(STDIN_FILENO, TIOCGWINSZ, &terminalBounds);
        if (terminalBounds.ws_col != terminalWidth || terminalBounds.ws_row != terminalHeight){
            printf("Terminal Was Resized.\nExiting Program...\n");
            break;
        }
        
        // Render Logic
        for (int i = 0; i <= greatest; i++){
            for (int j = 0; j < terminalWidth; j++)
                if (i >= lines[j])
                    printf(".");
                else
                    printf(" ");
            printf("\n");
        }

        // Sorting Logic
        Sort(lines, terminalWidth);

        // Delay For Visualization
        clock_t start_time = clock(), endTime = 0;
        while(true){
            if ((endTime - start_time) / (double) CLOCKS_PER_SEC > 0.01)
                break;
            endTime = clock();
        }
        system("clear");
    }
    printf("\033[?25h");
    return 0;
}