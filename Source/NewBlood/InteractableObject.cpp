// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableObject.h"
#include "NewBloodCharacter.h"
#include "UnrealNetwork.h"

// Sets default values
AInteractableObject::AInteractableObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	canInteract = true;
	bReplicates = true;
}

void AInteractableObject::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AInteractableObject, canInteract);
}


/*
====================================================================================================
Interaction Details
====================================================================================================
*/
void AInteractableObject::OnInteract(APawn* interactingPlayer)
{
	if (canInteract)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Is Interacting With: %s"), *this->GetName());
		this->OnEngage(interactingPlayer);
	}
}

void AInteractableObject::OnEngage(APawn* interactingPlayer)
{
	UE_LOG(LogTemp, Warning, TEXT("Object Is An Interactable Object"));

	ANewBloodCharacter* playerCharacter = Cast<ANewBloodCharacter>(interactingPlayer);
	if (playerCharacter != nullptr)
	{
		targetPlayer = playerCharacter;
	}

	// RCP Handling
	canInteract = false;
}

void AInteractableObject::OnDisengage(APawn* interactingPlayer)
{
	targetPlayer = nullptr;

	// RCP Handling
	canInteract = true;
}

bool AInteractableObject::GetCanInteract()
{
	return this->canInteract;
}

void AInteractableObject::ServerInteract_Implementation(APawn* interactingPlayer)
{
	if (canInteract)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Is Interacting With: %s"), *this->GetName());
		this->OnEngage(interactingPlayer);
	}
}

bool AInteractableObject::ServerInteract_Validate(APawn* interactingPlayer)
{
	return true;
}