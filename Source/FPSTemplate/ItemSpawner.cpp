// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSpawner.h"

// Sets default values
AItemSpawner::AItemSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void AItemSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<FItemData*> ItemList;
	
	FItemData NewItemData;
	
	ItemTable->GetAllRows("", ItemList);
	
	for (int i = 0; i < ItemList.Num(); i++)
	{
		//This will get the current item from the item list and transfer it to the new item list
		NewItemData = *ItemList[i];
		
		FVector SpawnLocation = GetActorLocation() + FVector(50 * i, 0, 0);
		FRotator SpawnRotation = GetActorRotation();
		
		AItem* NewItem = GetWorld()->SpawnActor<AItem>(BaseItem, SpawnLocation, SpawnRotation);
		
		if (NewItem)
		{
			NewItem->ItemDetails = NewItemData;
			NewItem->UpdateTitle();
		}
	}
	
}

// Called every frame
void AItemSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

