// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TP_PickUpComponent.h"
#include "Components/StaticMeshComponent.h"
#include "ConsumableBase.generated.h"

UCLASS()
class FPSTEMPLATE_API AConsumableBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AConsumableBase();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GamePlay)
	UTP_PickUpComponent* PickUpComp;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GamePlay)
	UStaticMeshComponent* ConsumableMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual void Consume();

};
