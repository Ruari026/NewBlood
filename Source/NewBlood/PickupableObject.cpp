// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupableObject.h"
#include "WeaponDetailsWidget.h"
#include "NewBloodCharacter.h"
#include "PlayerInventory.h"

APickupableObject::APickupableObject()
{

}


/*
====================================================================================================
Interaction Behaviour - Engagement
====================================================================================================
*/
void APickupableObject::ClientEngageBehaviour(APawn* interactingPlayer)
{
	Super::ClientEngageBehaviour(interactingPlayer);

	UE_LOG(LogTemp, Warning, TEXT("Object Is A Pickupable Object"));

	// Gets The Interacting Player Controller And Adds UI For Showing The Weapon Details
	APlayerController* playerController = Cast<APlayerController>(interactingPlayer->GetController());
	if (playerController != nullptr)
	{
		if (pickupWidgetBP != nullptr)
		{
			pickupWidgetInstance = CreateWidget<UWeaponDetailsWidget>(GetWorld(), pickupWidgetBP);
			if (pickupWidgetInstance != nullptr)
			{
				// Showing UI to player
				pickupWidgetInstance->AddToViewport();
			}
		}
	}
}

void APickupableObject::ServerEngageBehaviour(APawn* interactingPlayer)
{
	Super::ServerEngageBehaviour(interactingPlayer);
}


/*
====================================================================================================
Interaction Behaviour - Disengagement
====================================================================================================
*/
void APickupableObject::ClientDisengageBehaviour(APawn* interactingPlayer)
{
	Super::ClientDisengageBehaviour(interactingPlayer);

	// Removes Weapon Details UI
	if (pickupWidgetInstance != nullptr)
	{
		pickupWidgetInstance->RemoveFromParent();
	}
}

void APickupableObject::ServerDisengageBehaviour(APawn* interactingPlayer)
{
	Super::ServerDisengageBehaviour(interactingPlayer);
}


/*
====================================================================================================
Pickup Behaviour
====================================================================================================
*/
void APickupableObject::AddToPlayerInventory()
{
	if (targetPlayer != nullptr)
	{
		if (targetPlayer->playerInventory->AddItemToInventory(this))
		{
			this->SetActorScale3D(FVector::ZeroVector);
		}
	}
}