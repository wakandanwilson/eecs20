#include <stdio.h>

int main(void){

    //initialize start and end values
    char startChar;
    char endChar;
    int startInt = 0;
    int endInt = 0;

    //prompt user for starting character
    printf("Enter a starting character: ");
    scanf(" %c", &startChar);
    startInt = (int)startChar;

    //prompt user for ending character
    printf("Enter an ending character: ");
    scanf(" %c", &endChar);
    endInt = (int)endChar;

    //if characters are the same, print the char
    if (startInt == endInt){
        printf("%c", (char)startInt);
    }
    //if startChar is before endChar, print forwards
    else if (startInt < endInt){
        for (int i = startInt; i <= endInt; i++){
            printf("%c",(char)i);
            if (i < endInt){
                printf(", ");
            }
        }
    }
    //if endChar is before startChar, print backwards
    else if (startInt > endInt){
        for (int i = startInt; i >= endInt; i--){
            printf("%c",(char)i);
            if (i > endInt){
                printf(", ");
            }
        }
    }

    return 0;
}