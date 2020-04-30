// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableObject.h"
#include "NewBloodCharacter.h"
#include "Engine/Engine.h"

// Sets default values
AInteractableObject::AInteractableObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	canInteract = true;
	bReplicates = true;
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
	//this->SetOwner(interactingPlayer);
	if (Role == ROLE_Authority)
	{
		ServerSetCanInteract(false);
	}
	else
	{
		ClientSetCanInteract(false);
	}
}

void AInteractableObject::OnDisengage(APawn* interactingPlayer)
{
	targetPlayer = nullptr;

	// RCP Handling
	if (Role == ROLE_Authority)
	{
		ServerSetCanInteract(true);
	}
	else
	{
		ClientSetCanInteract(true);
	}
	//this->SetOwner(nullptr);
}

bool AInteractableObject::GetCanInteract()
{
	return this->canInteract;
}


/*
====================================================================================================
SERVER ONLY - Interaction Details
====================================================================================================
*/
void AInteractableObject::ServerSetCanInteract_Implementation(bool newCanInteract)
{
	canInteract = newCanInteract;
}

bool AInteractableObject::ServerSetCanInteract_Validate(bool newCanInteract)
{
	return true;
}


/*
====================================================================================================
CLIENT ONLY - Interaction Details
====================================================================================================
*/
void AInteractableObject::ClientSetCanInteract_Implementation(bool newCanInteract)
{
	ServerSetCanInteract(newCanInteract);
}

bool AInteractableObject::ClientSetCanInteract_Validate(bool newCanInteract)
{
	return true;
}