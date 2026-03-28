// Fill out your copyright notice in the Description page of Project Settings.

#include "TP_ItemPickUp.h"
#include "ItemDefinition.h"
#include "ItemData.h"

// Sets default values
ATP_ItemPickUp::ATP_ItemPickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	PickupMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	check(PickupMeshComponent != nullptr);
	SetRootComponent(PickupMeshComponent);
	
	//allow the player to pickup items
	PickUpComp = CreateDefaultSubobject<UTP_PickUpComponent>(TEXT("PickupComponent"));
	check(PickUpComp != nullptr);
	PickUpComp->SetupAttachment(PickupMeshComponent);
	PickUpComp->SetSphereRadius(32.f);
	PickUpComp->SetGenerateOverlapEvents(true);
	
	//to make sure the item won't have any physics once the player touches it
	PickUpComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	PickUpComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	PickUpComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

}

// Called when the game starts or when spawned
void ATP_ItemPickUp::BeginPlay()
{
	Super::BeginPlay();
	
	InitializePickup();
	
	PickUpComp->OnComponentBeginOverlap.RemoveAll(this);
	
	PickUpComp->OnComponentBeginOverlap.AddDynamic(this, &ATP_ItemPickUp::OnSphereBeginOverlap);
}

void ATP_ItemPickUp::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Testing Pickup Collision"));
	
	AFPSTemplateCharacter* Character = Cast<AFPSTemplateCharacter>(OtherActor);
	
	
	if (Character != nullptr)
	{
		Character->GiveItem(ReferenceItem);
		
		//set the pickup as invisible once the player touches it
		PickupMeshComponent->SetVisibility(false);
		PickupMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		PickUpComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		
		PickUpComp->OnPickUp.Broadcast(Character);
	}
	
	//if the pickup should respawn, wait for the respawn time before 
	//calling InitializePickup() to respawn it
	if (bShouldRespawn)
	{
		GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &ATP_ItemPickUp::InitializePickup, RespawnTime, false);
	}
}

//Update the pickup whenever the property changed
void ATP_ItemPickUp::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	
	//if property changed, get the name of the changed property otherwise use none
	const FName ChangedPropertyName = PropertyChangedEvent.Property
	? PropertyChangedEvent.Property->GetFName()
	: NAME_None;
	
	//check if the changed property is the affected item in this class
	if (ChangedPropertyName == GET_MEMBER_NAME_CHECKED(ATP_ItemPickUp, PickupItemID) || 
		ChangedPropertyName == GET_MEMBER_NAME_CHECKED(ATP_ItemPickUp, PickupDataTable))
	{
		InitializePickup();
	}
}

// Called every frame
void ATP_ItemPickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATP_ItemPickUp::InitializePickup()
{
	//verify if the assets exist before loading
	const FSoftObjectPath TablePath = PickupDataTable.ToSoftObjectPath();
	
	if (!TablePath.IsNull() && !PickupItemID.IsNone())
	{
		//loads the datatable if it exists
		UDataTable* LoadedDataTable = PickupDataTable.IsValid()
		? PickupDataTable.Get()
		: PickupDataTable.LoadSynchronous();
		
		//only continue if a valid datatable has been loaded
		if (!LoadedDataTable)
		{
			return;
		}
		
		//use the pickup ID to check the corresponding table row
		const FItemData* ItemDataRow = LoadedDataTable->FindRow<FItemData>(PickupItemID, PickupItemID.ToString());
		
		//only continue if the row was found
		if (!ItemDataRow)
		{
			return;
		}
		
		//loads the data asset if it exists
		UItemDefinition* TempItemDefinition = ItemDataRow->ItemBase.IsValid()
		? ItemDataRow->ItemBase.Get()
		: ItemDataRow->ItemBase.LoadSynchronous();
		
		//only continue if the data asset was found
		if (!TempItemDefinition)
		{
			return;
		}
		
		//build the item definition object based from the data table row
		ReferenceItem = TempItemDefinition->CreateItemCopy(this);
		
		//loads static mesh if it exists
		UStaticMesh* LoadedMesh = TempItemDefinition->WorldMesh.IsValid()
		? TempItemDefinition->WorldMesh.Get()
		: TempItemDefinition->WorldMesh.LoadSynchronous();
		
		//check if the mesh is set to load the asset before using it
		if (LoadedMesh)
		{
			PickupMeshComponent->SetStaticMesh(LoadedMesh);
		}
		
		PickupMeshComponent->SetVisibility(true);
		
		PickUpComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
}

