// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"
#include "Components/BoxComponent.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//create default components
	DoorFrame = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorFrameMesh"));
	Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	DoorTimelineComp = CreateDefaultSubobject<UTimelineComponent>(TEXT("DoorTimelineComp"));
	DoorProxVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("DoorProxVolume"));
	
	//setup the door attachments
	DoorFrame->SetupAttachment(RootComponent);
	Door->AttachToComponent(DoorFrame, FAttachmentTransformRules::KeepRelativeTransform);
	DoorProxVolume->AttachToComponent(DoorFrame, FAttachmentTransformRules::KeepRelativeTransform);
}

void ADoor::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	DoorTimelineComp->Play();
}

void ADoor::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	DoorTimelineComp->Reverse();
}

void ADoor::OpenDoor()
{
	//bind float track to the update timeline function
	UpdateFunctionFloat.BindDynamic(this, &ADoor::UpdateTimelineComp);
	
	//if there is a float curve, it will bind the graph to the update function
	if (DoorTimelineFloatCurve)
	{
		DoorTimelineComp->AddInterpFloat(DoorTimelineFloatCurve, UpdateFunctionFloat);
	}
	
	//bind the proximity box component to the overlap functions
	DoorProxVolume->OnComponentBeginOverlap.AddDynamic(this, &ADoor::OnOverlapBegin);
	DoorProxVolume->OnComponentEndOverlap.AddDynamic(this, &ADoor::OnOverlapEnd);
}

void ADoor::UpdateTimelineComp(float Output)
{
	//create and set the doors new relative location based on the output from the timeline curve
	FRotator DoorNewRotation = FRotator(0.f, Output, 0.f);
	Door->SetRelativeRotation(DoorNewRotation);
}

