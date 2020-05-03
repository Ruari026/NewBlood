// Fill out your copyright notice in the Description page of Project Settings.


#include "DetectiveDetailsWidget.h"
#include "NewBloodCharacter.h"

void UDetectiveDetailsWidget::CloseDetailsWidget()
{
	if (targetDetective != nullptr)
	{
		targetDetective->OnDisengageObject(targetDetective->targetPlayer);
	}
}