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
bool AInteractableObject::GetCanInteract()
{
	return this->canInteract;
}

void AInteractableObject::OnInteract(AActor* interactingPlayer)
{
	this->canInteract = false;
}

void AInteractableObject::OnDisengage()
{
	this->canInteract = true;
}