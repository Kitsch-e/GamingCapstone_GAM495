// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AI_TagChar.generated.h"

UCLASS()
class GAM495_CAPSTONE_API AAI_TagChar : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAI_TagChar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	// collision sphere to detect when player 'tags' AI
	UPROPERTY(EditAnywhere)
	class USphereComponent* detectCollisionSphere;

public:
	// getter of collision sphere
	class USphereComponent* getDetectCollisionSphere();
};
