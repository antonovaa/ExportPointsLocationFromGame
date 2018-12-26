// Fill out your copyright notice in the Description page of Project Settings.

#include "MyBlueprintFunctionLibraryTest.h"





void UMyBlueprintFunctionLibraryTest::SwitchAuthority( EMyEnum& Branches)
{

	if (1 == 1)
	{
		Branches = EMyEnum::Authority;
	}
	else
	{
		Branches = EMyEnum::Remote;
	}
	/*if (this->role)
	{
		Branches = EMyEnum::Authority;
	}
	if (Role == ROLE_SimulatedProxy)
	{
	Branches = EMyEnum::Remote;
	}
	else
	{
	Branches = EMyEnum::Standalone;
	}*/
}