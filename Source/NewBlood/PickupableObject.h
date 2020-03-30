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
	virtual void OnEngage(APawn* interactingPlayer);
	virtual void OnDisengage(APawn* interactingPlayer);

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