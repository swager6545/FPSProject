// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	StartButton->OnClicked.AddDynamic(this, &UMainMenuWidget::LoadLevel);
	ExitButton->OnClicked.AddDynamic(this, &UMainMenuWidget::ExitGame);
}

void UMainMenuWidget::LoadLevel()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("/Game/FirstPerson/Maps/FirstPersonMap"), TRAVEL_Absolute);
}

void UMainMenuWidget::ExitGame()
{
	GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
}
