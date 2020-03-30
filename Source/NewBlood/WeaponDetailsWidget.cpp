// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponDetailsWidget.h"


void UWeaponDetailsWidget::CloseDetailsWidget()
{
	if (targetWeapon != nullptr)
	{
		targetWeapon->OnDisengage(GetOwningPlayerPawn());
	}
}


/*
====================================================================================================
Player Actions
====================================================================================================
*/
void UWeaponDetailsWidget::PickupWeapon()
{
	targetWeapon->AddToPlayerInventory();
	this->CloseDetailsWidget();
}

void UWeaponDetailsWidget::RevealFingerprints()
{

}

void UWeaponDetailsWidget::WipeBlood()
{

}