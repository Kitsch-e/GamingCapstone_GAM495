// Fill out your copyright notice in the Description page of Project Settings.


#include "DayNightCycle.h"

// Sets default values
ADayNightCycle::ADayNightCycle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called every frame
void ADayNightCycle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// check if a light source has been assigned in the Editor
	if (directionalLightSource)
	{
		// rotate the light source
		directionalLightSource->AddActorLocalRotation(FRotator((DeltaTime * sunTurnRate), 0, 0));
	}

	// check if a sun actor has been assigned in the Editor
	if (sunActor)
	{
		// move the sun
		FOutputDeviceNull ODN;
		sunActor->CallFunctionByNameWithArguments(TEXT("UpdateSunDirection"), ODN, NULL, true);
	}
}

