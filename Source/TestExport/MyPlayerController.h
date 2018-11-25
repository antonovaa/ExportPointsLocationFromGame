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
#include "Runtime/Json/Public/Serialization/JsonSerializer.h"
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
	FString backEndAddress = "81.5.93.98";
public:


	UPROPERTY(BlueprintReadOnly)
		int result=-10;


	UPROPERTY(BlueprintReadOnly)
		int id =-10;	
	
	UPROPERTY(BlueprintReadOnly)
		FString info="";

	
	UFUNCTION(BlueprintCallable)
		FString getInfo();	

	UFUNCTION(BlueprintCallable)
		int getId();




	UFUNCTION(BlueprintCallable, Category = "Backend", meta = (DisplayName = "Registration Player"))
	void Registration(FString login, FString password, FString email);

	UFUNCTION(BlueprintCallable, Category = "Backend", meta = (DisplayName = "Authorization Player"))
	void Authorization(FString login, FString password);

	UFUNCTION(BlueprintCallable, Category = "Backend", meta = (DisplayName = "Update Player"))
	void Update(int idPlayer, FString newInfo);




	void OnRegistrationCompleted(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	void OnAuthorizationCompleted(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	void OnUpdateCompleted(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	
	
};
