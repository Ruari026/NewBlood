// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableObject.h"

// Sets default values
AInteractableObject::AInteractableObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	canInteract = true;
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
	if (Role == ROLE_Authority)
	{
		ServerSetCanInteract(true);
	}
	else
	{
		ClientSetCanInteract(true);
	}
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
	canInteract = newCanInteract;
}

bool AInteractableObject::ClientSetCanInteract_Validate(bool newCanInteract)
{
	return true;
}