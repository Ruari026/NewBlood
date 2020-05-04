// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableDetective.h"

#include "Components/SkeletalMeshComponent.h"

#include "NewBloodCharacter.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"

#include "DetectiveDetailsWidget.h"

// Sets default values
AInteractableDetective::AInteractableDetective()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->detectiveMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
}

void AInteractableDetective::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	DOREPLIFETIME(AInteractableDetective, canInteract);
	DOREPLIFETIME(AInteractableDetective, murderWeapon);
	DOREPLIFETIME(AInteractableDetective, pickedMurderer);
	DOREPLIFETIME(AInteractableDetective, allCharacters);
}

// Called when the game starts or when spawned
void AInteractableDetective::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AInteractableDetective::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


/*
====================================================================================================
Interaction Behaviour - Engagement
====================================================================================================
*/
void AInteractableDetective::ClientEngageBehaviour(APawn* interactingPlayer)
{
	Super::ClientEngageBehaviour(interactingPlayer);

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
			detailsWidgetInstance = CreateWidget<UDetectiveDetailsWidget>(GetWorld(), detailsWidgetBP);
			if (detailsWidgetInstance != nullptr)
			{
				// Setting the UI to show this specific weapon's information
				detailsWidgetInstance->targetDetective = this;

				// Showing UI to player
				detailsWidgetInstance->AddToViewport();
			}
		}
	}
}

void AInteractableDetective::ServerEngageBehaviour(APawn* interactingPlayer)
{
	Super::ServerEngageBehaviour(interactingPlayer);
}


/*
====================================================================================================
Interaction Behaviour - Disengagement
====================================================================================================
*/
void AInteractableDetective::ClientDisengageBehaviour(APawn* interactingPlayer)
{
	Super::ClientDisengageBehaviour(interactingPlayer);

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

void AInteractableDetective::ServerDisengageBehaviour(APawn* interactingPlayer)
{
	Super::ServerDisengageBehaviour(interactingPlayer);
}