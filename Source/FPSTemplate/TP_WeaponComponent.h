// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "TP_WeaponComponent.generated.h"

class AFPSTemplateCharacter;
class ATP_WeaponPickUp;
class UWeaponDefinition;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAmmoChanged, int32, MagAmmo, int32, CurrentAmmo);

UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPSTEMPLATE_API UTP_WeaponComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()

public:
	
	/** Sets default values for this component's properties */
	UTP_WeaponComponent();

	/** Attaches the actor to a FirstPersonCharacter */
	UFUNCTION(BlueprintCallable, Category="Weapon")
	bool AttachWeapon(AFPSTemplateCharacter* TargetCharacter, UWeaponDefinition* WeaponDefinition);
	
	UFUNCTION()
	void UpdateDamage(FHitResult OutHit) const;
	
	UFUNCTION()
	void WeaponEffects(FHitResult OutHit) const;
	
	UFUNCTION(BlueprintCallable, Category="Weapon")
	void Reload();
	
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
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons")
	ATP_WeaponPickUp* CurrentWeapon;
	
protected:
	/** Ends gameplay for this component. */
	UFUNCTION()
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	/** Make the weapon Fire a Projectile */
	UFUNCTION(BlueprintCallable, Category="Weapon")
	virtual void Fire();
	
	/** The Character holding this weapon*/
	AFPSTemplateCharacter* Character;
};
