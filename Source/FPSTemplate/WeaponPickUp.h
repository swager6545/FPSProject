// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponComponent.h"
#include "PickUpComponent.h"
#include "WeaponPickUp.generated.h"

UCLASS()
class FPSTEMPLATE_API AWeaponPickUp : public AActor
{
	GENERATED_BODY()
	
public:	
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GamePlay)
	UPickUpComponent* PickUpComp;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	UWeaponComponent* WeaponPickUp;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	AFPSTemplateCharacter* OwningCharacter;

};
