// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemSlotWidget.h"
#include "InteractableStorage.h"
#include "StorageDetailsWidget.generated.h"

/**
 * 
 */
UCLASS()
class NEWBLOOD_API UStorageDetailsWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent)
		void HandleActionPossibilities(ANewBloodCharacter* interactingPlayer);

	UPROPERTY(BlueprintReadOnly)
		AInteractableStorage* targetStorage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UItemSlotWidget* storageSlot;

	UFUNCTION(BlueprintCallable)
		void CloseDetailsWidget();
};
