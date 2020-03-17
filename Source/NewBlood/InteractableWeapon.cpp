// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableWeapon.h"

#include "Components/StaticMeshComponent.h"

#include "NewBloodCharacter.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"

#include "WeaponDetailsWidget.h"

// Sets default values
AInteractableWeapon::AInteractableWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->weaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
}

// Called when the game starts or when spawned
void AInteractableWeapon::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AInteractableWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


/*
====================================================================================================
Interaction Behaviour
====================================================================================================
*/
void AInteractableWeapon::OnEngage(APawn* interactingPlayer)
{
	Super::OnEngage(interactingPlayer);

	// Disables Player Movement & Enables UI Interaction
	ANewBloodCharacter* playerCharacter = Cast<ANewBloodCharacter>(interactingPlayer);
	if (playerCharacter != nullptr)
	{
		playerCharacter->SetPlayerControlMode(false);
	}

	// Gets The Interacting Player Controller And Adds UI For Showing The Weapon Details
	APlayerController* playerController = Cast<APlayerController>(interactingPlayer->GetController());
	if (playerController != nullptr)
	{
		if (detailsWidgetBP != nullptr)
		{
			detailsWidgetInstance = CreateWidget<UWeaponDetailsWidget>(GetWorld(), detailsWidgetBP);
			if (detailsWidgetInstance != nullptr)
			{
				// Setting the UI to show this specific weapon's information
				detailsWidgetInstance->targetWeapon = this;
				detailsWidgetInstance->SetWidgetDetails(this->weaponName, this->weaponDamageType);

				// Showing UI to player
				detailsWidgetInstance->AddToViewport();
			}
		}
	}
}

void AInteractableWeapon::OnDisengage(APawn* interactingPlayer)
{
	Super::OnDisengage(interactingPlayer);

	// Removes Weapon Details UI
	if (detailsWidgetInstance != nullptr)
	{
		detailsWidgetInstance->RemoveFromParent();
	}

	// Disables Player Movement & Enables UI Interaction
	ANewBloodCharacter* playerCharacter = Cast<ANewBloodCharacter>(interactingPlayer);
	if (playerCharacter != nullptr)
	{
		playerCharacter->SetPlayerControlMode(true);
	}
}