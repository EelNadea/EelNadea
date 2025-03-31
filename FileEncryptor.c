#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

void Encrypt(FILE **FilePtr, char fileName[], uint8_t *key) {
    FILE *File = *FilePtr;
    int ch;
    uint8_t encryptedChars[256]; //encryptedChars means the Characters from the file, not the "char" datatype
    uint8_t index = 0;
    while ( (ch = fgetc(File)) != EOF) {
        if (index > 255) {
            printf("Error: File is too large.");
            fclose(File);
            exit(1);
        }
        encryptedChars[index++] = ((uint8_t) ch) ^ *key; 
    }

    fclose(File);
    File = fopen(fileName, "w");
    if(File == NULL) { 
        printf("Error opening file.");
        exit(1);
    }

    *FilePtr = File;
    for (int a = 0; a < index; a++) {
        fputc(encryptedChars[a], File);
    }

    fclose(File);
}

int main() {
    uint8_t key;
    char fileName[129];
    printf("Enter file name: "); scanf("%128s", fileName);
    printf("Enter key: "); scanf("%hhu", &key);

    FILE *File = fopen(fileName, "r");
    if(File == NULL) { 
        printf("Error opening file.");
        return 1;
    } else { Encrypt(&File, fileName, &key); }

    return 0;
}
