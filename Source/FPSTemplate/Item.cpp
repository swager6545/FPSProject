// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//create default objects for items
	Model = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item Model"));
	RootComponent = Model;
	Text = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Item Title"));
	Text->SetupAttachment(Model);
	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Item Collider"));
	Collider->SetupAttachment(Model);
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	UpdateTitle();
	
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UWorld* World = GetWorld();
	if (World)
	{
		AController* Controller = World->GetFirstPlayerController();
		if (Controller)
		{
			AActor* PlayerPawn = Controller->GetPawn();
			if (PlayerPawn)
			{
				FRotator LookAt = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), 
					PlayerPawn->GetActorLocation());
				Text->SetWorldRotation(LookAt);
			}
		}
	}

}

void AItem::UpdateTitle()
{
	if (Text)
	{
		Text->SetText(FText::FromString(ItemDetails.Name));
		Text->SetTextRenderColor(RarityColor[ItemDetails.Rarity]);
	}
}

