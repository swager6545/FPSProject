// Fill out your copyright notice in the Description page of Project Settings.


#include "SpeedConsumable.h"
#include "GameFramework/CharacterMovementComponent.h"

void ASpeedConsumable::BeginPlay()
{
	Super::BeginPlay();
	
	//set the timer for how long the effect lasts
	GetWorld()->GetTimerManager().SetTimer(SpeedTimerHandle, this, &ASpeedConsumable::Consume, 1, true);
}

void ASpeedConsumable::Consume()
{
	Super::Consume();
	IncreaseSpeed(2000.f);
}

void ASpeedConsumable::IncreaseSpeed(float WalkSpeed)
{
	//connect this function to the player once they pick up the power up
	AActor* PlayerActor = Cast<AFPSTemplateCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	UCharacterMovementComponent* CharacterMovement = PlayerActor->GetComponentByClass<UCharacterMovementComponent>();
	
	//increment speed timer once the effect is active
	SpeedTimer++;
	UE_LOG(LogTemp, Display, TEXT("Speed Timer: %f"), SpeedTimer);
	
	if (CharacterMovement != nullptr)
	{
		//increase walk speed
		CharacterMovement->MaxWalkSpeed = WalkSpeed;
	}
	
	if (SpeedTimer >= 5.f)
	{
		//clear the timer once it hits 5 seconds
		GetWorld()->GetTimerManager().ClearTimer(SpeedTimerHandle);
		
		//reset character walk speed
		CharacterMovement->MaxWalkSpeed = 600.f;
			
		GEngine->AddOnScreenDebugMessage(0, 2.f, FColor::Red, TEXT("Time is up!"));
	}
}
