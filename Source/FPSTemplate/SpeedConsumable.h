// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ConsumableBase.h"
#include "SpeedConsumable.generated.h"

/**
 * 
 */
UCLASS()
class FPSTEMPLATE_API ASpeedConsumable : public AConsumableBase
{
	GENERATED_BODY()
	
	FTimerHandle SpeedTimerHandle;
	
	float SpeedTimer = 0;
	
	virtual void BeginPlay() override;
	
	virtual void Consume() override;
	
	void IncreaseSpeed(float WalkSpeed);
	
};
