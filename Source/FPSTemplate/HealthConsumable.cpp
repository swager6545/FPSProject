// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthConsumable.h"

#include "HealthComponent.h"

void AHealthConsumable::Consume()
{
	Super::Consume();
	
	AddHealth(10);
}

void AHealthConsumable::AddHealth(int32 Amount)
{
	AActor* PlayerActor = Cast<AFPSTemplateCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	
	UHealthComponent* HealthComp = PlayerActor->GetComponentByClass<UHealthComponent>();
	
	if (HealthComp != nullptr)
	{
		if (HealthComp->Health < HealthComp->MaxHealth)
		{
			//Add health to the player
			HealthComp->UpdateHealth(-Amount);
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(0, 2.f, FColor::Blue, TEXT("Your Health is full"));
		}
	}
}
