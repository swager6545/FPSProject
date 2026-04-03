// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDamageChanged);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, float, NewHealth, float, MaxHealth);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPSTEMPLATE_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();
	
	//current health
	UPROPERTY()
	float Health;
	
	//max health
	UPROPERTY(EditDefaultsOnly, Category = "Health")
	float MaxHealth;
	
	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnHealthChanged OnHealthChanged;
	
	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnDamageChanged OnDeath;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	virtual void OnComponentDestroyed(bool bIsDead) override;

public:	
	UFUNCTION(BlueprintCallable, Category = "Health")
	void UpdateHealth(float Damage);
};
