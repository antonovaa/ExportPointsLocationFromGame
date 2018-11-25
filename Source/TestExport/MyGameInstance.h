// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class TESTEXPORT_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
		
private:
		int gamer_id = -10;

public:

	UFUNCTION(BlueprintCallable, Category = "identity")
	int getGamerId();

	void setGamerId(int id);
	
	
};
