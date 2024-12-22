// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GAM495_CapstoneProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UNiagaraSystem;

UCLASS(config=Game)
class AGAM495_CapstoneProjectile : public AActor
{
	GENERATED_BODY()

	/** Sphere collision component */
	UPROPERTY(VisibleDefaultsOnly, Category=Projectile)
	USphereComponent* CollisionComp;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;

	// sphere mesh component
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* sphereMesh;

	// projectile color
	UPROPERTY()
	FLinearColor projColor;

	// material which overrides default material
	UPROPERTY(EditAnywhere)
	UMaterialInterface* projMat;

	// dynamic material instance which overrides projMat
	UPROPERTY()
	UMaterialInstanceDynamic* projMID;

	// niagara particle system
	UPROPERTY(EditAnywhere)
	UNiagaraSystem* particleSystem;

public:
	AGAM495_CapstoneProjectile();

protected:
	virtual void BeginPlay();

public:
	/** called when projectile hits something */
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	/** Returns CollisionComp subobject **/
	USphereComponent* GetCollisionComp() const { return CollisionComp; }
	/** Returns ProjectileMovement subobject **/
	UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }
};

