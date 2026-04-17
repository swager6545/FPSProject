// Fill out your copyright notice in the Description page of Project Settings.


#include "EasingFunctionLibrary.h"

float UEasingFunctionLibrary::EaseIn(float X)
{
	return 1 - FMath::Cos((X * PI) / 2.f);
}

float UEasingFunctionLibrary::EaseOut(float X)
{
	return FMath::Sin((X * PI) / 2.f);
}

float UEasingFunctionLibrary::EaseInOut(float X)
{
	return -FMath::Cos((X * PI) - 1 / 2.f);
}

float UEasingFunctionLibrary::FunctionSelection(EEasingFunctionName Name, float Input_)
{
	//to be able to select which easing function you want
	switch (Name)
	{
		case EEasingFunctionName::None:
			return Input_;
		case EEasingFunctionName::EaseIn:
			return EaseIn(Input_);
		case EEasingFunctionName::EaseOut:
			return EaseOut(Input_);
		case EEasingFunctionName::EaseInOut:
			return EaseInOut(Input_);
		default:
			return 0.0f;
	}
}






