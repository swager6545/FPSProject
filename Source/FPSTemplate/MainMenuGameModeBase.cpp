// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuGameModeBase.h"

#include "Kismet/GameplayStatics.h"

void AMainMenuGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	
	//show mouse cursor when on the menu
	APlayerController* PlayerControllerRef = UGameplayStatics::GetPlayerController(this, 0);
	PlayerControllerRef->SetShowMouseCursor(true);
}
