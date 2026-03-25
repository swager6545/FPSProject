// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ItemData.generated.h"

class UItemDefinition;

UENUM(BlueprintType)
enum class EItemType : uint8
{
	Item UMETA(DisplayName = "Item"),
	Consumable UMETA(DisplayName = "Consumable")
};

USTRUCT(BlueprintType)
struct FItemText
{
	GENERATED_USTRUCT_BODY()
	
	//name of item
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Name;
	
	//description of item
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Description;
};

USTRUCT(BlueprintType)
struct FItemData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
	FName ID;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
	EItemType ItemType;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
	FItemText ItemText;
	
	//references the item definition asset paths 
	UPROPERTY(EditAnywhere, Category = "Item Data")
	TSoftObjectPtr<UItemDefinition>ItemBase;
};




