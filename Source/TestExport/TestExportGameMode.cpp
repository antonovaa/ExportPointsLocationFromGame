// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "TestExportGameMode.h"
#include "TestExportCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Runtime/Core/Public/Misc/FileHelper.h"
#include "Runtime/Json/Public/Serialization/JsonReader.h"
#include "Runtime/Json/Public/Serialization/JsonSerializer.h"
#include "Runtime/Core/Public/Templates/SharedPointer.h"
#include "Runtime/Json/Public/Dom/JsonObject.h"
#include <string>

#define WIN32_LEAN_AND_MEAN
#include <ShlObj.h>


//#define TEXT TEXT_PASTE
void ATestExportGameMode::BeginPlay()
{

	timeBeginPlay = FDateTime::Now().GetTimeOfDay().GetTotalMicroseconds();
	//GEngine->AddOnScreenDebugMessage(-1, 55.f, FColor::Blue, FString::Printf(TEXT("GM Constructed time from constructed to begin play (seconds) = %f"), (timeBeginPlay - timeConstructed) / 1000000));

	Super::BeginPlay();
}

ATestExportGameMode::ATestExportGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	timeConstructed = FDateTime::Now().GetTimeOfDay().GetTotalMicroseconds();
	ATestExportGameMode::InitParams();

}



void ATestExportGameMode::MyServerTravel(FString mapName)
{
	GetWorld()->ServerTravel(FString(mapName));
}

void ATestExportGameMode::GetMyDocuments(FString & MyDocumentsPath)
{
	MyDocumentsPath = MyDocuments;
}

void ATestExportGameMode::InitParams()
{

	wchar_t Folder[1024];
	char str[1024];
	HRESULT hr = SHGetFolderPathW(0, CSIDL_MYDOCUMENTS, 0, 0, Folder);
	if (SUCCEEDED(hr))
	{
		sprintf(str, "%ws", Folder);
	}
	FString StringTemp(str);
	FString JsonString;
	MyDocuments = StringTemp;
	FString FileNamePath3 = MyDocuments + "/Narratex/serverJson.json";
	if (FFileHelper::LoadFileToString(JsonString, *FileNamePath3))
	{
		UE_LOG(LogTemp, Warning, TEXT("Settings is : %s"), *JsonString);
		TSharedPtr<FJsonObject> JsonObject;
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);
		FString teststr;

		if (FJsonSerializer::Deserialize(Reader, JsonObject))
		{

			AdminInformation.Language = JsonObject->GetIntegerField(TEXT("language"));
			AdminInformation.PlayersNum = JsonObject->GetIntegerField(("playerCount"));
			AdminInformation.MapID = JsonObject->GetIntegerField(("mapId"));
			AdminInformation.ServerPortAdmin = JsonObject->GetIntegerField(("ServerPortAdmin"));
			AdminInformation.ServerIpAdmin = JsonObject->GetStringField(("ServerIpAdmin"));


			auto objects = JsonObject->GetArrayField("infoPlayersInGames");
			for (int i = 0; i < objects.Num(); i++)
			{
				TSharedPtr<FJsonObject> PlayerJsonObject = objects[i]->AsObject();
				FPlayerInformation playerInformation;

				playerInformation.PlayerGender = static_cast<EGenderTypeBase>(PlayerJsonObject->GetIntegerField(TEXT("playerGender")));
				playerInformation.PlayerIP = PlayerJsonObject->GetStringField(TEXT("playerIp"));
				playerInformation.PlayerId = PlayerJsonObject->GetIntegerField(TEXT("playerId"));

				AdminInformation.Players.Add(playerInformation);
			}
			UE_LOG(LogTemp, Warning, TEXT("Server JSON deserialized!"));

		}

		else
		{
			UE_LOG(LogTemp, Warning, TEXT("JSON aren't deserialized!"));
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("File open error!"));
	}
}

void ATestExportGameMode::GenericPlayerInitialization(AController * C)
{
	Super::GenericPlayerInitialization(C);
	SeamlessTravelConnectedController(C);
}

void ATestExportGameMode::SeamlessTravelConnectedController_Implementation(AController* C)
{
	GEngine->AddOnScreenDebugMessage(-1, 55.f, FColor::White, TEXT("Connected"));
}
