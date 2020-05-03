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

	ObjectOwnerTest();
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
void AInteractableObject::OnDisengageObject(APawn* interactingPlayer)
{
	ClientDisengageBehaviour(interactingPlayer);
	ServerDisengageBehaviour(interactingPlayer);
}

void AInteractableObject::ClientDisengageBehaviour(APawn* interactingPlayer)
{
	UE_LOG(LogTemp, Warning, TEXT("Client: Disengage"));

	targetPlayer = nullptr;
}

void AInteractableObject::ServerDisengageBehaviour_Implementation(APawn* interactingPlayer)
{
	UE_LOG(LogTemp, Warning, TEXT("Server: Disengage"));

	this->canInteract = true;
}

bool AInteractableObject::ServerDisengageBehaviour_Validate(APawn* interactingPlayer)
{
	return true;
}


/*
====================================================================================================
Testing
====================================================================================================
*/
void AInteractableObject::SetObjectOwner_Implementation(AActor* newOwner)
{
	this->SetOwner(newOwner);
}

bool AInteractableObject::SetObjectOwner_Validate(AActor* newOwner)
{
	return true;
}

void AInteractableObject::ObjectOwnerTest_Implementation()
{
	this->canInteract = false;
}

bool AInteractableObject::ObjectOwnerTest_Validate()
{
	return true;
}