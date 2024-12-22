// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Horse_Actor.generated.h"

UCLASS()
class GAM495_CAPSTONE_API AHorse_Actor : public AActor
{
	GENERATED_BODY()

	// mesh representing the horse
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* horseMesh;

	// material color
	UPROPERTY()
	FLinearColor coatLinearColor;

	// material which overrides default coat material
	UPROPERTY(EditAnywhere)
	UMaterialInterface* coatMAT;

	// dynamic material which overrides coatMAT
	UPROPERTY()
	UMaterialInstanceDynamic* coatDMI;
	
public:
	// Sets default values for this actor's properties
	AHorse_Actor();

	// array which stores this actor's specific coat
	char horseCoat[2];

	// arrays which store the actor's specific genes
	// are not sorted properly
	int eGenes[2];
	int aGenes[2];

	// applies a material to the actor based on the genetic code gleaned from
	// CoatGenerator.cpp
	void setMaterial(char coatColor[2]);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// generates actor's gene code & sorts it
	void generateGenes();

	// generates actor's coat based on genes
	void generateCoat();

	/*
	// array which stores pixel info for coatTexture
	uint8* texturePixels;

	// stores the size of the texture
	uint32 texturePixelsSize;

	// stores the size of the square root texture
	uint32 texturePixelsSqrtSize;

	// stores the total number of pixels
	uint32 texturePixelsTotalCount;

	// material texture
	UPROPERTY(EditAnywhere)
	UTexture2D* coatTexture;

	// pointer which updates the texture
	FUpdateTextureRegion2D* textureRegion;
	*/
};
