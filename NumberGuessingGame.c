#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

void SearchAlgorithm(unsigned int* ComputerGuess, unsigned int* RandNum, unsigned int* RngOfNumsToGss){
    //binary search
    int low = 1;
    unsigned int high = *RngOfNumsToGss;
    int NumOfTries = 0;

    while (*ComputerGuess != *RandNum){
        NumOfTries++;
        *ComputerGuess = floor((low + high) / 2);
        printf("\nComputer's guess: %u", *ComputerGuess);

        if (*ComputerGuess > *RandNum){
            printf("\nToo high!");
            high = *ComputerGuess - 1;
        } 
        else if (*ComputerGuess < *RandNum){
            printf("\nToo low!");
            low = *ComputerGuess + 1;
        }
    }

    printf("\nNice one!");
    printf("\nComputer's number of tries: %d\n\n", NumOfTries);
}

int main(){
    //range of numbers to guess
    unsigned int RngOfNumsToGss;
    printf("Enter range: "); scanf("%u", &RngOfNumsToGss);

    //random number generator
    srand(time(0));
    unsigned int RandNum = (rand() % RngOfNumsToGss) + 1;
    unsigned int ComputerGuess = 0;

    SearchAlgorithm(&ComputerGuess, &RandNum, &RngOfNumsToGss);

    return 0;
}