#include <stdio.h>
#include <stdbool.h>
#include <string.h>

//const int 3 (3x3 matrix)
#define SIZE 3

bool gameWon(char board[SIZE][SIZE], char player);
bool isBoardFull(char board[SIZE][SIZE]);
bool isMoveValid(int row, char col, char board[SIZE][SIZE]);
void initializeBoard(char board[SIZE][SIZE]);
void playerInput(char input[]);
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
                if (board[i][j] == '_')
                    printf("   ");
                else
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
void playerInput(char input[]){ //accepts input array as arg, input stores player's input
    fgets(input, 6, stdin); //longest string: Q U I T \n \0
    input[strcspn(input, "\n")] = '\0'; //finds first index where \n and changes to null terminator
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
            board[i][j] = '_';
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
    int playerNum[2] = {1,2};
    bool gameEnd = false;

    //while loop game no end
    while (gameEnd == false && isBoardFull(board) == false){

        char input[6]; //set 6 memory spaces for input

        //get player input
        if (currentPlayer == 'X'){
            printf("Player %d's move (NEW for new game, QUIT to quit): ", playerNum[0]);
        }
        else {
            printf("Player %d's move (NEW for new game, QUIT to quit): ", playerNum[1]);
        }
        playerInput(input);

        //initialize col and row values
        char col;
        int row;

        //check for new game or quit
        if (strcmp(input, "NEW") == 0){ //checks if ASCII values of input and NEW are the same
            printf("New game.\n");
            initializeBoard(board);
            currentPlayer = 'X';
            continue;
        }
        else if (strcmp(input, "QUIT") == 0){
            printf("Quitting game.\n");
            break;
        }

        if (sscanf(input, "%c%d", &col, &row) == 2){ //reads and parses string from input, checks to see if string is 2 chars
            //converts row and col to indices
            int rowIndex = 3 - row;
            int colIndex = col - 'A';

            if (isMoveValid(row,col,board)){
                updateMove(board, rowIndex, colIndex, currentPlayer);
                if (gameWon(board, currentPlayer)){
                    gameEnd = true;
                    printCurrentBoard(board);
                    if (currentPlayer == 'X'){
                        printf("Player %d wins\n", playerNum[0]);
                    }
                    else {
                        printf("Player %d wins\n", playerNum[1]);
                    }
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
        }
        if (isBoardFull(board)){
            printf("Board is full.");
        }
    }
    return 0;
}
