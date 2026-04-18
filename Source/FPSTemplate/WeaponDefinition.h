// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemDefinition.h"
#include "WeaponDefinition.generated.h"

class AWeaponPickUp;

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class FPSTEMPLATE_API UWeaponDefinition : public UItemDefinition
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<AWeaponPickUp> WeaponAsset;
	
	virtual UWeaponDefinition* CreateItemCopy(UObject* Outer) const override;
	
	
	
};
