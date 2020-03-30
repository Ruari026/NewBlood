// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractableWeapon.h"
#include "WeaponDetailsWidget.generated.h"

/**
 * 
 */
UCLASS()
class NEWBLOOD_API UWeaponDetailsWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
		AInteractableWeapon* targetWeapon;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void SetWidgetDetails(const FString& weaponName, const FString& damageType);
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void ShowFurtherDetails();
	UFUNCTION(BlueprintCallable)
		void CloseDetailsWidget();
};