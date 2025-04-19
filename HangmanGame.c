#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

void WordPicker(char *chosenWord) {
    //Random number generator
    srand(time(0));

    const char *wordList[] = {"CAT", "DOG", "SUN", "TREE", "MOON", "STAR", "FISH"};
    uint8_t wordListSize = sizeof(wordList) / sizeof(wordList[0]); //Number of elements
    
    strcpy(chosenWord, wordList[rand() % wordListSize]);
}

int main() {
    char chosenWord[7];
    WordPicker(chosenWord);
    uint8_t chosenWordLength = strlen(chosenWord);

    // 'strlen' does not include the null-terminator
    char displayedChars[chosenWordLength + 1];
    for(int a = 0; a < chosenWordLength; a++) {
        displayedChars[a] = '_';
    }
    displayedChars[chosenWordLength] = '\0';

    uint8_t MaxNumOfGuess = 3;
    printf("Hearts: %d\n%s", MaxNumOfGuess, displayedChars);
    while(MaxNumOfGuess != 0) {
        char userGuess;
        printf("   Guess a letter: "); scanf(" %c", &userGuess);

        bool isGuessCorrect = false;
        for(int c = 0; c < chosenWordLength; c++) {
            if(userGuess == chosenWord[c]) { 
                isGuessCorrect = true;
                displayedChars[c] = userGuess;
            } 
            else { continue; }
        }
        if(isGuessCorrect == false) { 
            --MaxNumOfGuess; 
            printf("\nHearts: %d\n%s", MaxNumOfGuess, displayedChars);
        } else { printf("\n%s", displayedChars); }

        if(strcmp(displayedChars, chosenWord) == 0) {
            printf("\nNice!\n"); 
            return 0;
        }
    }

    return 0;
}