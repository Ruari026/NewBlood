// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PickupableObject.h"
#include "PlayerInventory.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NEWBLOOD_API UPlayerInventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerInventory();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Checking Inventory Space
	UFUNCTION(BlueprintCallable)
		bool InventoryHasSpace();
	UFUNCTION(BlueprintCallable)
		int GetNumberOfFreeSpaces();

	// Controlling Selected Item
	void ChangeSelectedItem(int newSelection);
	void IncreaseSelectedItem();
	void DecreaseSelectedItem();

	// Controlling Adding & Removing Items
	UFUNCTION(BlueprintCallable)
		bool AddItemToInventory(APickupableObject* itemToAdd);
	UFUNCTION(BlueprintCallable)
		void RemoveItemFromInventory(int slotToRemoveFrom);

	// Getters
	UFUNCTION(BlueprintCallable)
		int GetInventorySize();
	UFUNCTION(BlueprintCallable)
		int GetSelectedItemNumber();
	UFUNCTION(BlueprintCallable)
		APickupableObject* GetSelectedItemObject();
	UFUNCTION(BlueprintCallable)
		TArray<APickupableObject*> GetInventoryItems();

private:
	UPROPERTY(EditAnywhere)
		int inventorySize;
	int selectedItem;
	UPROPERTY(EditAnywhere)
	TArray<APickupableObject*> inventoryItems;
};
