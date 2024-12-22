// Fill out your copyright notice in the Description page of Project Settings.


#include "Campfire.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

// Sets default values
ACampfire::ACampfire()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	// initialization for actor components
	boxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("fire collision component"));
	boxCollision->InitBoxExtent(FVector(50.0f, 50.0f, 50.0f));
	RootComponent = boxCollision;

	// bind overlap functions
	boxCollision->OnComponentBeginOverlap.AddDynamic(this, &ACampfire::OnOverlapBegin);
	boxCollision->OnComponentEndOverlap.AddDynamic(this, &ACampfire::OnOverlapEnd);

	// initialize boolean value
	bCanApplyDamage = false;
}

// check if fire damage need be applied & call ApplyFireDamage if so
void ACampfire::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// check if collision is not nothing, and is not itself
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		if (OtherActor)
		bCanApplyDamage = true;
		playerCharacter = Cast<AActor>(OtherActor);
		fireHit = SweepResult;
		GetWorldTimerManager().SetTimer(fireTimerHandle, this, &ACampfire::ApplyFireDamage, 2.2f, true, 0.0f);
	}
}

// stop applying fire damage
void ACampfire::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	bCanApplyDamage = false;
	GetWorldTimerManager().ClearTimer(fireTimerHandle);
}

// apply damage while fireTimerHandle is running
void ACampfire::ApplyFireDamage()
{
	if (bCanApplyDamage)
	{
		UGameplayStatics::ApplyPointDamage(playerCharacter, 5.0f, GetActorLocation(), fireHit, nullptr, this, fireDamageType);
	}
}

// Called when the game starts or when spawned
void ACampfire::BeginPlay()
{
	Super::BeginPlay();

	// spawn fire particle system
	if (particleFire)
	{
		UNiagaraComponent* fireComp = UNiagaraFunctionLibrary::SpawnSystemAttached(particleFire, boxCollision, NAME_None, FVector(0.0f, 0.0f, 0.0f), FRotator(0.0f), EAttachLocation::KeepRelativeOffset, true);
	}
}

/*
// Called every frame
void ACampfire::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
*/

