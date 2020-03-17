// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableObject.h"
#include "InteractableVictim.generated.h"

/**
 * 
 */
UCLASS()
class NEWBLOOD_API AInteractableVictim : public AInteractableObject
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AInteractableVictim();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Inherited Interaction Behaviour
	virtual void OnEngage(APawn* interactingPlayer) override;
	virtual void OnDisengage(APawn* interactingPlayer) override;

private:
	UPROPERTY(EditAnywhere)
		class USkeletalMeshComponent* victimMesh;

	// Weapon Details
	UPROPERTY(EditAnywhere)
		FString victimName;
	UPROPERTY(EditAnywhere)
		FString victimMurderMethod;

	// Weapon Details UI
	class UVictimDetailsWidget* detailsWidgetInstance;
	UPROPERTY(EditAnywhere, Category = "Widgets")
		TSubclassOf<UVictimDetailsWidget> detailsWidgetBP;
};
