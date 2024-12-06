#include <stdio.h>
#include <stdbool.h>

//const int 3 (3x3 matrix)
#define SIZE 3

bool gameWon(char board[SIZE][SIZE], char player);
bool isBoardFull(char board[SIZE][SIZE]);
bool isMoveValid(int row, char col, char board[SIZE][SIZE]);
void initializeBoard(char board[SIZE][SIZE]);
void playerInput(int *row, char *col);
void updateMove(char board[SIZE][SIZE], int row, int col, char player);
void printCurrentBoard(char board[SIZE][SIZE]);


//check if player input is valid 
bool isMoveValid(int row, char col, char board[SIZE][SIZE]){
    if ((col >= 'A' && col <= 'C') && (row >= 1 && row <= 3)) {
        int rowIndex = 3 - row; //convert to board index
        int colIndex = col - 'A';
        if (board[rowIndex][colIndex] == '_' || board[rowIndex][colIndex] == ' ') {
            return true;
        }
    }
    return false;
}

//print the current board after player's move
void printCurrentBoard(char board[SIZE][SIZE]){
    for (int i =0; i < 3; i++){
        printf("%d ", 3-i);
        for (int j = 0; j < 3; j++){
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

//update board based on player's move
void updateMove(char board[SIZE][SIZE], int row, int col, char player){
    board[row][col] = player;
}

//check if game is won
bool gameWon(char board[SIZE][SIZE], char player){
    //check each row and column
    for (int i = 0; i < SIZE; i++){
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) || (board[0][i] == player && board[1][i] == player && board[2][i] == player)){
            return true;
        }
    }
    //check diagonals
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) || (board[0][2] == player && board[1][1] == player && board[2][0])){
        return true;
    }

    return false;
}

//get player input, update row and col
void playerInput(int *row, char *col){ //points to value in address to directly modify
    scanf(" %c%d", col, row);
}

//check if board is full (return true if board is full)
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

//print empty board
void initializeBoard(char board[SIZE][SIZE]){
    for (int i = 0; i < 3; i++){ //rows
        printf("%d ", 3-i);
        for (int j = 0; j < 3; j++){ //columns
            if (i < 2){
                printf("___");
            }
            if (i == 2){
                printf("   ");
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

    char currentPlayer = 'X'; //X is 1, O is 2
    bool gameEnd = false;

    //while loop game no end
    while (gameEnd == false && isBoardFull(board) == false){
        //print board each time

        //get player input
        int row; //initialize row, col
        char col;
        printf("Player %c's move: ", currentPlayer);
        playerInput(&row, &col); //pass memory address as parameter

        //convert input into indices
        int rowIndex = 3 - row;
        int colIndex = col - 'A';

        if (isMoveValid(row,col,board)){
            updateMove(board, rowIndex, colIndex, currentPlayer);
            if (gameWon(board, currentPlayer)){
                gameEnd = true;
                printCurrentBoard(board);
                printf("Player %c wins\n", currentPlayer);
            }
            else{
                if (currentPlayer == 'X'){
                    currentPlayer = 'O';
                }
                else if (currentPlayer == 'O'){
                    currentPlayer = 'X';
                }
                printCurrentBoard(board);
            }
        }
        else {
            printf("Invalid move. Try again\n");
        }
        if (isBoardFull(board)){
        printf("Board is full.");
        }
    }

    return 0;
}