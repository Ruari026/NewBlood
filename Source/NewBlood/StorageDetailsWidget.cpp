// Fill out your copyright notice in the Description page of Project Settings.


#include "StorageDetailsWidget.h"

void UStorageDetailsWidget::CloseDetailsWidget()
{
	if (targetStorage != nullptr)
	{
		targetStorage->OnDisengage(GetOwningPlayerPawn());
	}
}