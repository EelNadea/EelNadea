#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

void Encrypt(FILE **FilePtr, char fileName[], uint16_t *key) {
    FILE *File = *FilePtr;
    char ch;
    uint16_t decimalCnvrtdChars[256];
    uint16_t index = 0;
    while ( (ch = fgetc(File)) != EOF) {
        if (index >= 255) {
            printf("Error: File is too large.");
            fclose(File);
            exit(1);
        }
        decimalCnvrtdChars[index++] = ((uint16_t)ch) ^ (*key);
    }
    decimalCnvrtdChars[index] = '\0';

    fclose(File);
    File = fopen(fileName, "w");
    if(File == NULL) { 
        printf("Error opening file.");
        exit(1);
    }

    *FilePtr = File;
    for (int a = 0; a < index; a++) {
        fputc(decimalCnvrtdChars[a], File);
    }

    fclose(File);
    *FilePtr = NULL;
}

int main() {
    uint16_t key;
    char fileName[129];
    printf("Enter file name: "); scanf("%128s", fileName);
    printf("Enter key: "); scanf("%hu", &key);

    FILE *File = fopen(fileName, "r");
    if(File == NULL) { 
        printf("Error opening file.");
        return 1;
    } else { Encrypt(&File, fileName, &key); }

    return 0;
}
