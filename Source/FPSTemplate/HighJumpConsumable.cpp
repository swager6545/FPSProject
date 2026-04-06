// Fill out your copyright notice in the Description page of Project Settings.


#include "HighJumpConsumable.h"

#include "GameFramework/CharacterMovementComponent.h"

void AHighJumpConsumable::BeginPlay()
{
	Super::BeginPlay();
	
	//set the timer for how long the effect lasts
	GetWorld()->GetTimerManager().SetTimer(HighJumpTimerHandle, this, &AHighJumpConsumable::Consume, 1, true);
}

void AHighJumpConsumable::Consume()
{
	Super::Consume();
	
	IncreaseJumpHeight(800);
}

void AHighJumpConsumable::IncreaseJumpHeight(float JumpHeight)
{
	//connect this function to the player once they pick up the power up
	AActor* PlayerActor = Cast<AFPSTemplateCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	UCharacterMovementComponent* CharacterMovement = PlayerActor->GetComponentByClass<UCharacterMovementComponent>();
	
	//increment jump timer once the effect is active
	HighJumpTimer++;
	UE_LOG(LogTemp, Display, TEXT("Speed Timer: %f"), HighJumpTimer);
	
	if (CharacterMovement != nullptr)
	{
		//increase jump height
		CharacterMovement->JumpZVelocity = JumpHeight;
	}
	
	if (HighJumpTimer >= 5)
	{
		//clear the timer once it hits 5 seconds
		GetWorld()->GetTimerManager().ClearTimer(HighJumpTimerHandle);
		
		//reset to the default jump value
		CharacterMovement->JumpZVelocity = 420.f;
		
		GEngine->AddOnScreenDebugMessage(0, 2.f, FColor::Red, TEXT("Time is up!"));
	}
}
