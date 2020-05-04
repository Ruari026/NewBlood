// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Blueprint/UserWidget.h"
#include "NewBloodCharacter.generated.h"

class UInputComponent;

UCLASS(config=Game)
class ANewBloodCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	class USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;

public:
	ANewBloodCharacter();

protected:
	virtual void BeginPlay();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

protected:

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);
	
protected:
	UPROPERTY(EditAnywhere)
		float interactionStartDistance;
	UPROPERTY(EditAnywhere)
		float interactionEndDistance;
	bool canInteract;
	void TryInteract();

	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

public:
	/** Returns Mesh1P subobject **/
	FORCEINLINE class USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	// Crosshairs
	class UPlayerCrosshairsWidget* crosshairsWidgetInstance;
	UPROPERTY(EditAnywhere, Category = "Widgets")
		TSubclassOf<UPlayerCrosshairsWidget> crosshairsWidgetBP;
	void SetPlayerControlMode(bool canMove);

	// Player Character
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		 FString characterName;
	UFUNCTION(BlueprintCallable, Server, Reliable, WithValidation)
		void SetCharacterName(const FString& newName);
	UFUNCTION(NetMulticast, Reliable, WithValidation)
		void ReplicateCharacterName(const FString& newName);
	UFUNCTION(BlueprintCallable, NetMulticast, Reliable, WithValidation)
		void ShowCharacterRole(bool isMurderer);

	// Interaction - Engagement
	AInteractableObject* interactingObject;
	UFUNCTION(Server, Reliable, WithValidation)
		void SetInteractingObject(AInteractableObject* interactingObject);
	UFUNCTION()
		void EngageObject(AInteractableObject* objectToInteract);
	UFUNCTION()
		void ClientEngageObject();
	UFUNCTION(Server, Reliable, WithValidation)
		void ServerEngageObject();

	// RPC Testing
	UFUNCTION(Server, Reliable, WithValidation)
		void ChangeObjectOwner();

	// Inventory Management
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UPlayerInventory* playerInventory;
	class UPlayerInventoryWidget* inventoryWidgetInstance;
	UPROPERTY(EditAnywhere, Category = "Widgets")
		TSubclassOf<UPlayerInventoryWidget> inventoryWidgetBP;
	UPROPERTY(EditAnywhere, Category = "Widgets")
		TSubclassOf<UUserWidget> innocentRoleWidgetBP;
	UPROPERTY(EditAnywhere, Category = "Widgets")
		TSubclassOf<UUserWidget> murdererRoleWidgetBP;
};