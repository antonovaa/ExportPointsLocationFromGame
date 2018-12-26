// Fill out your copyright notice in the Description page of Project Settings.

#include "ReplicationMovementComponentCpp.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Materials/MaterialInstanceConstant.h"
#include "UnrealNetwork.h"

// Sets default values for this component's properties
UReplicationMovementComponentCpp::UReplicationMovementComponentCpp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UReplicationMovementComponentCpp::BeginPlay()
{
	Super::BeginPlay();
	ParentActor = GetOwner();

	SetIsReplicated(true);

	netFrequency = ParentActor->NetUpdateFrequency;
	// ...
	
}


// Called every frame
void UReplicationMovementComponentCpp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (ParentActor->Role < ROLE_Authority)
	{
		UReplicationMovementComponentCpp::startMoveMesh(DeltaTime);
	}
}





void UReplicationMovementComponentCpp::forReplicationParamsAfterSetUp(FVector v, FRotator r)
{
	FRepParams rp;
	rp.LocationRep = v;
	rp.RotatorRep = r;
	repParams.Add(rp);
	if (isReplicatedParams) {
		UReplicationMovementComponentCpp::getMasFromServerTest(repParams);
		isReplicatedParams = false;

	}

}

void UReplicationMovementComponentCpp::testDelay(const TArray<FRepParams>&  repParamsFromServer)
{
	repParams.Append(repParamsFromServer);
	if (repParams.Num() > 10) {

		timeInterplolate *= 0.8;
		if (repParams.Num() > 10 + netFrequency) {
			timeInterplolate *= 0.6;
		}
		else if (repParams.Num() > 10 + 2 * netFrequency) {
			timeInterplolate *= 0.4;
		}
	}
	else if (repParams.Num() < 5) {
		doOnce = true;
		timeInterplolate *= 1.05;
	}
}

void UReplicationMovementComponentCpp::startMoveMesh(float delta)
{



	if (repParams.IsValidIndex(1) && repParams.IsValidIndex(0)) {

		FVector tempL = FMath::VInterpTo(repParams[0].LocationRep, repParams[1].LocationRep, delta, 2);
		FRotator tempR= FMath::RInterpTo(repParams[0].RotatorRep, repParams[1].RotatorRep, delta, 2);
		ParentActor->SetActorLocationAndRotation(tempL, tempR);
		timeSumTick += delta;
		if (timeInterplolate <= timeSumTick) {
			timeSumTick = 0;
			repParams.RemoveAt(0);
		}
	}
}

void UReplicationMovementComponentCpp::sendToServerToMulticast_Implementation(FVector v, FRotator r)
{

	//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("sendToServer!!"));

	if (ParentActor->HasAuthority()) {
		//GetWorldTimerManager().SetTimer(UnusedHandle, this, &AMyActorRepCpp::doTestRep, DeltaTickTime, false);
		/*
		if (Switcher) {
		tempLocation = tempLocation + FVector(0, 0, 0.5);

		Switcher = (tempLocation.Z <= 300.0);
		}
		else {
		tempLocation = tempLocation - FVector(0, 0, 0.5);
		Switcher = (tempLocation.Z <-100.0);
		}*/
		ParentActor->SetActorLocationAndRotation(v, r);

		UReplicationMovementComponentCpp::forReplicationParamsAfterSetUp(v, r);
	}

}
bool UReplicationMovementComponentCpp::sendToServerToMulticast_Validate(FVector v, FRotator r) {
	return true;
}

void UReplicationMovementComponentCpp::PreReplication(IRepChangedPropertyTracker & ChangedPropertyTracker)
{
	isReplicatedParams = true;
}


void UReplicationMovementComponentCpp::startReplicateOnClient_Implementation(const TArray<FRepParams>&  repParamsFromServer)
{
	//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::White, TEXT("startReplicateOnClient"));
	UReplicationMovementComponentCpp::testDelay(repParamsFromServer);
}


void UReplicationMovementComponentCpp::getMasFromServerTest_Implementation(const TArray<FRepParams> & repParamsFromServer)
{
	if (ParentActor->Role < ROLE_Authority)
	{
		UReplicationMovementComponentCpp::testDelay(repParamsFromServer);
		//AMyActorRepCpp::startReplicateOnClient(repParamsFromServer);
	}
	if (ParentActor->Role == ROLE_Authority) {

		repParams.Empty(); //AMyActorRepCpp::ClearMasOnServer();

	}
}
