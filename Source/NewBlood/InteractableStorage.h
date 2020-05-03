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
	void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
		APickupableObject* storedObject;
	UFUNCTION(BlueprintCallable)
		void AddObjectToStorage(APickupableObject* objectToStore);
	UFUNCTION(Server, Reliable, WithValidation)
		void ServerStore(APickupableObject* objectToStore);

private:
	// Details UI
	class UStorageDetailsWidget* detailsWidgetInstance;
	UPROPERTY(EditAnywhere, Category = "Widgets")
		TSubclassOf<UStorageDetailsWidget> detailsWidgetBP;
};