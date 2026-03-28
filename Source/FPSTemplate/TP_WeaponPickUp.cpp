// Fill out your copyright notice in the Description page of Project Settings.


#include "TP_WeaponPickUp.h"

#include "EnhancedInputComponent.h"
#include "TP_PickUpComponent.h"

// Sets default values
ATP_WeaponPickUp::ATP_WeaponPickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	PickUpComp = FindComponentByClass<UTP_PickUpComponent>();
	
	if (PickUpComp != nullptr)
	{
		WeaponPickUp = FindComponentByClass<UTP_WeaponComponent>();
	}
}


