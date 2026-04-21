// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PickUpComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemPickUp.generated.h"

class UItemDefinition;

UCLASS(BlueprintType, Blueprintable)
class FPSTEMPLATE_API AItemPickUp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemPickUp();
	
	void InitializePickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UPROPERTY(EditAnywhere, Category = "Pickup | Item Table")
	FName PickupItemID;
	
	UPROPERTY(EditAnywhere, Category = "Pickup | Item Table")
	TSoftObjectPtr<UDataTable> PickupDataTable;
	
	UPROPERTY(VisibleAnywhere, Category = "Pickup | Reference")
	TObjectPtr<UItemDefinition> ReferenceItem;
	
	UPROPERTY(VisibleDefaultsOnly, Category = "Pickup | Mesh")
	TObjectPtr<UStaticMeshComponent> PickupMeshComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup | Components")
	TObjectPtr<UPickUpComponent> PickUpComp;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup | Respawn")
	bool ShouldRespawn;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup | Respawn")
	float RespawnTime = 4.0f;
	
	FTimerHandle RespawnTimerHandle;

/* Won't work when building the game
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
*/

};
