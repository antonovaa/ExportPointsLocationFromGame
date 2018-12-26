// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActorRepCpp.generated.h"


//
//USTRUCT(BlueprintType)
//struct TESTEXPORT_API FRepParams
//{
//	GENERATED_USTRUCT_BODY()
//public:
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//		FVector LocationRep;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//		FRotator RotatorRep;
//
//};

UCLASS()
class TESTEXPORT_API AMyActorRepCpp : public AActor
{
	GENERATED_BODY()
	
//pprivate:	
//	// Sets default values for this actor's properties
//	
//	TArray<FRepParams> repParams;
//	float 	netFrequency;
//	bool Switcher = true;;
//	float timeInterplolate = 0.02;
//	float timeSumTick=0;
//	bool doOnce = true;
//
//	FVector tempLocation;
//
//protected:
//	// Called when the game starts or when spawned
//	virtual void BeginPlay() override;
//
//public:	
//
//	//UPROPERTY(Replicated)
//	//	AMyActorRepCpp * Owner;
//
//	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Helicopter, meta = (AllowPrivateAccess = "true"))
//		USceneComponent* SceneComponent;
//
//	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Helicopter, meta = (AllowPrivateAccess = "true"))
//	UStaticMeshComponent * Cube2;
//
//	FTimerHandle UnusedHandle;
//
//	float DeltaTickTime = 0.02;;
//
//	AMyActorRepCpp();
//
//	UPROPERTY(BlueprintReadWrite)
//		bool isReplicatedParams =false;
//
//	// Called every frame
//	virtual void Tick(float DeltaTime) override;
//
//	virtual void PreReplication(IRepChangedPropertyTracker & ChangedPropertyTracker) override;
//
//	UFUNCTION(reliable,netmulticast, Category = "replication Server")
//		void getMasFromServerTest(const TArray<FRepParams>& repParamsFromServer);
//
//	
//	UFUNCTION(BlueprintNativeEvent, Category = "replication Server")
//		void startReplicateOnClient(const TArray<FRepParams>&  repParamsFromServer);
//
//	//UFUNCTION(BlueprintCallable, Category = "replication Server")
//		void ClearMasOnServer();
//
//
//		UFUNCTION(Reliable, Server, WithValidation , BlueprintCallable, Category = "replication Server")
//			void sendToServer(FVector v,FRotator r);
//
//
//	void forReplicationParamsAfterSetUp(FVector v, FRotator r);
//
//	//UFUNCTION(BlueprintCallable, Category = "replication Server")
//	void testDelay(const TArray<FRepParams>& repParamsFromServer);
//	void startMoveMesh(float delta);
//	float interpTo(float current, float target, float deltaTime, float speed);
//
//
//	//UFUNCTION(BlueprintCallable, Category = "Utilities|FlowControl", meta = (Latent, WorldContext = "WorldContextObject", LatentInfo = "LatentInfo", Duration = "0.2", Keywords = "sleep"))
//		//void DelayForClient(UObject* WorldContextObject, float Duration, FLatentActionInfo LatentInfo);
//
//
//
//
//
//
//
//
//
//	//virtual void SetupPlayerInutComponent(class UInputComponent* InputComponent) override;
};
