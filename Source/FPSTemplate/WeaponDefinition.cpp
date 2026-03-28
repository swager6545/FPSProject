// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponDefinition.h"

UWeaponDefinition* UWeaponDefinition::CreateItemCopy(UObject* Outer) const
{
	//if we need an outer, use GetTransientPackage
	if (!Outer)
	{
		Outer = GetTransientPackage();
	}
	
	return DuplicateObject<UWeaponDefinition>(this, Outer);
}
