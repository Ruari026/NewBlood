// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableObject.h"
#include "NewBloodCharacter.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"

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
	DOREPLIFETIME(AInteractableObject, canInteract);
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


/*
====================================================================================================
On Interaction Details
====================================================================================================
*/
void AInteractableObject::ClientEngageBehaviour(APawn* interactingPlayer)
{
	UE_LOG(LogTemp, Warning, TEXT("Client: Engage"));

	ANewBloodCharacter* playerCharacter = Cast<ANewBloodCharacter>(interactingPlayer);
	if (playerCharacter != nullptr)
	{
		targetPlayer = playerCharacter;
	}
}

void AInteractableObject::ServerEngageBehaviour(APawn* interactingPlayer)
{
	UE_LOG(LogTemp, Warning, TEXT("Server: Engage"));

	this->canInteract = false;
}


/*
====================================================================================================
On Disengage Details
====================================================================================================
*/
void AInteractableObject::ClientDisengageBehaviour(APawn* interactingPlayer)
{
	UE_LOG(LogTemp, Warning, TEXT("Client: Disengage"));

	targetPlayer = nullptr;
}

void AInteractableObject::ServerDisengageBehaviour(APawn* interactingPlayer)
{
	UE_LOG(LogTemp, Warning, TEXT("Server: Disengage"));

	this->canInteract = true;
}