// Fill out your copyright notice in the Description page of Project Settings.


#include "WinLoseStateHUD.h"
#include "Components/TextBlock.h"

void UWinLoseStateHUD::setWinLoseText(bool winLose)
{
	if (winLose)  // player won
	{
		WinLoseText->SetText(FText::FromString("You Won!"));
	}
	else  // player lost
	{
		WinLoseText->SetText(FText::FromString("You Lost!"));
	}
}
