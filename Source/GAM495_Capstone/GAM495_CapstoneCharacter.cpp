// Copyright Epic Games, Inc. All Rights Reserved.

#include "GAM495_CapstoneCharacter.h"
#include "GAM495_CapstoneProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"
// for HUD display
#include "GAM495_CapstoneHUD.h"
#include "WinLoseStateHUD.h"
#include "Blueprint/UserWidget.h"
//#include "GAM495_CapstonePlayerController.h"  // for parenting the HUD

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AGAM495_CapstoneCharacter

AGAM495_CapstoneCharacter::AGAM495_CapstoneCharacter()
{
	// Character doesnt have a rifle at start
	bHasRifle = false;

	// set health
	maxHealth = 50.0f;
	currentHealth = maxHealth;

	// set game time (in seconds)
	currentGameTime = 15.0f;
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));
}

void AGAM495_CapstoneCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	// initializing HUD
	// ensures HUD are only drawn for player characters
	if (IsLocallyControlled() && playerHUDClass)
	{
		//AGAM495_CapstoneCharacter* playerCharacter = GetController<AGAM495_CapstoneCharacter>();  // controller stored inside character class
		APlayerController* playerController = GetController<APlayerController>();
		if (playerController)
		{
			playerHUD = CreateWidget<UGAM495_CapstoneHUD>(playerController, playerHUDClass);
			if (playerHUD)
			{
				playerHUD->AddToPlayerScreen();

				// set starting health value
				playerHUD->setHealth(currentHealth, maxHealth);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("HUD Creation Failed: PlayerHUDClass could not be instantiated."));
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Controller Error: GetController<APatten_GAM312Character>() returned null."));
		}
	}

	// handles receiving damage
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &AGAM495_CapstoneCharacter::OnTakePointDamage);

	// starts timer for game
	GetWorldTimerManager().SetTimer(gameTimerHandle, this, &AGAM495_CapstoneCharacter::setHUDGameTimer, 1.0f, true, 0.0f);
}

void AGAM495_CapstoneCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	/*
	// ensures HUD exists before attempting to modify it
	if (playerHUD)
	{
		playerHUD->RemoveFromParent();
		// cannot kill directly, returns to nullptr to be destroyed naturally
		playerHUD = nullptr;
	}
	*/
}

//////////////////////////////////////////////////////////////////////////// Input

void AGAM495_CapstoneCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AGAM495_CapstoneCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AGAM495_CapstoneCharacter::Look);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AGAM495_CapstoneCharacter::setHUDGameTimer()
{
	if (playerHUD)
	{
		playerHUD->setGameTimer(currentGameTime);
		// decrement time
		currentGameTime = currentGameTime - 1.0f;
	}
	if (currentGameTime <= 0.0f)
	{
		gamePlayEnd(false);
	}
}

void AGAM495_CapstoneCharacter::UpdateHealth(float healthDelta)
{
	// clamps currentHealth value to be between 0 and maxHealth
	currentHealth = FMath::Clamp(currentHealth + healthDelta, 0.0f, maxHealth);

	if (currentHealth == 0.0f)
	{
		// call gamePlayEnd
		gamePlayEnd(false);
	}
}

void AGAM495_CapstoneCharacter::gamePlayEnd(bool winLose)
{
	// clear any timers still running
	GetWorldTimerManager().ClearAllTimersForObject(this);

	// clear old HUD
	playerHUD->RemoveFromParent();
	playerHUD = nullptr;

	// get the player controller
	APlayerController* playerController = GetController<APlayerController>();

	// clear player input
	playerController->DisableInput(playerController);
	// show mouse
	playerController->SetShowMouseCursor(true);

	// add new HUD
	if (playerController)
	{
		endHUD = CreateWidget<UWinLoseStateHUD>(playerController, endPlayHUDClass);
		if (endHUD)
		{
			endHUD->AddToPlayerScreen();
			if (!winLose)  // true state set in HUD by default
			{
				endHUD->setWinLoseText(winLose);
			}
		}
	}
}

void AGAM495_CapstoneCharacter::OnTakePointDamage(AActor* damagedActor, float damage, const UDamageType* DamageType, AController* instigator, AActor* damageCauser)
{
	// clamps currentHealth value to be between 0 and maxHealth
	currentHealth = FMath::Clamp(currentHealth + damage, 0.0f, maxHealth);

	// display health value
	playerHUD->setHealth(currentHealth, maxHealth);

	if (currentHealth == 0.0f)
	{
		// kill player
	}
}

void AGAM495_CapstoneCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AGAM495_CapstoneCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AGAM495_CapstoneCharacter::SetHasRifle(bool bNewHasRifle)
{
	bHasRifle = bNewHasRifle;
}

bool AGAM495_CapstoneCharacter::GetHasRifle()
{
	return bHasRifle;
}