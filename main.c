#define dSize 64
#define phalfSize 32
#define kComSize 56
#define kHalComSize 28
#define ull unsigned long long

#include <stdio.h>
#include "tables.c"
#include "functions.c"
#include "Encrypted.c"

void main()
{
	ull hexPlain = 0x00, hexKey = 0x00;
	int *plainBlock[dSize] = { 0 }, *cipherBlock[dSize] = { 0 }, *keyWithParities[dSize] = { 0 };
	int  *RoundKeys[16][48] = { 0 };
    
   printf("Input PlainText:");
   scanf_s("%I64x", &hexPlain);
   printf("Input key:");
   scanf_s("%I64x", &hexKey);

    hexToBin(dSize,hexPlain, plainBlock);
    hexToBin(dSize,hexKey,keyWithParities);

    Key_Generator(keyWithParities, RoundKeys, ShiftTable);
	Encrypted(plainBlock, RoundKeys, cipherBlock);
    }