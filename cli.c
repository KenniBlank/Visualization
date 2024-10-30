#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <sys/ioctl.h>
#include <unistd.h>
#define FPS (90.00)

void Swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

bubbleSort(int *array, int sizeOfArray){
    static int i = 0;
    for (i; i < sizeOfArray; i++){
        for (int j = i + 1; j < sizeOfArray; j++){
            if (array[i] < array[j]){
                Swap(&array[i], &array[j]);
                return false;
            }
        }
    }
    i = 0;
    return true;
}

selectionSort(int *array, int sizeOfArray){
    static int i = 0;
    for (i; i < sizeOfArray; i++){
        int minIndex = i;
        for (int j = i + 1; j < sizeOfArray; j++)
            if (array[j] > array[minIndex])
                minIndex = j;
        if (minIndex != i){
            Swap(&array[i], &array[minIndex]);
            return false;
        }
    }
    i = 0;
    return true;
}

// insertionSort(int* array, int sizeOfArray){
//     static int i = sizeOfArray;
//     for (i; i >= 0; i--){
//         for (int j = 0;)
//     }
// }

Sort(int *array, int sizeOfArray){
    // return bubbleSort(array, sizeOfArray);
    bool returnValue = selectionSort(array, sizeOfArray);
    // return insertionSort(array, sizeOfArray);
    if (returnValue){
        system("clear");
        // Delay For Visualization
        clock_t start_time = clock(), endTime = 0;
        while(true){
            endTime = clock();
            if ((endTime - start_time) / (double) CLOCKS_PER_SEC > (1.00/FPS))
                break;
        }
    }

    return returnValue;
}

UnSort(int *array, int sizeOfArray){
    static int i = 0;
    static int unSortCount = 0;
    for (; i < sizeOfArray; i++){
        Swap(&array[i], &array[rand() % sizeOfArray]);
        unSortCount++;
        if (unSortCount > sizeOfArray)
            break;
        return false;
    }
    i = 0;
    unSortCount = 0;
    
    return true;
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
        lines[i] = rand() % terminalHeight;
    
    // Write C code here
    int greatest = 0;
    for (int i = 0; i < terminalWidth; i++)
        if (greatest < lines[i])
            greatest = lines[i];
    printf("\033[?25l");
    bool Sorted = false;
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
        if (Sorted)
            Sorted = !UnSort(lines, terminalWidth);
        else
            Sorted = Sort(lines, terminalWidth);

        // Delay For Visualization
        clock_t start_time = clock(), endTime = 0;
        while(true){
            endTime = clock();
            if ((endTime - start_time) / (double) CLOCKS_PER_SEC > (1.00/FPS))
                break;
        }
        system("clear");
    }
    printf("\033[?25h");
    return 0;
}