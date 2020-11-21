void Encrypted(int* plainBlock[], int* RoundKeys[][48], int *cipherBlock[]) {

	int inBlock[64], leftBlock[32], rightBlock[32], outBlock[64];

	printf("\nPlaintext: %-16llx\n\n", binToHex(64, plainBlock));
	permute(64, 64, plainBlock, inBlock, InitialPermutationTable);
	printf("After initial permutation: %-16llx\n", binToHex(64, inBlock));
	split(64, 32, inBlock, leftBlock, rightBlock);
	printf("After splitting: L0= %-8llx  R0= %-8llx\n\n", binToHex(32, leftBlock), binToHex(32, rightBlock));
	printf("%-8s%10s%11s%15s\n\n", "Round", "Left", "Right", "Round Key");

	for (int round = 0; round < 16; round++) {  //Round16
		mixer(leftBlock, rightBlock, &RoundKeys[round]);
		if (round != 15) swapper(leftBlock, rightBlock);	// Don't swap when final round(16)
		printf("Round %2d    %8llx   %8llx   %-12llx\n", round + 1, binToHex(32, leftBlock), binToHex(32, rightBlock), binToHex(48, &RoundKeys[round]));
	}

	combine(32, 64, leftBlock, rightBlock, outBlock);
	printf("\nAfter combination: %-16llx\n", binToHex(64, outBlock));
	permute(64, 64, outBlock, cipherBlock, FinalPermutationTable);
	printf("Ciphertext: %-16llx\n", binToHex(64, cipherBlock));

}