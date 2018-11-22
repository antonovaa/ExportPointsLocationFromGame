// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayerController.h"

void AMyPlayerController::PostSendCrash(FString login,FString password,FString email)
{

		FString JsonString2;
		TSharedRef<TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<TCHAR>::Create(&JsonString2);
		JsonWriter->WriteObjectStart();
		JsonWriter->WriteValue("login", login);
		JsonWriter->WriteValue("password", password);
		JsonWriter->WriteValue("email", email);
		JsonWriter->WriteValue("gameName", gameName);
		JsonWriter->WriteObjectEnd();
		JsonWriter->Close();

		// the json request
		TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();

		HttpRequest->SetVerb("POST");

		HttpRequest->SetHeader("Content-Type", "application/json");
		HttpRequest->SetURL(backEndAddress + ":8085/registration");
		HttpRequest->SetContentAsString(JsonString2);

		HttpRequest->OnProcessRequestComplete().BindUObject(this, &AMyPlayerController::OnYourFunctionCompleted);
		HttpRequest->ProcessRequest();
}


void AMyPlayerController::OnYourFunctionCompleted(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	FString JsonString = Response->GetContentAsString();
	if (bWasSuccessful)
	{
		TSharedPtr<FJsonObject> JsonObject;
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);

		if (FJsonSerializer::Deserialize(Reader, JsonObject))
		{

			int i = JsonObject->GetIntegerField("result");
		}
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("access server"));
	}
}
