// Fill out your copyright notice in the Description page of Project Settings.


#include "VictimDetailsWidget.h"


void UVictimDetailsWidget::CloseDetailsWidget()
{
	if (targetVictim != nullptr)
	{
		targetVictim->OnDisengage(GetOwningPlayerPawn());
	}
}