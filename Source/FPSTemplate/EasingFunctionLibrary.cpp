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

float UEasingFunctionLibrary::SmoothStep(float X)
{
	return FMath::SmoothStep(0.f, 1.f, X);
}

float UEasingFunctionLibrary::ElasticIn(float T, float H, float B)
{
	return FMath::Pow(T, 2) - H * T * sin(B * T * PI);
}

float UEasingFunctionLibrary::FunctionSelection(EEasingFunctionName Name, float Input_, float Input2_, float Input3_)
{
	switch (Name)
	{
		case EEasingFunctionName::None:
			return Input_;
			break;
		case EEasingFunctionName::EaseIn:
			return EaseIn(Input_);
			break;
		case EEasingFunctionName::EaseOut:
			return EaseOut(Input_);
			break;
		case EEasingFunctionName::SmoothStep:
			return SmoothStep(Input_);
			break;
		case EEasingFunctionName::ElasticIn:
			return ElasticIn(Input2_, Input3_, Input_);
			break;
		default:
			return 0.0f;
	}
}






