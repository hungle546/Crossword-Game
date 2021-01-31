#ifndef game_h
#define game_h
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <stdbool.h>

typedef struct clues
{
    char solution[500], clue[256];
    char Orientation[50];
    int r,c;
    int i;
    bool isFound;
}clues;


char** createArray(int row, int col) {
    char **myArray;
    myArray = calloc(row, sizeof(char *));
    if (myArray == NULL) {
        printf("Error %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < row; i++) {
        myArray[i] = calloc(col, sizeof(char));
        if (myArray[i] == NULL) {
            printf("Error %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
    }

    return myArray;
}


void blankSpace(struct clues *puzzles, char** myArray, int words)
{
    for (int i =0; i<words;i++) {
        if (strcmp("Horizontal",puzzles[i].Orientation)==0) {
            for (unsigned int j = 0; j < strlen(puzzles[i].solution); j++){
                myArray[puzzles[i].r-1][puzzles[i].c-1+j] = '_';
            }
        }
        else {
            for (unsigned int j = 0; j < strlen(puzzles[i].solution); j++){
                myArray[puzzles[i].r-1+j][puzzles[i].c-1] = '_';
            }
        }

    }


}

void printArray(char** myArray, int rows, int cols) {
    printf("    1 2 3 4 5 6 7 8 9 10 11 12 13 14 15\n");
    printf("   ------------------------------------\n");

    for (int i = 0; i < rows; i++) {
        printf("%d | ", i+1);
        for (int j = 0; j < cols; j++) {
            printf("%c ", myArray[i][j]);
        }
        printf("\n");
    }

}
void fillArray(char** myArray, int rows, int cols) {

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            myArray[i][j] = '#';

        }
    }
    return;
}

#endif

