// Copyright Epic Games, Inc. All Rights Reserved.

#include "GAM495_CapstoneGameMode.h"
#include "GAM495_CapstoneCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "AI_TagChar.h"  // for finding AIs in level
#include "GAM495_CapstoneCharacter.h"  // for casting to HUD
#include "GAM495_CapstoneHUD.h"

AGAM495_CapstoneGameMode::AGAM495_CapstoneGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// counts AI_TagChar BP instances in the level
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAI_TagChar::StaticClass(), foundActors);
}

int AGAM495_CapstoneGameMode::GetTotalAIActors()
{
	/*
	* crashes Engine
	* I assume it has something to do with foundActors not being initialized
	* and so when attempting to find the length, the Engine crashes
	* haven't proved this.
	*/
		return foundActors.Num();
}