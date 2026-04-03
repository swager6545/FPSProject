// Fill out your copyright notice in the Description page of Project Settings.


#include "ConsumableBase.h"

#include "TP_PickUpComponent.h"

// Sets default values
AConsumableBase::AConsumableBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AConsumableBase::BeginPlay()
{
	Super::BeginPlay();
	
	PickUpComp = FindComponentByClass<UTP_PickUpComponent>();
	
	if (PickUpComp != nullptr)
	{
		ConsumableMesh = FindComponentByClass<UStaticMeshComponent>();
	}
	
}

// Called every frame
void AConsumableBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AConsumableBase::Consume()
{
	//Will be overridden by classes that inherited from this one
}

