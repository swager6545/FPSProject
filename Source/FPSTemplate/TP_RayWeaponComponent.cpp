// Fill out your copyright notice in the Description page of Project Settings.


#include "TP_RayWeaponComponent.h"
#include "FPSTemplateCharacter.h"
#include "FPSTemplateCharacter.h"

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
			DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1, 0, 1);
			
			//check if the hit result is a blocking hit
			if (isHit)
			{
				if (OutHit.bBlockingHit)
				{
					AActor* OtherActor = OutHit.GetActor();
					UPrimitiveComponent* OtherComp = OutHit.GetComponent();
					
					if (OtherActor != nullptr && (OtherActor != GetOwner()) && 
						(OtherComp != nullptr) && (OtherComp->IsSimulatingPhysics()))
					{
						//how much force the projectiles have
						OtherComp->AddImpulseAtLocation(Forward * 300000.f, OutHit.ImpactPoint);
					}
				}
			}
		}
	}
}
