// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "GAM495_CapstoneCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AGAM495_CapstoneCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* MoveAction;
	
public:
	AGAM495_CapstoneCharacter();

protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
		
	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	/** Bool for AnimBP to switch to another animation set */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	bool bHasRifle;

	/** Setter to set the bool */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void SetHasRifle(bool bNewHasRifle);

	/** Getter for the bool */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	bool GetHasRifle();

	// decides if the game has been won or not
	UPROPERTY(EditAnywhere)
	bool bWon;

	// stores max health for the player
	UPROPERTY(EditAnywhere)
	float maxHealth;

	// stores the current health for the player
	UPROPERTY(EditAnywhere)
	float currentHealth;

	// stores current game time
	UPROPERTY(EditAnywhere)
	float currentGameTime;

	// timer handle for game timer
	FTimerHandle gameTimerHandle;

	void setHUDGameTimer();

	// called to update player health
	void UpdateHealth(float healthDelta);

	// called when game ends
	void gamePlayEnd(bool winLose);

	void OnTakePointDamage(AActor* damagedActor, float damage, const UDamageType* DamageType, AController* instigator, AActor* damageCauser);

protected:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

public:  // HUD display
	// stores HUD to display on viewport
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UGAM495_CapstoneHUD> playerHUDClass;

	// stores the instance of the HUD
	UPROPERTY()
	class UGAM495_CapstoneHUD* playerHUD;

	// stores HUD to swap to when gameplay has ended
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UWinLoseStateHUD> endPlayHUDClass;

	// stores instance of the win/lose HUD
	UPROPERTY()
	class UWinLoseStateHUD* endHUD;

public:
	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }
	// returns pointer to HUD widget
	UGAM495_CapstoneHUD* GetFirstPersonHUDComponent() const { return playerHUD; }
};

