// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UnrealNetwork.h"
#include "InteractableObject.generated.h"

UCLASS()
class NEWBLOOD_API AInteractableObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractableObject();
	void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const;

	// Interaction Handling
	bool GetCanInteract();

	UPROPERTY(BlueprintReadWrite)
		class ANewBloodCharacter* targetPlayer;

	// Handling Multiplayer Behaviour - Engagement
	virtual void ClientEngageBehaviour(APawn* interactingPlayer);
	virtual void ServerEngageBehaviour(APawn* interactingPlayer);


	// Handling Multiplayer Behaviour - Disengagement
	void OnDisengageObject(APawn* interactingPlayer);
	UFUNCTION()
		virtual void ClientDisengageBehaviour(APawn* interactingPlayer);
	UFUNCTION(Server, Reliable, WithValidation)
		virtual void ServerDisengageBehaviour(APawn* interactingPlayer);

	// RPC Testing
	UFUNCTION(NetMulticast, Reliable, WithValidation)
		void SetObjectOwner(AActor* newOwner);
	// RPC Testing
	UFUNCTION(Server, Reliable, WithValidation)
		void ObjectOwnerTest();

protected:
	// Preventing Multiple players from interacting with the same item
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
		bool canInteract;
};
