// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableObject.generated.h"

UCLASS()
class NEWBLOOD_API AInteractableObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractableObject();

	void OnInteract(APawn* interactingPlayer);

	virtual void OnEngage(APawn* interactingPlayer);
	virtual void OnDisengage(APawn* interactingPlayer);

protected:
	bool canInteract;
};
