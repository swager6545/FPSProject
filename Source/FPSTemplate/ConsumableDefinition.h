// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemDefinition.h"
#include "ConsumableDefinition.generated.h"

class AConsumableBase;

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class FPSTEMPLATE_API UConsumableDefinition : public UItemDefinition
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<AConsumableBase> ConsumableAsset;
	
	virtual UConsumableDefinition* CreateItemCopy(UObject* Outer) const override;
	
};
