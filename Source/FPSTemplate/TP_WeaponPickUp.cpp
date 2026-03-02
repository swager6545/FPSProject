// Fill out your copyright notice in the Description page of Project Settings.


#include "TP_WeaponPickUp.h"

#include "TP_PickUpComponent.h"

// Sets default values
ATP_WeaponPickUp::ATP_WeaponPickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	PickUpComp = FindComponentByClass<UTP_PickUpComponent>();
	
	if (PickUpComp != nullptr)
	{
		WeaponPickUp = FindComponentByClass<UTP_WeaponComponent>();
	}

}

// Called when the game starts or when spawned
void ATP_WeaponPickUp::BeginPlay()
{
	Super::BeginPlay();
	PickUpComp = FindComponentByClass<UTP_PickUpComponent>();
	
	if (PickUpComp != nullptr)
	{
		WeaponPickUp = FindComponentByClass<UTP_WeaponComponent>();
		if (WeaponPickUp != nullptr)
		{
			PickUpComp->OnPickUp.AddDynamic(this, &ATP_WeaponPickUp::AttachWeapon);
		}
	}
	
}

void ATP_WeaponPickUp::AttachWeapon(AFPSTemplateCharacter* PickUpCharacter)
{
	//check if the WeaponPickUp and PickUpCharacter
	if (WeaponPickUp != nullptr)
	{
		if (PickUpCharacter != nullptr)
		{
			//attach the WeaponPickUp to the character
			WeaponPickUp->AttachWeapon(PickUpCharacter);
		}
	}
}

