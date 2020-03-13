// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableWeapon.h"

#include "Components/StaticMeshComponent.h"

// Sets default values
AInteractableWeapon::AInteractableWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->weaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
}

// Called when the game starts or when spawned
void AInteractableWeapon::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AInteractableWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}