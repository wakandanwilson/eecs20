#include <stdio.h>
#include <stdbool.h>

//const int 3 (3x3 matrix)
#define SIZE 3

bool gameWon(char board[SIZE][SIZE], char player);
bool isBoardFull(char board[SIZE][SIZE]);
bool isMoveValid(int row, char col);
void initializeBoard(char board[SIZE][SIZE]);
void playerInput(int *row, char *col);
void updateMove(char board[SIZE][SIZE], int row, int col, char player);
void printCurrentBoard(char board[SIZE][SIZE]);


//check if player inout is valid 
bool isMoveValid(int row, char col){
    if ((col == 'A' || col == 'B' || col == 'C') && (row == 1 || row == 2 || row == 3)){
        return true;
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
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) || (board[3][1] == player && board[2][2] == player && board[1][3])){
        return true;
    }

    return false;
}

//get player input, update row and col
void playerInput(int *row, char *col){ //points to value in address to directly modify
    scanf("%c%d", col, row);
}

//check if board is full (no more moves)
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
    while (gameEnd == false){
        //run game

        //get player input
        int row; //initialize row, col
        char col;
        printf("Player %c's move: ", currentPlayer);
        playerInput(&col, &row); //pass memory address as parameter

        //convert input into indices
        int rowIndex = 3 - row;
        int colIndex = (int)col - 65;

        if (isMoveValid(rowIndex,col)){
            updateMove(board, rowIndex, colIndex, currentPlayer);
            if (gameWon(board, currentPlayer)){
                gameEnd = true;
                printCurrentBoard(board);
                printf("Player %c wins\n", currentPlayer);
            }
            else if (isBoardFull(board)){
                gameEnd = true;
                printCurrentBoard(board);
                printf("Board is full.\n");
            }
            else{
                if (currentPlayer == 'X'){
                    currentPlayer = 'O';
                }
                else if (currentPlayer == 'O'){
                    currentPlayer = 'X';
                }
            }
        }
        else if(!isMoveValid(rowIndex,col)){
            printf("Invalid move, please specify both column and row.");
        }
    }

    return 0;
}