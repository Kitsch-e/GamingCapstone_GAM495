// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GAM495_CapstoneHUD.generated.h"

/**
 * 
 */
UCLASS()
class GAM495_CAPSTONE_API UGAM495_CapstoneHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	// integer value to perform math on FText for HUDcounter
	int HUDInternalCounter = 0;

	// how many actors are in the level
	// eventually link this to the length of the array in the GameMode.cpp file
	int HUDMaxCount = 6;

public:
	// updates HUD with health information
	void setHealth(float currentHealth, float maxHealth);

	// updates HUD with counter information
	void setCounter(int counterStep);

	// sets total AI_TagChar actors in the level
	void setTotalCount(int total);

	// updates game timer
	void setGameTimer(float newTime);

	// widget that displays current health
	// meta data means that the blueprint widget derived from this c++ code
	// MUST override this data
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UProgressBar* healthBar;

	// widget that displays the current counter for AI 'tagged'
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* HUDcounter;

	// widget that displays the total AI_TagChar actors in the level
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* HUDtotalCount;

	// widget that displays the current time
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* HUDtimer;

	// cast to GameMode
	class AGAM495_CapstoneGameMode* GM;

	// getter
	int getHUDActorCounter();
};
