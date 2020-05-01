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

	// RCP Handling
	this->ClientEngageBehaviour(interactingPlayer);
	this->ServerEngageBehaviour(interactingPlayer);
}

void AInteractableObject::OnDisengage(APawn* interactingPlayer)
{
	// RCP Handling
	this->ClientDisengageBehaviour(interactingPlayer);
	this->ServerDisengageBehaviour(interactingPlayer);
}

bool AInteractableObject::GetCanInteract()
{
	return this->canInteract;
}


/*
====================================================================================================
On Interaction Details
====================================================================================================
*/
void AInteractableObject::ClientEngageBehaviour(APawn* interactingPlayer)
{
	ANewBloodCharacter* playerCharacter = Cast<ANewBloodCharacter>(interactingPlayer);
	if (playerCharacter != nullptr)
	{
		targetPlayer = playerCharacter;
	}
}

void AInteractableObject::ServerEngageBehaviour_Implementation(APawn* interactingPlayer)
{
	this->canInteract = false;
}

bool AInteractableObject::ServerEngageBehaviour_Validate(APawn* interactingPlayer)
{
	return true;
}


/*
====================================================================================================
On Disengage Details
====================================================================================================
*/
void AInteractableObject::ClientDisengageBehaviour(APawn* interactingPlayer)
{
	targetPlayer = nullptr;
}

void AInteractableObject::ServerDisengageBehaviour_Implementation(APawn* interactingPlayer)
{
	this->canInteract = true;
}

bool AInteractableObject::ServerDisengageBehaviour_Validate(APawn* interactingPlayer)
{
	return true;
}