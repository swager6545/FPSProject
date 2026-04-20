// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuHUD.h"

#include "Blueprint/UserWidget.h"

void AMainMenuHUD::BeginPlay()
{
	Super::BeginPlay();
	
	//display menu widget
	if (MenuWidget)
	{
		UUserWidget* MenuWidgetRef = CreateWidget(GetWorld(), MenuWidget);
		if (MenuWidgetRef)
		{
			MenuWidgetRef->AddToViewport();
		}
	}
}
