// Fill out your copyright notice in the Description page of Project Settings.


#include "TP_WeaponPickUp.h"
#include "TP_PickUpComponent.h"

void ATP_WeaponPickUp::BeginPlay()
{
	Super::BeginPlay();
	
	PickUpComp = FindComponentByClass<UTP_PickUpComponent>();
	
	if (PickUpComp != nullptr)
	{
		WeaponPickUp = FindComponentByClass<UTP_WeaponComponent>();
	}
}


