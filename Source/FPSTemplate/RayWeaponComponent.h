// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "RayWeaponComponent.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FPSTEMPLATE_API URayWeaponComponent : public UWeaponComponent
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = Weapon)
	float WeaponRange = 10000.f;
	
	virtual void Fire() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Asset References")
	UNiagaraSystem* BeamParticles;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Asset References")
	UNiagaraSystem* HitParticles;
	
	
};
