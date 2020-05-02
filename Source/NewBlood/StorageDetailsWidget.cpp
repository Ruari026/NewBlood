// Fill out your copyright notice in the Description page of Project Settings.


#include "StorageDetailsWidget.h"
#include "NewBloodCharacter.h"

void UStorageDetailsWidget::CloseDetailsWidget()
{
	if (targetStorage != nullptr)
	{
		targetStorage->targetPlayer->DisengageObject();
	}
}