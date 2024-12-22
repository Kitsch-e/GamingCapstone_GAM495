// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Runtime/Engine/Classes/Engine/TargetPoint.h"  // AI selects a random target point
#include "AI_TagController.generated.h"

/**
 * AI controller class
 * dictates how the AI acts before and after getting 'tagged' by the player character
 * controls the AI_TagChar character file.
 */
UCLASS()
class GAM495_CAPSTONE_API AAI_TagController : public AAIController
{
	GENERATED_BODY()

public:
	// BeginPlay and Tick overrides
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// float determining personal space awareness
	UPROPERTY(EditAnywhere)
	float playerBubble;

private:  // code that handles waypoints
	// array storing available waypoints
	UPROPERTY()
	TArray<AActor*> Waypoints;

	// function which selects a waypoint
	UFUNCTION()
	ATargetPoint* GetRandomWaypoint();

	// moves AI to selected waypoint
	UFUNCTION()
	void GoToRandomWaypoint();

private:  // code that handles follow behavior
	// local variable storing cast to player character
	APawn* playerPawn;
	class AGAM495_CapstoneCharacter* playerChar;

	// stores a random location
	FNavLocation navigationLocation;

	class UNavigationSystemV1* navigationArea;

	// pointer to TagChar class
	class AAI_TagChar* tagAI;

	// vector storing a random location
	FVector randomLocale = FVector();

	// bools determining state of AI
	bool bFollowPlayer;
	bool bHide;

	// functions to execute AI behavior
	void GenerateRandomHideLocation();
	void HideFromPlayer();
	void FollowPlayer();

	// Timer to handle wait periods
	FTimerHandle hideTimerHandle;

public:  // public functions
	void OnMoveCompleted(FAIRequestID requestID, const FPathFollowingResult& result) override;

	/*
	UFUNCTION()
	void OnDetectPlayerBeginOverlap(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult);

	UFUNCTION()
	void OnDetectPlayerEndOverlap(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex);
	*/

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult);

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
