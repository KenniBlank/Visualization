#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <termios.h>
#define FPS (180.00)

void Swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

bool bubbleSort(int *array, int sizeOfArray){
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

bool selectionSort(int *array, int sizeOfArray){
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

// bool insertionSort(int* array, int sizeOfArray){
//     static int i = sizeOfArray;
//     for (i; i >= 0; i--){
//         for (int j = 0;)
//     }
// }

bool Sort(int *array, int sizeOfArray){
    bool returnValue;
    returnValue = bubbleSort(array, sizeOfArray);
    // returnValue = selectionSort(array, sizeOfArray);
    // returnValue = insertionSort(array, sizeOfArray);  
    return returnValue;
}

bool UnSort(int *array, int sizeOfArray){
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

bool IsIn(int* array, int arraySize, int value){
    for (int i = 0; i < arraySize; i++)
        if (array[i] == value)
            return true;
        else   
            array[i] = value;
    return false;
}

void timerOfSeconds(int delay_seconds){
    clock_t start_time = clock();
    double elapsed_time;
    int array[delay_seconds];
    while (true) {
        elapsed_time = (clock() - start_time) / (double)CLOCKS_PER_SEC;
        int time = (int)(delay_seconds - elapsed_time);
        if (!IsIn(array, delay_seconds, time))
            printf("%d...\n", time + 1);
        if (elapsed_time >= delay_seconds)
            break;
    }
}

int main() {
    struct termios old_termios, new_termios;
    int c;
    // Save the current terminal settings
    tcgetattr(STDIN_FILENO, &old_termios);

    // Modify the terminal settings to enable non-blocking input
    new_termios = old_termios;
    new_termios.c_lflag &= ~(ICANON | ECHO);
    new_termios.c_cc[VMIN] = 1;
    new_termios.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);

    struct winsize terminalBounds;
    ioctl(STDIN_FILENO, TIOCGWINSZ, &terminalBounds);
    int terminalHeight = terminalBounds.ws_row, terminalWidth = terminalBounds.ws_col;

    // Randomizer
    srand(time(NULL));
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
        if (Sorted){
            Sorted = !UnSort(lines, terminalWidth);
            if (Sorted == false){
                printf("The points are Unsorted\n\tPress Escape and Enter to exit or Any Other Key To Sort the Points");
                c = getchar();
                if (c == 27)
                    break;
                printf("Sorting the Points in...\n");
                timerOfSeconds(3);
            }
        }
        else{
            Sorted = Sort(lines, terminalWidth);
            if (Sorted == true){
                printf("The points are sorted\n\tPress Escape and Enter to exit or Any Other Key To UnSort the Points");
                c = getchar();
                if (c == 27)
                    break;
                printf("UnSorting the Points In ...\n");
                timerOfSeconds(3);
            }
        }

        // Delay For Visualization
        clock_t start_time = clock(), endTime = 0;
        while(true){
            endTime = clock();
            if ((endTime - start_time) / (double) CLOCKS_PER_SEC > (1.00/FPS))
                break;
        }
        system("clear");
    }
     // Restore Previous Terminal Configurations
    printf("\033[?25h");
    tcsetattr(STDIN_FILENO, TCSANOW, &old_termios);
    return 0;
}