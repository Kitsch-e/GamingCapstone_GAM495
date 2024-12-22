// Fill out your copyright notice in the Description page of Project Settings.

#include "CoatGenerator.h"

#include <random>  // for randomly selecting genes

CoatGenerator::CoatGenerator()  // constructor
{
}

CoatGenerator::~CoatGenerator()  // destructor
{
}

char CoatGenerator::generateBaseCoat(int domE, int recE, int domA, int recA)
{
	// returns a pointer to the sorted array
	int* sortedGenesPtr = sortGenes(domE, recE, domA, recA);

	// returns a char representing the base coat
	/*
	* black -> K
	* chestnut -> C
	* bay -> B
	*/
	if (sortedGenesPtr[0] == 101) {  // ee__
		return 'C';
	}
	else {
		if (sortedGenesPtr[2] == 97) {  // E_aa
			return 'K';
		}
		else {  // E_A_
			return 'B';
		}
	}
}

char CoatGenerator::generateExactCoat(char baseCoat, int domE, int recE, int domA, int recA)
{
	// returns a pointer to the sorted array
	int* sortedGenesPtr = sortGenes(domE, recE, domA, recA);

	if (baseCoat == 'K')  // black
	{
		return 'K';  // black
	}
	else if (baseCoat == 'C')  // chestnut
	{
		/*
		*	light chestnut -> CL
		*	pale chestnut -> CP
		*	liver chestnut -> CR
		*	sorrel -> CS
		*	golden chestnut -> CG
		*	bright chestnut -> CB
		*	medium chestnut -> CM
		*	copper chestnut -> CC
		*/
		if (sortedGenesPtr[2] == 43) {  // A+_
			if (rand() % 101 <= 50) {
				return 'L';  // light chestnut
			}
			else {
				return 'P';  // pale chestnut
			}
		}
		else {
			if (sortedGenesPtr[2] == 97) {  // aa
				return 'R';  // liver chestnut
			}
			else if (sortedGenesPtr[3] == 65) {  // AA
				if (rand() % 101 <= 20) {
					return 'S';  // sorrel
				}
			}
			else if (sortedGenesPtr[2] == 116) {  // AtAt, Ata
				if (rand() % 101 <= 10) {
					return 'G';  // golden chestnut
				}
			}
		}
		// all other coat attempts failed
		int coatChance = rand() % 3;
		if (coatChance == 0) {
			return 'B';  // bright chestnut
		}
		else if (coatChance == 1) {
			return 'M';  // medium chestnut
		}
		else {
			return 'C';  // copper chestnut
		}
	}
	else  // bay
	{
		/*
		* Bay -> B
		*	wild bay -> BW
		*	seal brown -> BS
		*	mahogany bay -> BM
		*	dark bay -> BD
		*	golden bay -> BG
		*	light bay -> BL
		*	blood bay -> BB
		*	cherry bay -> BY
		*	classic bay -> BC
		*	copper bay -> BR
		*/
		if (sortedGenesPtr[2] == 43) {  // A+_
			return 'W';  // wild bay
		}
		else {
			if (sortedGenesPtr[2] == 116) {  // AtAt, Ata
				return 'S';  // seal brown
			}
			else {  // AA, Aa, AAt
				if (sortedGenesPtr[3] != 116) {
					if (sortedGenesPtr[1] == 69) {  // EEAA, EEAa
						if (rand() % 101 <= 50) {
							if (sortedGenesPtr[3] == 65) {  // EEAA
								return 'M';  // mahogany bay
							}
							else {  // EEAa
								return 'D';  // dark bay
							}
						}
					}
					else {  // EeAA, EeAa
						int coatChance = rand() % 101;
						if (sortedGenesPtr[3] == 65) {  // EeAA
							if (coatChance <= 60) {
								if (coatChance <= 10) {
									return 'G';  // golden bay
								}
								else {
									return 'L';  // light bay
								}
							}
						}
						else {  // EeAa
							if (coatChance <= 60) {
								if (coatChance <= 10) {
									return 'B';  // blood bay
								}
								else {
									return 'Y';  // cherry bay
								}
							}
						}
					}
				}
			}
			// all other coat attempts failed
			int coatChance = rand() % 2;
			if (coatChance == 0) {
				return 'C';  // classic bay
			}
			else {
				return 'R';  // copper bay
			}
		}
	}
}

// generates one of the two E genes randomly
/*
* genetic number system, taken from the decimal unicode
* E -> 69
* e -> 101
*/
int CoatGenerator::generateEGene()
{
	int E = rand() % 2;  // creates a random integer, either 1 or 2

	// assigns correct Extension value
	if (E == 0) {
		E = 69;
	}
	else {
		E = 101;
	}

	return E;
}

// generates one of the four A genes randomly
/*
* genetic number system, taken from the decimal unicode
* A -> 65
* a -> 97
* At -> 116
* A+ -> 43
*/
int CoatGenerator::generateAGene()
{
	int A;

	// decides if Agouti will be At or A+
	int AtChance = rand() % 101;
	int ApChance = rand() % 101;
	if (AtChance <= 5) {
		A = 116;
	}
	else if (ApChance <= 50) {
		A = 43;
	}
	else {
		A = rand() % 2;
	}

	// assigns correct Agouti value
	if (A == 0) {
		A = 65;
	}
	else {
		A = 97;
	}

	return A;
}

// returns a sorted integer array of passed in genes
int* CoatGenerator::sortGenes(int domE, int recE, int domA, int recA)
{
	/*
	* sorts genes before deciding on a base coat
	* illegal gene pairings include:
	* eE
	* aA
	* AtA
	* _A+
	*/

	// local variables to store sorted genes
	int locDomE;
	int locRecE;
	int locDomA;
	int locRecA;

	if (domE > recE) {  // eE instead of Ee
		locDomE = 69;
		locRecE = 101;
	}
	else
	{
		locDomE = domE;
		locRecE = recE;
	}

	if (domA > recA) {  // aA, aA+, AA+, Ata, AtA, or AtA+
		// swaps genes
		locDomA = recA;
		locRecA = domA;
		// options became
		// Aa, A+a, A+A, aAt, AAt, or A+At

		// swaps aAt to Ata
		if (locDomA == 97) {
			locDomA = 116;
			locRecA = 97;
		}
	}
	else {  // A+A, A+a, A+At, Aa, AAt, or aAt
		// swaps aAt to Ata
		if (domA == 97) {
			locDomA = 116;
			locRecA = 97;
		}
	}

	int* sortedGenes = new int[4];

	sortedGenes[0] = locDomE;
	sortedGenes[1] = locRecE;
	sortedGenes[2] = locDomA;
	sortedGenes[3] = locRecA;

	return sortedGenes;
}
