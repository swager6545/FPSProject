// Copyright Epic Games, Inc. All Rights Reserved.


#include "TP_WeaponComponent.h"

#include <filesystem>

#include "FPSTemplateCharacter.h"
#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Animation/AnimInstance.h"
#include "Engine/LocalPlayer.h"
#include "Engine/World.h"
#include "HealthComponent.h"
#include "InventoryComponent.h"
#include "TP_WeaponPickUp.h"
#include "WeaponDefinition.h"

// Sets default values for this component's properties
UTP_WeaponComponent::UTP_WeaponComponent()
{
	// Default offset from the character location for projectiles to spawn
	MuzzleOffset = FVector(100.0f, 0.0f, 10.0f);
	
	// Default weapon damage
	WeaponDamage = 50.f;
	
	// Default weapon knockback
	WeaponKnockback = 2000.f;
	
	// Enables gravity
	ProjectileGravity = true;
	
	Ammo = MaxAmmoCapacity;
	MagAmmo = MaxMagAmmo;
}

bool UTP_WeaponComponent::AttachWeapon(AFPSTemplateCharacter* TargetCharacter, UWeaponDefinition* WeaponDefinition)
{
	Character = TargetCharacter;
	
	// Check that the character is valid, and has no weapon component yet
	if (Character == nullptr || WeaponDefinition == nullptr)
	{
		return false;
	}
	
	if (!TargetCharacter->IsWeaponEquipped(WeaponDefinition))
	{
		//spawn the weapon pickup to appear on the character
		ATP_WeaponPickUp* WeaponToEquip = 
	GetWorld()->SpawnActor<ATP_WeaponPickUp>(WeaponDefinition->WeaponAsset, Character->GetActorTransform());

		// Attach the weapon to the First Person Character
		FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
		WeaponToEquip->AttachToComponent(Character->GetMesh1P(), AttachmentRules, FName(TEXT("GripPoint")));
		
		//add the weapon to the inventory
		TargetCharacter->InventoryComponent->WeaponInventory.Add(WeaponDefinition);
		WeaponToEquip->OwningCharacter = TargetCharacter;
		CurrentWeapon = WeaponToEquip;
	
		// Set the maximum ammo capacity
		if (Ammo >= MaxAmmoCapacity)
		{
			Ammo = MaxAmmoCapacity;
		}
	
		// Set the maximum mag capacity
		if (MagAmmo >= MaxMagAmmo)
		{
			MagAmmo = MaxMagAmmo;
		}
	
		// Subtract the current ammo with the mag ammo so that it accurately show how many bullets the player has
		Ammo = Ammo - MagAmmo;
	
		OnAmmoChanged.Broadcast(MagAmmo, Ammo);
		
		// Set up action bindings
		if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
			{
				// Set the priority of the mapping to 1, so that it overrides the Jump action with the Fire action when using touch input
				Subsystem->AddMappingContext(FireMappingContext, 1);
			}

			if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
			{
				// Fire
				EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &UTP_WeaponComponent::Fire);
			
				// Reload
				EnhancedInputComponent->BindAction(ReloadAction, ETriggerEvent::Completed, this, &UTP_WeaponComponent::Reload);
			}
		}
	}
	return true;
}

void UTP_WeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// Ensure we have a character owner
	if (Character != nullptr)
	{
		// Remove the input mapping context from the Player Controller
		if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
			{
				Subsystem->RemoveMappingContext(FireMappingContext);
			}
		}
	}

	// Maintain the EndPlay call chain
	Super::EndPlay(EndPlayReason);
}

void UTP_WeaponComponent::Fire()
{
	// Function will be overriden
}

void UTP_WeaponComponent::UpdateDamage(FHitResult OutHit) const
{
	AActor* DamageActor = OutHit.GetActor();
	
	// Add damage to the actors
	UHealthComponent* HealthComp = DamageActor->GetComponentByClass<UHealthComponent>();
	if (HealthComp != nullptr)
	{
		//the actors will take damage after the beam hits them
		HealthComp->UpdateHealth(WeaponDamage);
	}
}

void UTP_WeaponComponent::WeaponEffects(FHitResult OutHit) const
{
	AActor* OtherActor = OutHit.GetActor();
	UPrimitiveComponent* OtherComp = OutHit.GetComponent();
	
	// Make the physics work
	FRotator WeaponRotator = Character->GetActorRotation();
	const FVector WeaponVelocity = WeaponRotator.Vector();
	const FVector UpWeaponVelocity = OtherComp->GetUpVector() * WeaponRotator.RotateVector(OtherComp->GetUpVector());
	
	// Knockback effect
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != nullptr) && (OtherActor != GetOwner()) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(WeaponVelocity * WeaponKnockback * 1000, OtherActor->GetActorLocation());
		
		// Gravity effect
		// If it's false the projectiles will make the objects have zero gravity
		if (!ProjectileGravity)
		{
			OtherComp->SetEnableGravity(false);
		}
		
		// Knockback goes up effect (It doesn't always work sometimes the objects don't go up when hit in a certain direction)
		OtherComp->AddImpulseAtLocation(UpWeaponVelocity * UpKnockback * 1000, OtherActor->GetActorLocation());
		
		if (DoesShrink)
		{
			OtherActor->SetActorScale3D(OtherActor->GetActorScale3D() * 0.666f);
			OtherComp->SetMassScale(NAME_None, OtherComp->GetMassScale() * (1 / 0.666f));
		}
		
		if (DoesGrow)
		{
			OtherActor->SetActorScale3D(OtherActor->GetActorScale3D() * 2);
		}
	} 
	
}

void UTP_WeaponComponent::Reload()
{
	if (MagAmmo < MaxMagAmmo &&  Ammo > 0)
	{
		// Bullets left in the magazine
		int32 BulletsLeft = MaxMagAmmo - MagAmmo;
		
		// Bullets that is left over to reload
		int32 BulletsToReload = FMath::Min(BulletsLeft, Ammo);
		
		MagAmmo += BulletsToReload;
		Ammo -= BulletsToReload;
		
		// Clamp these values so that the ammo won't go over the limit
		MagAmmo = FMath::Clamp(MagAmmo, 0, MaxMagAmmo);
		Ammo = FMath::Clamp(Ammo, 0, MaxAmmoCapacity);
		
		// Update the ammo counter once the weapon is reloaded
		OnAmmoChanged.Broadcast(MagAmmo, Ammo);
		
		if (Ammo == 0)
		{
			UE_LOG(LogTemp, Display, TEXT("You ran out of ammo"));
		}
		
	}
}
