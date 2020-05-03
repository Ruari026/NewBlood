// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponDetailsWidget.h"
#include "NewBloodCharacter.h"

void UWeaponDetailsWidget::CloseDetailsWidget()
{
	if (targetWeapon != nullptr)
	{
		targetWeapon->OnDisengageObject(targetWeapon->targetPlayer);
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