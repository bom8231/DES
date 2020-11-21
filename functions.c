//small functions

//permutation function
void permute(int insize, int outsize, int inBlock[], int* outBlock[], const int Table[]) {

	for (int i = 0; i < outsize; i++)
		outBlock[i] = inBlock[Table[i] - 1];

}

//split function
void split(int inSize, int outSize, int inBlock[], int* leftBlock[], int* rightBlock[]) {

	for (int i = 0; i < outSize; i++)
		leftBlock[i] = inBlock[i];

	for (int i = outSize, j = 0; i < inSize, j < outSize; i++, j++)
		rightBlock[j] = inBlock[i];

}

//combine function
void combine(int preSize, int afterSize, int leftBlock[], int rightBlock[], int* outBlock[]) {

	for (int i = 0; i < preSize; i++)
		outBlock[i] = leftBlock[i];

	for (int i = preSize, j = 0; i < afterSize, j < preSize; i++, j++)
		outBlock[i] = rightBlock[j];
}

//copy function
void copy(int size, int original[], int* copy[]) {
	for (int i = 0; i < size; i++)
		copy[i] = original[i];

}

//XOR function
void exclusiveOR(int size, int Block1[], int Block2[], int* outBlock[]) {

	for (int i = 0; i < size; i++)
		outBlock[i] = Block1[i] ^ Block2[i];

}

//shiftLeft
void shiftLeft(int* block[], int numOfShifts) {
	int T = 0;
	for (int i = 0; i < numOfShifts; i++) {
		T = block[0];
		for (int j = 1; j < 28; j++)
			block[j - 1] = block[j];
		block[27] = T;
	}
}

// Hex -> Binary function
void hexToBin(int size, unsigned long long hex, int *array[]) {
	for (int i = 0; i < size; i++) {
		int bit = (hex >> (size - 1 - i)) & 0x01;
		array[i] = bit;
	}

}

// Bin -> Hex function
ull binToHex(int size, int array[])
{
	ull num = 0;

	for (int i = 0; i < size; i++)
		num = num * 2 + array[i];
	return num;
}

//Big Functions

//swapper
void swapper(int* leftBlock[], int* rightBlock[]) {

	int T[32] = { 0 };

	copy(32, leftBlock, T);
	copy(32, rightBlock, leftBlock);
	copy(32, T, rightBlock);

}

//substitute
void substitute(int inBlock[], int* outBlock[], const int SubstitutionTables[][4][16]) {

	int row = 0, col = 0, value = 0;

	for (int i = 0; i < 8; i++) {

		row = 2 * inBlock[i * 6 + 0] + inBlock[i * 6 + 5];
		col = 8 * inBlock[i * 6 + 1] + 4 * inBlock[i * 6 + 2] + 2 * inBlock[i * 6 + 3] + inBlock[i * 6 + 4];

		value = SubstitutionTables[i][row][col];

		outBlock[i * 4 + 0] = (value & 0b1000) >> 3;
		outBlock[i * 4 + 1] = (value & 0b0100) >> 2;
		outBlock[i * 4 + 2] = (value & 0b0010) >> 1;
		outBlock[i * 4 + 3] = (value & 0b0001);
	}
}

//fuction 
function(int *inBlock[], int *RoundKey[][48], int *outBlock[])
{
	int T1[48] = { 0 };
	int T2[48] = { 0 };
	int T3[32] = { 0 };

	permute(32, 48, inBlock, T1, ExpansionPermutationTable);
	exclusiveOR(48, T1, RoundKey, T2);
	substitute(T2, T3, SubstitutionTables);
	permute(32, 32, T3, outBlock, StraightPermutationTable);
}

//Key_Gen
Key_Generator(int keyWithParities[], int *RoundKeys[][48], const int shiftTable[]) {

	int cipherKey[kComSize] = { 0 }, leftKey[kHalComSize] = { 0 }, rightKey[kHalComSize] = { 0 }, preRoundKey[kComSize] = { 0 };

	permute(dSize, kComSize, keyWithParities, cipherKey, ParityDropTable);
	split(kComSize, kHalComSize, cipherKey, leftKey, rightKey);

	for (int round = 0; round < 16; round++) {
		shiftLeft(leftKey, shiftTable[round]);
		shiftLeft(rightKey, shiftTable[round]);
		combine(28, 56, leftKey, rightKey, preRoundKey);
		permute(kComSize, 48, preRoundKey, &RoundKeys[round], KeyCompressionTable);
	}
}

//mixer
void mixer(int *leftBlock[], int *rightBlock[], int *Roundkey[][48]) {
	int *T1[32] = { 0 };
	int *T2[32] = { 0 };
	int *T3[32] = { 0 };

	copy(32, rightBlock, T1);
	function(T1, Roundkey, T2);
	exclusiveOR(32, leftBlock, T2, T3);
	copy(32, T3, leftBlock);
}