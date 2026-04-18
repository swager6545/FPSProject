// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "WeaponComponent.generated.h"

class AFPSTemplateCharacter;
class UWeaponDefinition;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAmmoChanged, int32, MagAmmo, int32, CurrentAmmo);

UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPSTEMPLATE_API UWeaponComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()

public:
	
	/** Sets default values for this component's properties */
	UWeaponComponent();
	
	UFUNCTION(BlueprintCallable, Category="Weapon")
	bool SetupWeaponControls(AFPSTemplateCharacter* TargetCharacter, UWeaponDefinition* WeaponDefinition);
	
	UFUNCTION()
	void UpdateDamage(FHitResult OutHit) const;
	
	UFUNCTION()
	void WeaponEffects(FHitResult OutHit) const;
	
	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	USoundBase* FireSound;
	
	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* FireAnimation;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	FVector MuzzleOffset;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* FireMappingContext;

	/** Fire Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* FireAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* ReloadAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	float WeaponDamage;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	float WeaponKnockback;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	float UpKnockback;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	bool ProjectileGravity;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	bool DoesShrink;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	bool DoesGrow;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	int32 Ammo;
	
	UPROPERTY(BlueprintReadWrite, Category=Gameplay)
	int32 MaxAmmoCapacity;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	int32 MagAmmo;
	
	UPROPERTY(BlueprintReadWrite, Category=Gameplay)
	int32 MaxMagAmmo;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	float ReloadTime;
	
	UPROPERTY(BlueprintAssignable, Category=Weapons)
	FOnAmmoChanged OnAmmoChanged;
	
protected:
	/** Ends gameplay for this component. */
	UFUNCTION()
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	/** Make the weapon Fire a Projectile */
	UFUNCTION(BlueprintCallable, Category="Weapon")
	virtual void Fire();
	
	UFUNCTION()
	void DisplayAmmoUI();
	
	UFUNCTION(BlueprintCallable, Category="Weapon")
	void Reload();
	
	/** The Character holding this weapon*/
	AFPSTemplateCharacter* Character;
};
