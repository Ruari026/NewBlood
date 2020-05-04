// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInventory.h"

// Sets default values for this component's properties
UPlayerInventory::UPlayerInventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UPlayerInventory::BeginPlay()
{
	Super::BeginPlay();

	// ...
	inventoryItems.SetNum(inventorySize);
	for (int i = 0; i < inventorySize; i++)
	{
		inventoryItems[i] = nullptr;
	}
}


// Called every frame
void UPlayerInventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


/*
====================================================================================================
Checking Inventory Space
====================================================================================================
*/
bool UPlayerInventory::InventoryHasSpace()
{
	bool emptySpot = false;
	for (int i = 0; i < inventoryItems.Num(); i++)
	{
		if (inventoryItems[i] == nullptr)
		{
			emptySpot = true;
		}
	}

	return emptySpot;
}

int UPlayerInventory::GetNumberOfFreeSpaces()
{
	int emptySpaces = 0;
	for (int i = 0; i < inventoryItems.Num(); i++)
	{
		if (inventoryItems[i] == nullptr)
		{
			emptySpaces++;
		}
	}

	return emptySpaces;
}


/*
====================================================================================================
Controlling Inventory Selection
====================================================================================================
*/
void UPlayerInventory::ChangeSelectedItem(int newSelection)
{
	if (newSelection >= 0 && newSelection < inventorySize)
	{
		selectedItem = newSelection;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Inventory Cannot Reach The Requested Item At Spot %d"), newSelection);
	}
}

void UPlayerInventory::IncreaseSelectedItem()
{
	selectedItem++;

	if (selectedItem >= inventorySize)
	{
		selectedItem = 0;
	}
}

void UPlayerInventory::DecreaseSelectedItem()
{
	selectedItem--;

	if (selectedItem < 0)
	{
		selectedItem = (inventorySize - 1);
	}
}


/*
====================================================================================================
Controlling Adding & Removing Inventory Items
====================================================================================================
*/
bool UPlayerInventory::AddItemToInventory(APickupableObject* itemToAdd)
{
	// If there is room for the new item
	if (this->InventoryHasSpace())
	{
		for (int i = 0; i < inventoryItems.Num(); i++)
		{
			if (inventoryItems[i] == nullptr)
			{
				inventoryItems[i] = itemToAdd;
				return true;
			}
		}

		// Error Handling
		UE_LOG(LogTemp, Warning, TEXT("ERROR: Item Failed To Be Added To Inventory"));
		return false;
	}
	// The Inventory is full
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("NOTE: No Room In Inventory"));
		return false;
	}
}

void UPlayerInventory::RemoveItemFromInventory(int slotToRemoveFrom)
{
	if (slotToRemoveFrom >= 0 && slotToRemoveFrom < inventorySize)
	{
		inventoryItems[slotToRemoveFrom] = nullptr;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Inventory Cannot Reach The Requested Item At Spot %d"), slotToRemoveFrom);
	}
}


/*
====================================================================================================
Getters
====================================================================================================
*/
int UPlayerInventory::GetInventorySize()
{
	return inventorySize;
}

int UPlayerInventory::GetSelectedItemNumber()
{
	return selectedItem;
}

APickupableObject* UPlayerInventory::GetSelectedItemObject()
{
	return inventoryItems[selectedItem];
}

TArray<APickupableObject*> UPlayerInventory::GetInventoryItems()
{
	return inventoryItems;
}