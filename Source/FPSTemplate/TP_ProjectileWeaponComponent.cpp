// Fill out your copyright notice in the Description page of Project Settings.


#include "TP_ProjectileWeaponComponent.h"
#include "FPSTemplateCharacter.h"
#include "FPSTemplateProjectile.h"
#include "Kismet/GameplayStatics.h"

void UTP_ProjectileWeaponComponent::Fire()
{
	Super::Fire();
	
	if (Character == nullptr || Character->GetController() == nullptr)
	{
		return;
	}

	// Try and fire a projectile
	if (ProjectileClass != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			//if there is ammo the gun will shoot projectiles normally until it runs out
			if (MagAmmo > 0)
			{
				APlayerController* PlayerController = Cast<APlayerController>(Character->GetController());
				const FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
				// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
				const FVector SpawnLocation = GetOwner()->GetActorLocation() + SpawnRotation.RotateVector(MuzzleOffset);
	
				//Set Spawn Collision Handling Override
				FActorSpawnParameters ActorSpawnParams;
				ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	
				// Spawn the projectile at the muzzle

				if (AFPSTemplateProjectile* BulletProjectile = World->SpawnActor<AFPSTemplateProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams))
				{
					BulletProjectile->SetOwningWeapon(this);
				}
				
				// Try and play the sound if specified
				if (FireSound != nullptr)
				{
					UGameplayStatics::PlaySoundAtLocation(this, FireSound, Character->GetActorLocation());
				}
				
				// Try and play a firing animation if specified
				if (FireAnimation != nullptr)
				{
					// Get the animation object for the arms mesh
					UAnimInstance* AnimInstance = Character->GetMesh1P()->GetAnimInstance();
					if (AnimInstance != nullptr)
					{
						AnimInstance->Montage_Play(FireAnimation, 1.f);
					}
				}
				
				//decrement the ammo once fired
				MagAmmo -= 1;
				OnAmmoChanged.Broadcast(MagAmmo, Ammo);
			}
		}
	}
	else if (Ammo > 0)
	{
		Reload();
	}
}
