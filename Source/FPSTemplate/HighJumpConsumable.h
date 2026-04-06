// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ConsumableBase.h"
#include "HighJumpConsumable.generated.h"

/**
 * 
 */
UCLASS()
class FPSTEMPLATE_API AHighJumpConsumable : public AConsumableBase
{
	GENERATED_BODY()
	
	FTimerHandle HighJumpTimerHandle;
	
	float HighJumpTimer = 0;
	
	virtual void BeginPlay() override;
	
	virtual void Consume() override;
	
	void IncreaseJumpHeight(float JumpHeight);
	
};
