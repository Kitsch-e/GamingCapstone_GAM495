// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_TagController.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "NavigationSystem.h"  // may not be necessary
#include "AI_TagChar.h"
#include "Components/SphereComponent.h"
#include "GAM495_CapstoneCharacter.h"
#include "GAM495_CapstoneProjectile.h"
#include "GameFramework/CharacterMovementComponent.h"  // may not be necessary
#include "GAM495_CapstoneHUD.h"

void AAI_TagController::BeginPlay()
{
	Super::BeginPlay();

	// store a cast to the player character
	playerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	playerChar = Cast<AGAM495_CapstoneCharacter>(playerPawn);

	navigationArea = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);

	// instantiate behavior bools
	bHide = true;
	bFollowPlayer = false;

	// generates a random space to give player when following
	playerBubble = FMath::RandRange(100.0f, 300.0f);

	// generate the first locale
	GenerateRandomHideLocation();
	HideFromPlayer();

	// attempt cast
	tagAI = Cast<AAI_TagChar>(GetPawn());

	// if tagAI exists
	if (tagAI)
	{
		// bind functions to collision sphere inside the AI_TagChar file
		//tagAI->getDetectPlayerCollisionSphere()->OnComponentBeginOverlap.AddDynamic(this, &AAI_TagController::OnDetectPlayerBeginOverlap);
		//tagAI->getDetectPlayerCollisionSphere()->OnComponentEndOverlap.AddDynamic(this, &AAI_TagController::OnDetectPlayerEndOverlap);
		tagAI->getDetectCollisionSphere()->OnComponentBeginOverlap.AddDynamic(this, &AAI_TagController::OnOverlapBegin);
		tagAI->getDetectCollisionSphere()->OnComponentHit.AddDynamic(this, &AAI_TagController::OnHit);
	}
}

void AAI_TagController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// if AI has been 'tagged'
	if (bFollowPlayer)
	{
		// constantly update position
		FollowPlayer();
	}
}

// uses FMath to select a waypoint at random, returns a pointer to it
ATargetPoint* AAI_TagController::GetRandomWaypoint()
{
	// stores a random index within the range of total waypoints
	auto index = FMath::RandRange(0, Waypoints.Num() - 1);
	return Cast<ATargetPoint>(Waypoints[index]);
}

// calls getRandomWaypoint() and instructs the AI to move to that locale
void AAI_TagController::GoToRandomWaypoint()
{
	MoveToActor(GetRandomWaypoint());
}

// selects a random location within a radius around the AI's current locale
void AAI_TagController::GenerateRandomHideLocation()
{
	navigationArea->GetRandomReachablePointInRadius(GetPawn()->GetActorLocation(), 10000.0f, navigationLocation);
	randomLocale = navigationLocation.Location;
}

// instructs the AI to move to the locale stored in the randomLocale vector
void AAI_TagController::HideFromPlayer()
{
	MoveToLocation(randomLocale);
}

// instructs the AI to move to the player, respecting their personal space
void AAI_TagController::FollowPlayer()
{
	MoveToActor(playerPawn, playerBubble);
}

// once a move is completed, start a new move
void AAI_TagController::OnMoveCompleted(FAIRequestID requestID, const FPathFollowingResult& result)
{
	Super::OnMoveCompleted(requestID, result);

	if (bHide)
	{
		GenerateRandomHideLocation();
		HideFromPlayer();
	}
}

/*
// something has collided with the AI's collision sphere
void AAI_TagController::OnDetectPlayerBeginOverlap(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("AI Overlapped!")));
	}

	// casts to player char, if successful than player char overlapped this actor
	AGAM495_CapstoneCharacter* GAM495Char = Cast<AGAM495_CapstoneCharacter>(otherActor);
	// casts to player projectile, if successful than projectile overlapped this actor
	AGAM495_CapstoneProjectile* GAM495Proj = Cast<AGAM495_CapstoneProjectile>(otherActor);

	// cast successful
	if ((GAM495Char) || (GAM495Proj))
	{
		// if HUD exists, change it to reflect the 'tag', if bHide is false this controller has already been 'tagged'
		if ((playerChar->GetFirstPersonHUDComponent()) && (bHide))
		{
			playerChar->GetFirstPersonHUDComponent()->setCounter(1);
		}

		// change AI's behavior state
		bHide = false;
		bFollowPlayer = true;
	}
}


// something has stopped overlapping AI's collision sphere
void AAI_TagController::OnDetectPlayerEndOverlap(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex)
{
	// currently don't need to do anything when this occurs
}
*/

void AAI_TagController::OnOverlapBegin(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult)
{
	// casts to player char, if successful than player char overlapped this actor
	AGAM495_CapstoneCharacter* GAM495Char = Cast<AGAM495_CapstoneCharacter>(otherActor);

	// cast successful
	if (GAM495Char)
	{
		// if HUD exists, change it to reflect the 'tag', if bHide is false this controller has already been 'tagged'
		if ((playerChar->GetFirstPersonHUDComponent()) && (bHide))
		{
			playerChar->GetFirstPersonHUDComponent()->setCounter(1);
		}

		// change AI's behavior state
		bHide = false;
		bFollowPlayer = true;
	}
}

void AAI_TagController::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// casts to player projectile, if successful than projectile overlapped this actor
	AGAM495_CapstoneProjectile* GAM495Proj = Cast<AGAM495_CapstoneProjectile>(OtherActor);

	// cast successful
	if (GAM495Proj)
	{
		// if HUD exists, change it to reflect the 'tag', if bHide is false this controller has already been 'tagged'
		if ((playerChar->GetFirstPersonHUDComponent()) && (bHide))
		{
			playerChar->GetFirstPersonHUDComponent()->setCounter(1);
		}

		// change AI's behavior state
		bHide = false;
		bFollowPlayer = true;
	}
}
