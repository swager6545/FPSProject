// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponPickUp.h"
#include "PickUpComponent.h"

void AWeaponPickUp::BeginPlay()
{
	Super::BeginPlay();
	
	PickUpComp = FindComponentByClass<UPickUpComponent>();
	
	if (PickUpComp != nullptr)
	{
		WeaponPickUp = FindComponentByClass<UWeaponComponent>();
	}
}


