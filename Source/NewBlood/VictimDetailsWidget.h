// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractableVictim.h"
#include "VictimDetailsWidget.generated.h"

/**
 * 
 */
UCLASS()
class NEWBLOOD_API UVictimDetailsWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite)
		AInteractableVictim* targetVictim;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void SetWidgetDetails(const FString& victimName, const FString& victimMurderMethod);
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void ShowFurtherDetails();
	UFUNCTION(BlueprintCallable)
		void CloseDetailsWidget();
};
