// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PickupableObject.h"
#include "ItemSlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class NEWBLOOD_API UItemSlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void UpdateSlotVisual();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void SetSelectedState(bool isSelected);

	UPROPERTY(BlueprintReadWrite)
		APickupableObject* slotObject;
};
