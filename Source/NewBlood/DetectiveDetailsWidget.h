// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractableDetective.h"
#include "DetectiveDetailsWidget.generated.h"

/**
 * 
 */
UCLASS()
class NEWBLOOD_API UDetectiveDetailsWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite)
		AInteractableDetective* targetDetective;

	UFUNCTION(BlueprintCallable)
		void CloseDetailsWidget();
};
