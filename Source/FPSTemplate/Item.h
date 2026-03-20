// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TextRenderComponent.h"
#include "Components/BoxComponent.h"
#include "Item.generated.h"

UENUM(BlueprintType)
enum class ERarity : uint8
{
	Common UMETA(DisplayName="Common"),
	Rare UMETA(DisplayName="Rare"),
	VeryRare UMETA(DisplayName="VeryRare"),
	Legendary UMETA(DisplayName="Legendary")
};

USTRUCT(BlueprintType)
struct FItemData
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ERarity Rarity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BaseValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Weight;
};

UCLASS()
class FPSTEMPLATE_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FItemData ItemDetails;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<ERarity,FColor> RarityColor;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Model;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTextRenderComponent* Text;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* Collider;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
	void UpdateTitle();

};
