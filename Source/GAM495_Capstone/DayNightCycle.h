// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DirectionalLight.h"
#include "Misc/OutputDeviceNull.h"
#include "GameFramework/Actor.h"
#include "DayNightCycle.generated.h"

UCLASS()
class GAM495_CAPSTONE_API ADayNightCycle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADayNightCycle();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Atmosphere")
	AActor* sunActor;

	UPROPERTY(EditAnywhere, Category = "Atmosphere")
	ADirectionalLight* directionalLightSource;

	// decides the turn speed of the sun actor
	UPROPERTY(EditAnywhere, Category = "Atmosphere")
	float sunTurnRate;

};
