// Fill out your copyright notice in the Description page of Project Settings.


#include "GAM495_CapstoneHUD.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "GAM495_CapstoneGameMode.h"
#include "GAM495_CapstoneCharacter.h"

void UGAM495_CapstoneHUD::setHealth(float currentHealth, float maxHealth)
{
	// healthBar has been assigned in Editor
	if (healthBar)
	{
		healthBar->SetPercent(currentHealth / maxHealth);
	}

	// calls function within the GameMode
	//HUDtotalCount->SetText(FText::AsNumber(GM->GetTotalAIActors()));
}

void UGAM495_CapstoneHUD::setCounter(int counterStep)
{
	// adds step to counter
	HUDInternalCounter = HUDInternalCounter + counterStep;
	
	// create text literal
	HUDcounter->SetText(FText::AsNumber(HUDInternalCounter));
}

void UGAM495_CapstoneHUD::setTotalCount(int total)
{
	HUDtotalCount->SetText(FText::AsNumber(total));
}

void UGAM495_CapstoneHUD::setGameTimer(float newTime)
{
	HUDtimer->SetText(FText::AsNumber(newTime));
}

int UGAM495_CapstoneHUD::getHUDActorCounter()
{
	return HUDInternalCounter;
}
