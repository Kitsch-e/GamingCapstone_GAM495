// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WinLoseStateHUD.generated.h"

/**
 * 
 */
UCLASS()
class GAM495_CAPSTONE_API UWinLoseStateHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	// widget that displays if the player won or lost the game
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* WinLoseText;

	// sets the text to display if the player won or lost
	void setWinLoseText(bool winLose);
};
