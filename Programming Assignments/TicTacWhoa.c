#include <stdio.h>
#include <stdbool.h>

#define SIZE 3

bool gameWon(char board[SIZE][SIZE], char player);
bool isBoardFull(char board[SIZE][SIZE]);
void initializeBoard(char board[SIZE][SIZE]);
void playerInput(char *row, int *col);
void updateMove(char board[SIZE][SIZE], char row, int col, char player);
//void printBoard();

void updateMove(char board[SIZE][SIZE], char row, int col, char player){
    board[row][col] = player;
}

bool gameWon(char board[SIZE][SIZE], char player){
    //check each row and column
    for (int i = 0; i < SIZE; i++){
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) || (board[0][i] == player && board[1][i] == player && board[2][i] == player)){
            return true;
        }
    }
    //check diagonals
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) || (board[3][1] == player && board[2][2] == player && board[1][3])){
        return true;
    }

    return false;
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

    char player = 'X'; //X is 1, O is 2

    //while loop
    while (gameWon == false && isBoardFull == false){

        gameWon(board[SIZE][SIZE], player);
        isBoardFull(board[SIZE][SIZE]);
        //run game

        //get player input
        int row; //initialize row, col
        char col;
        playerInput(&row, &col); //pass memory address as parameter
    }

    //check if board is full
    return 0;
}