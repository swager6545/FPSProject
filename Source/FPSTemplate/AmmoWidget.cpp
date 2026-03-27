// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoWidget.h"

#include "LocalizationDescriptor.h"
#include "Components/TextBlock.h"

void UAmmoWidget::OnAmmoChanged(int32 NewMagAmmo, int32 NewCurrentAmmo)
{
	if (TargetWeaponComponent != nullptr)
	{
		NewMagAmmo = TargetWeaponComponent->MagAmmo;
		NewCurrentAmmo = TargetWeaponComponent->Ammo;
		if (AmmoTextBlock)
		{
			//change the text to show the amount of ammo the player has
			AmmoTextBlock->SetText(FText::Format(FText::FromString("{0}/{1}"), NewMagAmmo, NewCurrentAmmo));
		}
	}
}

void UAmmoWidget::SetTargetWeaponComponent(UTP_WeaponComponent* NewWeaponComponent)
{
	//check if the target weapon component is the new weapon component
	if (TargetWeaponComponent == NewWeaponComponent)
	{
		return;
	}
	
	if (TargetWeaponComponent.IsValid())
	{
		TargetWeaponComponent->OnAmmoChanged.RemoveDynamic(this, &UAmmoWidget::OnAmmoChanged);
	}
	
	TargetWeaponComponent = NewWeaponComponent;
	
	if (TargetWeaponComponent.IsValid())
	{
		TargetWeaponComponent->OnAmmoChanged.AddDynamic(this, &UAmmoWidget::OnAmmoChanged);
	}
}
