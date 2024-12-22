// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GAM495_CapstoneGameMode.generated.h"

UCLASS(minimalapi)
class AGAM495_CapstoneGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGAM495_CapstoneGameMode();

	// array storing all AI_TagChar BP instances in the world
	TArray<AActor*> foundActors;

	// getter to number of actors
	int GetTotalAIActors();
};

