// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableVictim.h"

#include "Components/SkeletalMeshComponent.h"

#include "NewBloodCharacter.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"

#include "VictimDetailsWidget.h"

// Sets default values
AInteractableVictim::AInteractableVictim()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->victimMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
}


void AInteractableVictim::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	DOREPLIFETIME(AInteractableVictim, canInteract);
	DOREPLIFETIME(AInteractableVictim, victimName);
	DOREPLIFETIME(AInteractableVictim, victimMurderMethod);
}


// Called when the game starts or when spawned
void AInteractableVictim::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AInteractableVictim::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


/*
====================================================================================================
Interaction Behaviour - Engagement
====================================================================================================
*/
void AInteractableVictim::ClientEngageBehaviour(APawn* interactingPlayer)
{
	Super::ClientEngageBehaviour(interactingPlayer);

	UE_LOG(LogTemp, Warning, TEXT("Object Is An Victim Object"));

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
			detailsWidgetInstance = CreateWidget<UVictimDetailsWidget>(GetWorld(), detailsWidgetBP);
			if (detailsWidgetInstance != nullptr)
			{
				// Setting the UI to show this specific weapon's information
				detailsWidgetInstance->targetVictim = this;
				detailsWidgetInstance->SetWidgetDetails(this->victimName, this->victimMurderMethod);

				// Showing UI to player
				detailsWidgetInstance->AddToViewport();
			}
		}
	}
}

void AInteractableVictim::ServerEngageBehaviour(APawn* interactingPlayer)
{
	Super::ServerEngageBehaviour(interactingPlayer);
}



/*
====================================================================================================
Interaction Behaviour - Disengagement
====================================================================================================
*/
void AInteractableVictim::ClientDisengageBehaviour(APawn* interactingPlayer)
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

void AInteractableVictim::ServerDisengageBehaviour(APawn* interactingPlayer)
{
	Super::ServerDisengageBehaviour(interactingPlayer);
}