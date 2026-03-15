// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TP_WeaponComponent.h"
#include "Blueprint/UserWidget.h"
#include "AmmoWidget.generated.h"

class UTextBlock;
class UAmmoWidget;

/**
 * 
 */
UCLASS()
class FPSTEMPLATE_API UAmmoWidget : public UUserWidget
{
	GENERATED_BODY()
	TWeakObjectPtr<UTP_WeaponComponent> TargetWeaponComponent;
	
	UFUNCTION()
	void OnAmmoChanged(int32 NewMagAmmo, int32 NewCurrentAmmo);
	
protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> AmmoTextBlock;
	
public:
	UFUNCTION(BlueprintCallable)
	void SetTargetWeaponComponent(UTP_WeaponComponent* NewWeaponComponent);
	
};
