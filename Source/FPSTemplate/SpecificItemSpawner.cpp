// Fill out your copyright notice in the Description page of Project Settings.


#include "SpecificItemSpawner.h"

// Sets default values
ASpecificItemSpawner::ASpecificItemSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//position the spawner
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));

}

// Called when the game starts or when spawned
void ASpecificItemSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<FItemData> ItemList;
	FItemData NewItemData;
	
	if(SpecificItem.DataTable)
	{
		NewItemData = *SpecificItem.GetRow<FItemData>("");
		
		FVector SpawnLocation = GetActorLocation();
		FRotator SpawnRotation = GetActorRotation();
		AItem* NewItem = GetWorld()->SpawnActor<AItem>(BaseItem, SpawnLocation, SpawnRotation);
		if(NewItem)
		{
			NewItem->ItemDetails = NewItemData;
			NewItem->UpdateTitle();
		}
	}
	
}

// Called every frame
void ASpecificItemSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

