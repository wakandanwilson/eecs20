#include <stdio.h>
#include <stdbool.h>

#define SIZE 3

bool gameWon(char board[SIZE][SIZE], char player);
bool isBoardFull(char board[SIZE][SIZE]);
void initializeBoard(char board[SIZE][SIZE]);
void playerInput(char *row, int *col);


//initialize Plyaer 1 and 2 input to empty string of length 2
char p1input[2];
char p2input[2];

bool gameWon(char board[SIZE][SIZE], char player){
    //check diagonals
    //check each row
    for (int i = 0; i < SIZE; i++){
        if (board[0][i] != '_'){
            
        }
    }
    //check each column
}

void playerInput(int *row, char *col){ //points to value in address to directly modify
    scanf("%c%d", row, col);
}

bool isBoardFull(char board[SIZE][SIZE]){
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            if (board[i][j] == '_'){
                return false;
            }
        }
    }
    return true;
}

void initializeBoard(char board[SIZE][SIZE]){
    for (int i = 0; i < 3; i++){ //rows
        printf("%d ", 3-i);
        for (int j = 0; j < 3; j++){ //columns
            if (i < 2){
                printf("_%c_", board[i][j]);
            }
            if (i == 2){
                printf(" %c ", board[i][j]);
            }
            if (j < 2){
                printf("|");
            }
        }
        printf("\n");
    }
    printf("   A   B   C\n");
}

int main(void){
    //initialize board
    char board[SIZE][SIZE] = {
        {'_','_','_'},
        {'_','_','_'},
        {' ',' ',' '}
    };
    initializeBoard(board);

    //while loop
    while (/*gameWon == false and isBoardFull == false*/true){
        //run game

        //get player input
        int row;
        char col;
        playerInput(&row, &col); //pass memory address as parameter
    }

    //check if board is full
    if (isBoardFull){
        printf("Board is full. Game over.");
        return 0;
    }



    return 0;
}