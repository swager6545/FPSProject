// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components\TimelineComponent.h"
#include "Door.generated.h"

UCLASS()
class FPSTEMPLATE_API ADoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();
	
	UPROPERTY(EditAnywhere)
	UCurveFloat* DoorTimelineFloatCurve;
	
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* DoorFrame;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Door;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UTimelineComponent* DoorTimelineComp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UBoxComponent* DoorProxVolume;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	FOnTimelineFloat UpdateFunctionFloat;
	
	UFUNCTION()
	void UpdateTimelineComp(float Output);

};
