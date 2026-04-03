// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ConsumableBase.h"
#include "HealthConsumable.generated.h"

/**
 * 
 */
UCLASS()
class FPSTEMPLATE_API AHealthConsumable : public AConsumableBase
{
	GENERATED_BODY()
	
	FTimerHandle HealthTimerHandle;
	
	//this will be used to set the time for the healing effect
	float HealthTimerLimit = 10;
	
	virtual void Consume() override;
	
	void AddHealth(int32 Amount);
	
};
