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
	// Ownership Handling
	AActor* a = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	this->SetOwner(a);
	AActor* b = this->GetOwner();

	// RCP Handling
	this->ClientEngageBehaviour(interactingPlayer);
	this->ServerEngageBehaviour(interactingPlayer);
}

void AInteractableObject::OnDisengage(APawn* interactingPlayer)
{
	// RCP Handling
	this->ClientDisengageBehaviour(interactingPlayer);
	this->ServerDisengageBehaviour(interactingPlayer);

	// Ownership Handling
	//this->SetOwner(nullptr);
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
	UE_LOG(LogTemp, Warning, TEXT("Client: Engage"));

	ANewBloodCharacter* playerCharacter = Cast<ANewBloodCharacter>(interactingPlayer);
	if (playerCharacter != nullptr)
	{
		targetPlayer = playerCharacter;
	}
}

void AInteractableObject::ServerEngageBehaviour_Implementation(APawn* interactingPlayer)
{
	UE_LOG(LogTemp, Warning, TEXT("Server: Engage"));

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