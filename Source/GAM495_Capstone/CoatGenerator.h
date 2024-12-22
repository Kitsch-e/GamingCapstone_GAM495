// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * generates and reads a horse coat based on the first two horse genes, Extension and Agouti
 */
class GAM495_CAPSTONE_API CoatGenerator
{
public:
	CoatGenerator();  // constructor
	~CoatGenerator();  // destructor

	/*
	* Black -> K
	* Chestnut -> C
	*	light chestnut -> CL
	*	pale chestnut -> CP
	*	liver chestnut -> CR
	*	sorrel -> CS
	*	golden chestnut -> CG
	*	bright chestnut -> CB
	*	medium chestnut -> CM
	*	copper chestnut -> CC
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

	// generates a coat based on the genes passed in as arguments
	char generateBaseCoat(int domE, int recE, int domA, int recA);
	// pass in returned char from generateBaseCoat as first argument
	char generateExactCoat(char baseCoat, int domE, int recE, int domA, int recA);

	// returns an integer representing one Extension or Agouti gene
	int generateEGene();
	int generateAGene();

private:
	// function that returns a pointer to an integer array of its sorted arguments
	int* sortGenes(int domE, int recE, int domA, int recA);
};
