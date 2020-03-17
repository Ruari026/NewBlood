// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponDetailsWidget.h"


void UWeaponDetailsWidget::CloseDetailsWidget()
{
	if (targetWeapon != nullptr)
	{
		targetWeapon->OnDisengage(GetOwningPlayerPawn());
	}
}