// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthBarWidget.h"

#include "HealthComponent.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UHealthBarWidget::OnHealthChanged(float NewHealth, float MaxHealth)
{
	//set up the percentage of health the actor has
	float Percentage = NewHealth/MaxHealth;
	HealthBar->SetPercent(Percentage);
	
	//convert the percentage float to a string
	HealthText->SetText(FText::FromString(FString::Printf(TEXT("%d%%"), static_cast<int32>(Percentage * 100))));
}

void UHealthBarWidget::SetTargetHealthComponent(UHealthComponent* NewHealthComponent)
{
	//check if the target health component is the new health component
	if (TargetHealthComponent == NewHealthComponent)
	{
		return;
	}
	
	//unregister from the old target health component
	if (TargetHealthComponent.IsValid())
	{
		TargetHealthComponent->OnHealthChanged.RemoveDynamic(this, &UHealthBarWidget::OnHealthChanged);
	}
	
	TargetHealthComponent = NewHealthComponent;
	
	//register to the new target health component
	if (TargetHealthComponent.IsValid())
	{
		TargetHealthComponent->OnHealthChanged.AddDynamic(this, &UHealthBarWidget::OnHealthChanged);
	}
}
