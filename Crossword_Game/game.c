#include <stdio.h>
#include "game.h"
#include <string.h>

bool endGame(struct clues *crosswordArr, int num) {

    for (int i = 0; i < num; i++){
        if (crosswordArr[i].isFound == false){

            return false;
        }
    }
    return true;
}


int main()
{
    FILE *file;
    struct clues *crosswordArr;
    char **board;
    char userAnswer[100];
    int rows, cols, wordNum;
    int userInput = 0;


    printf("Welcome \n \n");
    char filename[100];
    printf("Enter game filename : ");
    scanf("%s", filename);

    file = fopen(filename,"r");
    if (!file)
    {
        printf("Could not open file %s",filename);
        exit(0);
    }

    printf("Loading game file %s\n", filename);



    fscanf(file,"%d %d %d",&rows,&cols,&wordNum);
    printf("Game is %d rows x %d cols with %d words",rows,cols,wordNum);

    crosswordArr = calloc(wordNum, sizeof(clues *));
    board = createArray(rows,cols);
    int i=0;
    do
    {
        fscanf(file,"%d %s %d %d %s %[^\n]",&crosswordArr[i].i, crosswordArr[i].Orientation, &crosswordArr[i].r, &crosswordArr[i].c, crosswordArr[i].solution, crosswordArr[i].clue);
        crosswordArr[i].isFound = false;
        if(strcmp("H",crosswordArr[i].Orientation) == 0){
            strcpy(crosswordArr[i].Orientation,"Horizontal");
        }
        else{
            strcpy(crosswordArr[i].Orientation,"Vertical");
        }
        i++;
    }
    while(i<wordNum);
          fclose(file);
    fillArray(board,rows,cols);
    blankSpace(crosswordArr, board, wordNum);

    do {
    printf("Current Puzzle: \n");
    printArray(board,rows,cols);
    if (endGame(crosswordArr, wordNum)) {
        printf("\n Win \n");
        break;
    }
    printf("\n");
    printf("All Clues: ");
    printf("\n--------------------- \n ");
    printf("#    Direction    Row/Col      Clue \n ");
    for(int i = 0; i<wordNum;i++){
        
        printf(" %d:     %s         %d/%d       %s \n" ,crosswordArr[i].i, crosswordArr[i].Orientation, crosswordArr[i].r, crosswordArr[i].c, crosswordArr[i].clue);

    }
    do
    {
        printf("Enter clue to solve or -1 to exit: ");
        scanf("%d", &userInput);
        if(userInput == -1){
            exit(0);
        }
        if(userInput < 0 || userInput > wordNum || crosswordArr[userInput-1].isFound == true)
        {
            printf("Invalid, Try again \n");
        }
    }while(userInput < 0 || userInput > wordNum || crosswordArr[userInput-1].isFound == true);

    userInput-=1;

    printf("Enter your solution: \n");
    scanf("%s", userAnswer);

    if(strcasecmp(userAnswer, crosswordArr[userInput].solution) ==0){
        crosswordArr[userInput].isFound = true;
        if (strcasecmp("Horizontal", crosswordArr[userInput].Orientation) == 0) {
            
            for (unsigned int i = 0; i < strlen(crosswordArr[userInput].solution); i++) {
                board[crosswordArr[userInput].r - 1] [crosswordArr[userInput].c - 1 + i] = crosswordArr[userInput].solution[i];

            }
        }

        else {
            for (unsigned int i = 0; i < strlen(crosswordArr[userInput].solution); i++) {
                board[crosswordArr[userInput].r - 1 + i] [crosswordArr[userInput].c - 1] = crosswordArr[userInput].solution[i];
            }
        }
    }
    else
        {
            printf("\n Sorry try again.\n");
        }
    } while (1);
    
    free(crosswordArr);

    return 0;
}



