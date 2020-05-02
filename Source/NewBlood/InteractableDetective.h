// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableObject.h"
#include "InteractableDetective.generated.h"

/**
 * 
 */
UCLASS()
class NEWBLOOD_API AInteractableDetective : public AInteractableObject
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AInteractableDetective();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Inherited Interaction Behaviour
	// Handling Multiplayer Behaviour - Engagement
	virtual void ClientEngageBehaviour(APawn* interactingPlayer) override;
	virtual void ServerEngageBehaviour(APawn* interactingPlayer) override;
	// Handling Multiplayer Behaviour - Disengagement
	virtual void ClientDisengageBehaviour(APawn* interactingPlayer) override;
	virtual void ServerDisengageBehaviour(APawn* interactingPlayer) override;

private:
	UPROPERTY(EditAnywhere)
		class USkeletalMeshComponent* detectiveMesh;

	// Details UI
	class UDetectiveDetailsWidget* detailsWidgetInstance;
	UPROPERTY(EditAnywhere, Category = "Widgets")
		TSubclassOf<UDetectiveDetailsWidget> detailsWidgetBP;
};
