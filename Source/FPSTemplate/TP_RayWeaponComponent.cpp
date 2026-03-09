// Fill out your copyright notice in the Description page of Project Settings.


#include "TP_RayWeaponComponent.h"
#include "FPSTemplateCharacter.h"
#include "NiagaraDataInterfaceArrayFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

void UTP_RayWeaponComponent::Fire()
{
	Super::Fire();
	
	UWorld* const World = GetWorld();
	if (World != nullptr)
	{
		APlayerController* PlayerController = Cast<APlayerController>(Character->GetController());
		
		if (PlayerController != nullptr)
		{
			//line trace to make collisions work
			FHitResult OutHit;
			const FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
			/*MuzzleOffset is in camera space, so transform it to world space before offsetting from the
			 *character location to find the final muzzle location*/
			const FVector Start = GetOwner()->GetActorLocation() + SpawnRotation.RotateVector(MuzzleOffset);
			const FVector Forward = SpawnRotation.Vector();
			const FVector End = Start + (Forward * WeaponRange);
			
			//check if the projectiles hit an object
			bool isHit = World->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility);
			FVector BeamEnd = End;
			
			if (isHit)
			{
				//check if the hit result is a blocking hit
				if (OutHit.bBlockingHit)
				{
					AActor* OtherActor = OutHit.GetActor();
					UPrimitiveComponent* OtherComp = OutHit.GetComponent();
					
					if (HitParticles != nullptr)
					{
						//spawn the hit particles
						UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), HitParticles, OutHit.ImpactPoint, OutHit.ImpactNormal.Rotation());
					}
					
					if (OtherActor != nullptr && (OtherActor != GetOwner()) || 
						(OtherComp != nullptr) && (OtherComp->IsSimulatingPhysics()))
					{
						//if any object has simulating physics the beams will trigger it
						if (OtherComp->IsSimulatingPhysics())
						{
							WeaponEffects(OutHit);
						}
						
						if (OtherActor != GetOwner())
						{
							UpdateDamage(OutHit);
						}
						
						if (BeamParticles != nullptr)
						{
							//add effects to the ray gun
							UNiagaraComponent* effect = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), BeamParticles, Start);
							
							if (effect != nullptr)
							{
								effect->SetVariableVec3(TEXT("EndPoint"), BeamEnd);
							}
							
							//play sound when it hits any target
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
						}
					}
				}
			}
		}
	}
}
