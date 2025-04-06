#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

void Encrypt(FILE **pFile, char fileName[], uint8_t *key) {
    int ch;
    uint8_t encryptedChars[3072]; //encryptedChars means the Characters from the file, not the "char" datatype
    uint16_t index = 0;
    while ( (ch = fgetc(*pFile)) != EOF ) {
        if (index > 3071) {
            printf("Error: File is too large.");
            fclose(*pFile);
            exit(1);
        } else {
            //ch is typecasted into uint8_t because fgetc returns usigned 8bit integers
            //if not EOF (-1)
            encryptedChars[index] = ((uint8_t) ch) ^ *key;
            index++;
        } 
    }

    fclose(*pFile);
    *pFile = fopen(fileName, "w");
    if(*pFile == NULL) { 
        printf("Error opening file.");
        exit(1);
    } else {
        for (int a = 0; a < index; a++) {
            fputc(encryptedChars[a], *pFile);
        }

        fclose(*pFile);
    }
}

int main() {
    uint8_t key;
    char fileName[129];
    printf("Enter file name: "); scanf("%128s", fileName);
    printf("Enter key: "); scanf("%hhu", &key);

    FILE *pFile = fopen(fileName, "r");
    if(pFile == NULL) { 
        printf("Error opening file.");
        return 1;
    } else { Encrypt(&pFile, fileName, &key); }

    return 0;
}