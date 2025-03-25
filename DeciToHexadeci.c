#include <stdio.h>

void Converter (int *DecimalNumber) {
    char InitialHexa[33] = {0}; // This string will be reversed
    int Remainders[32];
    int iteration = 0;

    while (*DecimalNumber != 0) {
        Remainders[iteration] = *DecimalNumber % 16;
        *DecimalNumber /= 16;
        iteration++;
    }

    for (int a = 0; a < iteration; a++) {
        switch (Remainders[a]) {
            case 10: 
                InitialHexa[a] = 'A';
                break;
            case 11:
                InitialHexa[a] = 'B';
                break;
            case 12:
                InitialHexa[a] = 'C';
                break;
            case 13:
                InitialHexa[a] = 'D';
                break;
            case 14:
                InitialHexa[a] = 'E';
                break;
            case 15:
                InitialHexa[a] = 'F';
                break;
            
            default:
                InitialHexa[a] = '0' + Remainders[a]; // Convert digit to character
        }
    }

    // Reverse the string
    char HexadecimalNum[33] = {0};
    for (int b = 0; b < iteration; b++) {
        HexadecimalNum[b] = InitialHexa[iteration -1 -b];
    }

    printf("Hexadecimal equivalent: 0x%s\n", HexadecimalNum);
}

int main () {
    printf("Decimal to Hexadecimal converter\n\n");

    while (1) {
        int DecimalNumber;
        printf("Enter number: "); scanf("%d", &DecimalNumber);
        Converter(&DecimalNumber);
    }
}