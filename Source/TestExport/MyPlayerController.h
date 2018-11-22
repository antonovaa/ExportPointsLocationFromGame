// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "Paths.h"
#include "FileHelper.h"
#include "Runtime/Engine/Classes/Engine/NetDriver.h"
#include "PlatformFilemanager.h"
#include "Runtime/Json/Public/Dom/JsonObject.h"
#include "Runtime/Json/Public/Serialization/JsonReader.h"
#include "Runtime/Json/Public/Serialization/JsonReader.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Runtime/json/public/serialization/JsonWriter.h"
#include "Engine/World.h"

#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TESTEXPORT_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:
	FString gameName = "Test";
	FString backEndAddress = "192.168.1.2";
public:
	void PostSendCrash(FString login, FString password, FString email);
	void OnYourFunctionCompleted(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	
	
};
