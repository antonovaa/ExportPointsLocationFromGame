// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyBlueprintFunctionLibraryTest.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EMyEnum : uint8
{
	//public:
	//BranchA,
	//BranchB

	Authority,
	Remote,
	Standalone
};

UCLASS()
class TESTEXPORT_API UMyBlueprintFunctionLibraryTest : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Meta = (ExpandEnumAsExecs = Branches), Category = Game)
		void SwitchAuthority(EMyEnum& Branches);

	
	
};
