// Fill out your copyright notice in the Description page of Project Settings.


#include "MurderManager.h"
AMurderManager* AMurderManager::instance = nullptr;

// Sets default values
AMurderManager::AMurderManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Singleton Design Pattern
AMurderManager* AMurderManager::GetInstance()
{
	return instance;
}

// Called when the game starts or when spawned
void AMurderManager::BeginPlay()
{
	Super::BeginPlay();
	
	if (instance == nullptr)
	{
		instance = this;
	}
	else
	{
		Destroy();
	}
}

// Called every frame
void AMurderManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}