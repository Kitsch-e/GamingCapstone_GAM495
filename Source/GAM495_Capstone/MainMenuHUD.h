// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuHUD.generated.h"

/**
 * 
 */
UCLASS()
class GAM495_CAPSTONE_API UMainMenuHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	// default constructor
	//UMainMenuHUD();

	// button to start the level
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* startBTN;

	// button to quit the game
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* endBTN;
};
