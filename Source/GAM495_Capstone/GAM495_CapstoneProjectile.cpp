// Copyright Epic Games, Inc. All Rights Reserved.

#include "GAM495_CapstoneProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

AGAM495_CapstoneProjectile::AGAM495_CapstoneProjectile() 
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(30.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AGAM495_CapstoneProjectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// create a static mesh representing the projectile
	sphereMesh = CreateDefaultSubobject<UStaticMeshComponent>("SphereMesh");

	// Set root component
	RootComponent = CollisionComp;
	// setup attachments
	sphereMesh->SetupAttachment(CollisionComp);

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

void AGAM495_CapstoneProjectile::BeginPlay()
{
	Super::BeginPlay();

	// 4Vector with random values for RGB and full alpha
	projColor = FLinearColor(UKismetMathLibrary::RandomFloatInRange(0.f, 1.f), UKismetMathLibrary::RandomFloatInRange(0.f, 1.f), UKismetMathLibrary::RandomFloatInRange(0.f, 1.f), 1.f);

	// creates a MID using material set in Editor
	projMID = UMaterialInstanceDynamic::Create(projMat, this);

	// string is name of parameter in material in Editor
	projMID->SetVectorParameterValue("projColor", projColor);

	// assigns random color to projectile
	sphereMesh->SetMaterial(0, projMID);
}

void AGAM495_CapstoneProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// projectile hit something
	if (OtherActor != nullptr)
	{
		// particleSystem set in projectile BP
		if (particleSystem)
		{
			// create Niagara component at projectile landing location
			UNiagaraComponent* particleComp = UNiagaraFunctionLibrary::SpawnSystemAttached(particleSystem, HitComp, NAME_None, FVector(-20.f, 0.f, 0.f), FRotator(0.f), EAttachLocation::KeepRelativeOffset, true);
			// apply color of projectile to particle system
			particleComp->SetNiagaraVariableLinearColor(FString("RandomColor"), projColor);

			// destroy the projectile mesh (projectile still exists for the InitalLifeSpan set in constructor)
			// simply Destory() the projectile would destroy the particles as well
			sphereMesh->DestroyComponent();
			// stop all subsequent collisions (to avoid spawining more particles)
			CollisionComp->BodyInstance.SetCollisionProfileName("NoCollision");
		}
	}

	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());

		Destroy();
	}
}