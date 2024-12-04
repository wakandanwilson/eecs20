#include <stdio.h>

/*
3 ___|___|___
2 ___|___|___
1    |   | 
   A   B   C
*/

/* 
setup:
create 2D array for the 
[]

*/
/*void setup(){
    char board[3][11] = {{"___|___|___"},{"___|___|___"},{"   |   |   "}};
}
*/

int main(void){
    char board[3][3] = {
        {'_','_','_'},
        {'_','_','_'},
        {'_','_','_'}
    };

    for (int i = 0; i < 3; i++){ //rows
        for (int j = 0; j < 3; j++){ //columns
            if (i < 2){
                printf("_%c_", board[i][j]);
            }
            if (i == 3){
                printf("   ");
            }
            if (j < 2){
                printf("|");
            }
        }
        printf("\n");
    }
    printf("   A   B   C");

    return 0;
}