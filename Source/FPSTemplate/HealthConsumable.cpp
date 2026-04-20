// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthConsumable.h"
#include "HealthComponent.h"

void AHealthConsumable::BeginPlay()
{
	Super::BeginPlay();
	
	//set the timer for the amount of time the health goes up by every 2 seconds
	GetWorld()->GetTimerManager().SetTimer(HealthTimerHandle, this, &AHealthConsumable::Consume, 1, true);
}

void AHealthConsumable::Consume()
{
	Super::Consume();
	
	AddHealth(5);
}

void AHealthConsumable::AddHealth(int32 Amount)
{
	//connect this function to the player once they pick up the potion
	AActor* PlayerActor = Cast<AFPSTemplateCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	UHealthComponent* HealthComp = PlayerActor->GetComponentByClass<UHealthComponent>();
	
	//increments the timer to update every second the function is called until the timer handle is clear
	HealthTimer++;
	
	UE_LOG(LogTemp, Display, TEXT("Health Timer: %f"), HealthTimer);
	
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
		
		//once the time limit hits 5 seconds, it will stop and clear the timer
		if (HealthTimer >= 5)
		{
			//clear the timer once it hits 5 seconds
			GetWorld()->GetTimerManager().ClearTimer(HealthTimerHandle);
			
			GEngine->AddOnScreenDebugMessage(0, 2.f, FColor::Red, TEXT("Time is up!"));
		}
	}
}

