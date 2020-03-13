// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableObject.h"
#include "InteractableWeapon.generated.h"

/**
 * 
 */
UCLASS()
class NEWBLOOD_API AInteractableWeapon : public AInteractableObject
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AInteractableWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Inherited Interaction Behaviour
	virtual void OnInteract(AActor* interactingPlayer) override;
	virtual void OnDisengage() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	// Weapon Interaction Behaviour
	class UStaticMeshComponent* weaponMesh;
	TArray<FString> weaponFingerPrints;
};