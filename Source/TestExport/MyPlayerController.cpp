// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayerController.h"
#include "MyGameInstance.h"


void AMyPlayerController::Registration(FString login,FString password,FString email)
{
	result = -10;
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

		HttpRequest->OnProcessRequestComplete().BindUObject(this, &AMyPlayerController::OnRegistrationCompleted);
		HttpRequest->ProcessRequest();

		UE_LOG(LogTemp, Log, TEXT("Message: %s"), "Registration");
}


void AMyPlayerController::OnRegistrationCompleted(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	
	if (bWasSuccessful)
	{
		FString JsonString = Response->GetContentAsString();
		
		if (JsonString.Equals("-1")) {//error backend
			UE_LOG(LogTemp, Log, TEXT("error: %s"), "error backend");

			result = -1;
		}
		else if (JsonString.Equals("-2")) {//error same game not found (create game)
			UE_LOG(LogTemp, Log, TEXT("error: %s"), "error same game not found (create game)");

			result = -2;
		}
		else if (JsonString.Equals("-3")) {//already registration same login
			UE_LOG(LogTemp, Log, TEXT("error: %s"), "already registration same login");

			result = -3;
		}
		else if (JsonString.Equals("0")) {//success registration
			UE_LOG(LogTemp, Log, TEXT("Message: %s"), "success registration");

			result = 0;
		}
		
	}
	else {
		result = -9;//error request

		UE_LOG(LogTemp, Error, TEXT("not access server"));
	}
}

void AMyPlayerController::Authorization(FString login,FString password)
{
		result = -10;
		FString JsonString2;
		TSharedRef<TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<TCHAR>::Create(&JsonString2);
		JsonWriter->WriteObjectStart();
		JsonWriter->WriteValue("login", login);
		JsonWriter->WriteValue("password", password);
		JsonWriter->WriteValue("gameName", gameName);
		JsonWriter->WriteObjectEnd();
		JsonWriter->Close();

		// the json request
		TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();

		HttpRequest->SetVerb("POST");

		HttpRequest->SetHeader("Content-Type", "application/json");
		HttpRequest->SetURL(backEndAddress + ":8085/authorization");
		HttpRequest->SetContentAsString(JsonString2);
		HttpRequest->OnProcessRequestComplete().BindUObject(this, &AMyPlayerController::OnAuthorizationCompleted);
		HttpRequest->ProcessRequest();
		UE_LOG(LogTemp, Log, TEXT("Message: %s"), "Authorization");

}


void AMyPlayerController::OnAuthorizationCompleted(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	
	if (bWasSuccessful)
	{
		
		FString JsonString = Response->GetContentAsString();

		TSharedPtr<FJsonObject> JsonObject;
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);

		if (FJsonSerializer::Deserialize(Reader, JsonObject))
		{
			id = JsonObject->GetIntegerField("registrated_id");
			info = JsonObject->GetStringField("info");
			if (id == -1) {
				UE_LOG(LogTemp, Log, TEXT("error: %s"), "Authorization failed");
			}
			else {
				UMyGameInstance* gi = Cast<UMyGameInstance>(GetGameInstance());
				gi->UMyGameInstance::setGamerId(id);
				UE_LOG(LogTemp, Log, TEXT("Message: %s"), "Authorization success");
			}

		}
	}
	else {
		id = -9;//error request. backend does not work and advises you not to work

		UE_LOG(LogTemp, Error, TEXT("not access server"));
	}
}

void AMyPlayerController::Update(int idPlayer, FString newInfo)
{

		FString JsonString2;
		TSharedRef<TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<TCHAR>::Create(&JsonString2);
		JsonWriter->WriteObjectStart();
		JsonWriter->WriteValue("id", idPlayer);
		JsonWriter->WriteValue("gameName", newInfo);
		JsonWriter->WriteObjectEnd();
		JsonWriter->Close();

		// the json request
		TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();

		HttpRequest->SetVerb("POST");

		HttpRequest->SetHeader("Content-Type", "application/json");
		HttpRequest->SetURL(backEndAddress + ":8085/update");
		HttpRequest->SetContentAsString(JsonString2);

		HttpRequest->OnProcessRequestComplete().BindUObject(this, &AMyPlayerController::OnUpdateCompleted);
		HttpRequest->ProcessRequest();
		UE_LOG(LogTemp, Log, TEXT("Message: %s"), "Update");

}


void AMyPlayerController::OnUpdateCompleted(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	
	if (bWasSuccessful)
	{
		FString JsonString = Response->GetContentAsString();

		if (JsonString.Equals("-1")) {//error backend update
			result = -1;
			UE_LOG(LogTemp, Log, TEXT("error: %s"), "Update error");

		}
		else if (JsonString.Equals("0")) {//ok
			UE_LOG(LogTemp, Log, TEXT("Message: %s"), "Update success");

			result = 0;
		}

	}
	else {
		result = -9;//error request

		UE_LOG(LogTemp, Error, TEXT("not access server"));
	}
}



FString AMyPlayerController::getInfo()
{
	return info;
}

int AMyPlayerController::getId()
{
	return id;
}
