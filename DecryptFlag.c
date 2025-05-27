/*
This is meant to reverse the encrypted file from HTB Simple Encryptor reversing challenge
*/

#include <stdio.h>
#include <stdlib.h>

unsigned char rotateRight(unsigned char val, unsigned int shifter) {
  return (val >> shifter) | (val << (8-shifter));
}

int main() {
  FILE *flag = fopen("flag.enc", "rb");

  fseek(flag, 0, SEEK_END);
  long sizeOfFlag = ftell(flag) - 4;
  fseek(flag, 4, SEEK_SET);

  unsigned char *allocSize = malloc(sizeOfFlag);
  fread(allocSize, sizeOfFlag, 1, flag);
  fclose(flag);

  srand(1655780698);
  for (int a = 0; a < sizeOfFlag; a++) {
	int xorKey = rand() & 0xFF;
	int shifter = rand() & 7;

	unsigned char val = allocSize[a];
	val = rotateRight(val, shifter);	
	val ^= (unsigned char)xorKey;
	allocSize[a] = val;
  }

  fwrite(allocSize, 1, sizeOfFlag, stdout);
  free(allocSize);

  return 0;
}
