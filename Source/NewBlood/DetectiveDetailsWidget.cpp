// Fill out your copyright notice in the Description page of Project Settings.


#include "DetectiveDetailsWidget.h"

void UDetectiveDetailsWidget::CloseDetailsWidget()
{
	if (targetDetective != nullptr)
	{
		targetDetective->OnDisengage(GetOwningPlayerPawn());
	}
}