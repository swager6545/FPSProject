// Fill out your copyright notice in the Description page of Project Settings.


#include "ConsumableDefinition.h"

UConsumableDefinition* UConsumableDefinition::CreateItemCopy(UObject* Outer) const
{
	//if we need an outer, use GetTransientPackage
	if (!Outer)
	{
		Outer = GetTransientPackage();
	}
	
	return DuplicateObject<UConsumableDefinition>(this, Outer);
}
