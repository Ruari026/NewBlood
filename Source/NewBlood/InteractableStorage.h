// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickupableObject.h"
#include "InteractableStorage.generated.h"

/**
 * 
 */
UCLASS()
class NEWBLOOD_API AInteractableStorage : public AInteractableObject
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AInteractableStorage();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Inherited Interaction Behaviour
	virtual void OnEngage(APawn* interactingPlayer) override;
	virtual void OnDisengage(APawn* interactingPlayer) override;

	UPROPERTY(BlueprintReadWrite)
		APickupableObject* storedObject;

private:
	// Details UI
	class UStorageDetailsWidget* detailsWidgetInstance;
	UPROPERTY(EditAnywhere, Category = "Widgets")
		TSubclassOf<UStorageDetailsWidget> detailsWidgetBP;
};