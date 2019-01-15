// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "Engine/DataAsset.h"
#include "Runtime/GameplayTags/Classes/GameplayTagContainer.h"

#include "MyDataAsset.generated.h"

/**
 * 
 */


USTRUCT(BlueprintType)
struct FIslandStruct: public FGameplayTag
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(BlueprintReadWrite)
		int32 SomeNumber;

};





UCLASS()
class TESTEXPORT_API UMyDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
	
	
	
};
