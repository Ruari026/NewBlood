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
	this->canInteract = false;
}

void AInteractableObject::OnDisengage(APawn* interactingPlayer)
{
	this->canInteract = true;
}