// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_TagChar.h"
#include "Components/SphereComponent.h"
#include "GAM495_CapstoneCharacter.h"  // to cast to player character

// Sets default values
AAI_TagChar::AAI_TagChar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// instantiate collision sphere
	detectCollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("collision sphere"));
	detectCollisionSphere->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AAI_TagChar::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAI_TagChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAI_TagChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

USphereComponent* AAI_TagChar::getDetectCollisionSphere()
{
	return detectCollisionSphere;
}

