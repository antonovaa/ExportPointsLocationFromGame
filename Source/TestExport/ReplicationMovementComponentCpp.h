// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ReplicationMovementComponentCpp.generated.h"

class AActor;

USTRUCT(BlueprintType)
struct TESTEXPORT_API FRepParams
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector LocationRep;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FRotator RotatorRep;

};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESTEXPORT_API UReplicationMovementComponentCpp : public UActorComponent
{
	GENERATED_BODY()
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
public:	
	// Sets default values for this component's properties
	UReplicationMovementComponentCpp();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Helicopter, meta = (AllowPrivateAccess = "true"))
		AActor* ParentActor;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	TArray<FRepParams> repParams;
	float 	netFrequency;
	bool Switcher = true;;
	float timeInterplolate = 0.02;
	float timeSumTick = 0;
	bool doOnce = true;

	FVector tempLocation;
	//UPROPERTY(Replicated)
	//	AMyActorRepCpp * Owner;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Helicopter, meta = (AllowPrivateAccess = "true"))
		USceneComponent* SceneComponent;


	FTimerHandle UnusedHandle;

	float DeltaTickTime = 0.02;;


	UPROPERTY(BlueprintReadWrite)
		bool isReplicatedParams = false;

	virtual void PreReplication(IRepChangedPropertyTracker & ChangedPropertyTracker) override;

	UFUNCTION(reliable, netmulticast, Category = "replication Server")
		void getMasFromServerTest(const TArray<FRepParams>& repParamsFromServer);


	UFUNCTION(BlueprintNativeEvent, Category = "replication Server")
		void startReplicateOnClient(const TArray<FRepParams>&  repParamsFromServer);

	UFUNCTION(Reliable, Server, WithValidation, BlueprintCallable, Category = "replication Server")
		void sendToServerToMulticast(FVector v, FRotator r);


	void forReplicationParamsAfterSetUp(FVector v, FRotator r);

	//UFUNCTION(BlueprintCallable, Category = "replication Server")
	void testDelay(const TArray<FRepParams>& repParamsFromServer);
	void startMoveMesh(float delta);
	
};
