// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableObject.h"
#include "PickupableObject.generated.h"

/**
 * 
 */
UCLASS()
class NEWBLOOD_API APickupableObject : public AInteractableObject
{
	GENERATED_BODY()
	

public:
	APickupableObject();

	// Inherited Interaction Behaviour
	// Handling Multiplayer Behaviour - Engagement
	virtual void ClientEngageBehaviour(APawn* interactingPlayer) override;
	virtual void ServerEngageBehaviour(APawn* interactingPlayer) override;
	// Handling Multiplayer Behaviour - Disengagement
	virtual void ClientDisengageBehaviour(APawn* interactingPlayer) override;
	virtual void ServerDisengageBehaviour(APawn* interactingPlayer) override;

	void AddToPlayerInventory();

protected:
	// Inventory Details
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup Details")
		FString inventoryName;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup Details")
		UTexture2D* inventoryIcon;

private:
	// Pickup UI
	class UWeaponDetailsWidget* pickupWidgetInstance;
	UPROPERTY(EditAnywhere, Category = "Widgets")
		TSubclassOf<UWeaponDetailsWidget> pickupWidgetBP;
};