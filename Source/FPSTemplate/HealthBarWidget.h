// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthBarWidget.generated.h"

class UProgressBar;
class UTextBlock;
class UHealthBarWidget;

/**
 * 
 */
UCLASS()
class FPSTEMPLATE_API UHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()
	TWeakObjectPtr<UHealthComponent> TargetHealthComponent;
	
	//get the on health change delegate from the health component so that the UI works alongside it
	UFUNCTION()
	void OnHealthChanged(float NewHealth, float MaxHealth);
	
protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UProgressBar> HealthBar;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> HealthText;
	
public:
	//registering and unregistering the health bar to the on health changed delegate
	UFUNCTION(BlueprintCallable)
	void SetTargetHealthComponent(UHealthComponent* NewHealthComponent);
	
	
	
	
};
