#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

void Encrypt(FILE **pFile, char fileName[], uint8_t *key) {
    FILE *ppFile = *pFile; //pointer-to-pointer
    int ch;
    uint8_t encryptedChars[256]; //encryptedChars means the Characters from the file, not the "char" datatype
    uint8_t index = 0;
    while ( (ch = fgetc(ppFile)) != EOF) {
        if (index > 255) {
            printf("Error: File is too large.");
            fclose(ppFile);
            exit(1);
        }

        //ch is typecasted into uint8_t because fgetc returns usigned 8bit integers
        //if not EOF (-1)
        encryptedChars[index++] = ((uint8_t) ch) ^ *key; 
    }

    fclose(pFile);
    ppFile = fopen(fileName, "w");
    if(ppFile == NULL) { 
        printf("Error opening file.");
        exit(1);
    }

    *pFile = ppFile;
    for (int a = 0; a < index; a++) {
        fputc(encryptedChars[a], ppFile);
    }

    fclose(ppFile);
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
