// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableStorage.h"
#include "NewBloodCharacter.h"
#include "PlayerInventory.h"
#include "StorageDetailsWidget.h"

AInteractableStorage::AInteractableStorage()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AInteractableStorage::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AInteractableStorage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AInteractableStorage::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	DOREPLIFETIME(AInteractableStorage, canInteract);
	DOREPLIFETIME(AInteractableStorage, storedObject);
}


/*
====================================================================================================
Interaction Behaviour - Engagement
====================================================================================================
*/
void AInteractableStorage::ClientEngageBehaviour(APawn* interactingPlayer)
{
	Super::ClientEngageBehaviour(interactingPlayer);

	UE_LOG(LogTemp, Warning, TEXT("Object Is An Storage Object"));

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
			detailsWidgetInstance = CreateWidget<UStorageDetailsWidget>(GetWorld(), detailsWidgetBP);
			if (detailsWidgetInstance != nullptr)
			{
				// Setting the UI to show this specific weapon's information
				detailsWidgetInstance->targetStorage = this;
				detailsWidgetInstance->HandleActionPossibilities(playerCharacter);

				// Showing UI to player
				detailsWidgetInstance->AddToViewport();
			}
		}
	}
}

void AInteractableStorage::ServerEngageBehaviour(APawn* interactingPlayer)
{
	Super::ServerEngageBehaviour(interactingPlayer);
}



/*
====================================================================================================
Interaction Behaviour - Disengagement
====================================================================================================
*/
void AInteractableStorage::ClientDisengageBehaviour(APawn* interactingPlayer)
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

void AInteractableStorage::ServerDisengageBehaviour(APawn* interactingPlayer)
{
	Super::ServerDisengageBehaviour(interactingPlayer);
}


/*
====================================================================================================
Storage
====================================================================================================
*/
void AInteractableStorage::AddObjectToStorage(APickupableObject* objectToStore)
{
	// Storing the object on the server
	ServerStore(objectToStore);
}

void AInteractableStorage::ServerStore_Implementation(APickupableObject* objectToStore)
{
	this->storedObject = objectToStore;
}

bool AInteractableStorage::ServerStore_Validate(APickupableObject* objectToStore)
{
	return true;
}