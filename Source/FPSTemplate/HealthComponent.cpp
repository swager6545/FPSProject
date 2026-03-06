// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
	
	//default values for health
	MaxHealth = 100.0f;
	Health = MaxHealth;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
}

//destroy component when the player dies
void UHealthComponent::OnComponentDestroyed(bool bIsDead)
{
	Super::OnComponentDestroyed(bIsDead);
	
	if (bIsDead)
	{
		FOnActorDestroyed();
	}
}


void UHealthComponent::UpdateHealth(float Damage)
{
	Health -= Damage;
	//clamp the values so it won't go over or under the current and max health values
	Health = FMath::Clamp(Health, 0.f, MaxHealth);
	
	//updates the health value
	OnHealthChanged.Broadcast(Health, MaxHealth);
	
	//update the damage when the actors gets hit
	if (Health == 0)
	{
		OnDeath.Broadcast();
		OnComponentDestroyed(true);
	}
}

