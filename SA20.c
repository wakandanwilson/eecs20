#include <stdio.h>
#include <stdlib.h>

/*
16.1
Write a C function that takes as a parameter a character string of unknown length, containing a single word. Your function should 
translate this string from English into Pig Latin. This translation is performed by removing the first letter of the string, 
appending it onto the end, and concatenating the letters ay. You can assume that the array contains enough space for you to add 
the extra characters. For example, if your function is passed the string “Hello,” after your function returns, the string should 
have the value “elloHay.” The first character of the string should be “e.”

void pigLatin(){

}

int main(void){
    printf("Enter a string: \n");
    scanf();

    return 0;
}
*/


/*
16.9
Write a program to remove any duplicates from a sequence of numbers. For example, if the list consisted of the numbers 5,4,5,5, 
and 3, the program would output 5,4,3.
*/
#define SIZE 100

void removeDupes(int numList[SIZE]){
    int finalList[100] = {0};
    for (int i = 0; i < sizeof(numList); i++){
        
    }

}

int main(void){
    int numList[] = {};

}

/*
16.10
Write a program to find the median of a set of numbers. Recall that the median is a number within the set in which half the 
numbers are larger and half are small. Hint: To perform this, you may need to sort the list first.
*/