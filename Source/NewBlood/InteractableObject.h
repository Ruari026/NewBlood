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

	void OnInteract(APawn* interactingPlayer);

	virtual void OnEngage(APawn* interactingPlayer);
	virtual void OnDisengage(APawn* interactingPlayer);

	bool GetCanInteract();

protected:
	UPROPERTY(BlueprintReadWrite)
		class ANewBloodCharacter* targetPlayer;

	// Preventing Multiple players from interacting with the same item
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
		bool canInteract;

	// Handling Multiplayer Behaviour - Interaction
	UFUNCTION()
		virtual void ClientEngageBehaviour(APawn* interactingPlayer);
	UFUNCTION(Server, Reliable, WithValidation)
		void ServerEngageBehaviour(APawn* interactingPlayer);


	// Handling Multiplayer Behaviour - Disengage
	UFUNCTION()
		virtual void ClientDisengageBehaviour(APawn* interactingPlayer);
	UFUNCTION(Server, Reliable, WithValidation)
		void ServerDisengageBehaviour(APawn* interactingPlayer);
};
