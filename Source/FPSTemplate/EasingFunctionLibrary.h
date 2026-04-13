// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "EasingFunctionLibrary.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EEasingFunctionName : uint8
{
	None UMETA(DisplayName = "None"),
	EaseIn UMETA(DisplayName = "EaseIn"),
	EaseOut UMETA(DisplayName = "EaseOut"),
	SmoothStep UMETA(DisplayName = "SmoothStep"),
	ElasticIn UMETA(DisplayName = "ElasticIn")
};
UCLASS()
class FPSTEMPLATE_API UEasingFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static float EaseIn(float X);
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static float EaseOut(float X);
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static float SmoothStep(float X, float Edge0, float Edge1);
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static float ElasticIn(float T, float H, float B);
	
	UFUNCTION(BlueprintCallable)
	static float FunctionSelection(EEasingFunctionName Name, float Input_, float Input2_, float Input3_);
	
};
