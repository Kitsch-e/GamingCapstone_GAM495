// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"  // for collision detection
#include "Campfire.generated.h"

class UNiagaraSystem;

UCLASS()
class GAM495_CAPSTONE_API ACampfire : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACampfire();

public:
	UPROPERTY(EditAnywhere)
	UNiagaraSystem* particleFire;

	UPROPERTY(EditAnywhere)
	UBoxComponent* boxCollision;

	// fire does damage to player colliding with it
	UPROPERTY(EditAnywhere)
	TSubclassOf<UDamageType> fireDamageType;

	UPROPERTY(EditAnywhere)
	AActor* playerCharacter;

	UPROPERTY(EditAnywhere)
	FHitResult fireHit;

	bool bCanApplyDamage;  // determines if fire will do damage
	FTimerHandle fireTimerHandle;  // determines how long fire will do damage

	// collision begin function
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// collision end function
	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// function to handle fire damage
	UFUNCTION()
	void ApplyFireDamage();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

/*
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
*/

};
