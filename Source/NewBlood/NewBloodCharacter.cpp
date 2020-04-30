// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "NewBloodCharacter.h"
#include "NewBloodProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "MotionControllerComponent.h"
#include "XRMotionControllerBase.h" // for FXRMotionControllerBase::RightHandSourceId
#include "UnrealNetwork.h"

#include "GameFramework/Actor.h"
#include "InteractableObject.h"
#include "PlayerInventory.h"
#include "PlayerCrosshairsWidget.h"
#include "PlayerInventoryWidget.h"

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

//////////////////////////////////////////////////////////////////////////
// ANewBloodCharacter

ANewBloodCharacter::ANewBloodCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->RelativeLocation = FVector(-39.56f, 1.75f, 64.f); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->RelativeRotation = FRotator(1.9f, -19.19f, 5.2f);
	Mesh1P->RelativeLocation = FVector(-0.5f, -4.4f, -155.7f);

	playerInventory = CreateDefaultSubobject<UPlayerInventory>(TEXT("PlayerInventory"));
	if (playerInventory == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ERROR"));
	}
	canInteract = true;

	bReplicates = true;
	bAlwaysRelevant = true;
}

void ANewBloodCharacter::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	DOREPLIFETIME(ANewBloodCharacter, canInteract);
}

void ANewBloodCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	// Adding Crosshairs to the player viewport
	if (crosshairsWidgetBP != nullptr)
	{
		crosshairsWidgetInstance = CreateWidget<UPlayerCrosshairsWidget>(GetWorld(), crosshairsWidgetBP);
		if (crosshairsWidgetInstance != nullptr)
		{
			crosshairsWidgetInstance->AddToViewport();
		}
	}

	if (inventoryWidgetBP != nullptr)
	{
		if (IsLocallyControlled())
		{
			inventoryWidgetInstance = CreateWidget<UPlayerInventoryWidget>(GetWorld(), inventoryWidgetBP);
			if (inventoryWidgetInstance != nullptr)
			{
				inventoryWidgetInstance->AddToViewport();
				inventoryWidgetInstance->targetInventory = this->playerInventory;
			}
		}
	}
}

void ANewBloodCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Checking if there is anything interactable in front of the player
	if (canInteract)
	{
		// Fires a raycast in the direction that the player is looking
		FVector fireLocation = FirstPersonCameraComponent->GetComponentLocation();
		FVector fireDirection = FirstPersonCameraComponent->GetForwardVector(); //this->GetActorForwardVector();

		FVector startFire = (fireLocation + (fireDirection * interactionStartDistance));
		FVector endFire = (fireLocation + (fireDirection * interactionEndDistance));

		// Checks if the raycast has sit anything
		FHitResult hitObject;
		FCollisionQueryParams collisionParams;
		if (GetWorld()->LineTraceSingleByChannel(hitObject, startFire, endFire, ECC_PhysicsBody, collisionParams))
		{
			// Checks if the hit object is an interactable object
			AInteractableObject* hitInteractable = Cast<AInteractableObject>(hitObject.GetActor());
			if (hitInteractable != nullptr)
			{
				// TODO: Show that a player is already interacting with the object
				if (hitInteractable->GetCanInteract())
				{
					crosshairsWidgetInstance->ShowInteractionOpportunity(true);
				}
				else
				{
					crosshairsWidgetInstance->ShowInteractionOpportunity(true);
				}
			}
			else
			{
				crosshairsWidgetInstance->ShowInteractionOpportunity(false);
			}
		}
		else
		{
			crosshairsWidgetInstance->ShowInteractionOpportunity(false);
		}
	}
}


/*
====================================================================================================
User Input
====================================================================================================
*/
void ANewBloodCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind interact event
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ANewBloodCharacter::TryInteract);


	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &ANewBloodCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ANewBloodCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ANewBloodCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ANewBloodCharacter::LookUpAtRate);

	// Inventory Controls
	//PlayerInputComponent->BindAction("ScrollLeft", IE_Pressed, this, &ANewBloodCharacter::playerInventory->DecreaseSelectedItem);
	//PlayerInputComponent->BindAction("ScrollRight", IE_Pressed, this, &ANewBloodCharacter::playerInventory->IncreaseSelectedItem);

}

void ANewBloodCharacter::SetPlayerControlMode_Implementation(bool canMove)
{
	APlayerController* playerController = Cast<APlayerController>(this->GetController());
	if (playerController != nullptr)
	{
		if (canMove)
		{
			// Enable Player Movement & Camera Rotation
			playerController->SetIgnoreMoveInput(false);
			playerController->SetIgnoreLookInput(false);

			// Showing Crosshairs
			crosshairsWidgetInstance->SetVisibility(ESlateVisibility::Visible);

			// Hide Cursor
			playerController->bShowMouseCursor = false;
			playerController->bEnableClickEvents = false;
			playerController->bEnableMouseOverEvents = false;

			// Enabling Player Interaction
			canInteract = true;
		}
		else
		{
			// Disable Player Movement & Camera Rotation
			playerController->SetIgnoreMoveInput(true);
			playerController->SetIgnoreLookInput(true);

			// Hiding Crosshairs
			crosshairsWidgetInstance->SetVisibility(ESlateVisibility::Hidden);

			// Show Cursor For UI Interaction
			playerController->bShowMouseCursor = true;
			playerController->bEnableClickEvents = true;
			playerController->bEnableMouseOverEvents = true;

			// Disabling Player Interaction
			canInteract = false;
		}
	}
}

bool ANewBloodCharacter::SetPlayerControlMode_Validate(bool canMove)
{
	return true;
}


/*
====================================================================================================
Player Movement
====================================================================================================
*/
void ANewBloodCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void ANewBloodCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void ANewBloodCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ANewBloodCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}


/*
====================================================================================================
Interaction
====================================================================================================
*/
void ANewBloodCharacter::TryInteract()
{
	AActor* owner = this->GetOwner();
	FString name = owner->GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s Server Is Trying To Interact"), *name);

	if (canInteract)
	{
		// Fires a raycast in the direction that the player is looking
		FVector fireLocation = FirstPersonCameraComponent->GetComponentLocation();
		FVector fireDirection = FirstPersonCameraComponent->GetForwardVector();

		FVector startFire = (fireLocation + (fireDirection * interactionStartDistance));
		FVector endFire = (fireLocation + (fireDirection * interactionEndDistance));

		// Checks if the raycast has sit anything
		FHitResult hitObject;
		FCollisionQueryParams collisionParams;
		if (GetWorld()->LineTraceSingleByChannel(hitObject, startFire, endFire, ECC_PhysicsBody, collisionParams))
		{
			// Checks if the hit object is an interactable object
			AInteractableObject* hitInteractable = Cast<AInteractableObject>(hitObject.GetActor());
			if (hitInteractable != nullptr)
			{
				ServerInteract(hitInteractable);
			}
		}
	}
}

void ANewBloodCharacter::ServerInteract_Implementation(AInteractableObject* hitInteractable)
{
	UE_LOG(LogTemp, Warning, TEXT("Player Is Looking At: %s"), *hitInteractable->GetName());

	// Interacts with that object
	hitInteractable->OnInteract(this);
}

bool ANewBloodCharacter::ServerInteract_Validate(AInteractableObject* hitInteractable)
{
	return true;
}