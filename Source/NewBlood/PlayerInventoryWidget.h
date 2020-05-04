// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerInventory.h"
#include "ItemSlotWidget.h"
#include "PlayerInventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class NEWBLOOD_API UPlayerInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly)
		UPlayerInventory* targetInventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<UItemSlotWidget*> inventorySlots;
};
