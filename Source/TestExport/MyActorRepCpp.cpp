//// Fill out your copyright notice in the Description page of Project Settings.
//
#include "MyActorRepCpp.h"
//#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
//#include "Runtime/Engine/Classes/Materials/MaterialInstanceConstant.h"
//#include "UnrealNetwork.h"
//// Sets default values
//AMyActorRepCpp::AMyActorRepCpp()
//{
//
//	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
//	SetRootComponent(SceneComponent);
//
//
//
//	Cube2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube2"));	
//	UMaterialInstanceConstant* material = Cast<UMaterialInstanceConstant>(StaticLoadObject(UMaterialInstanceConstant::StaticClass(), nullptr, TEXT("Material'/NewMaterial'")));
//	//this->SetRootComponent(RootComponent);
//	Cube2->SetMaterial(0, material);
//	Cube2->SetupAttachment(SceneComponent);
//	Cube2->bEditableWhenInherited = true;
//	static ConstructorHelpers::FObjectFinder<UStaticMesh> Cube2Asset(TEXT("/Game/Geometry/Meshes/1M_Cube"));
//	Cube2->SetStaticMesh(Cube2Asset.Object);
//
//
//	
//	bReplicates = true;
// 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
//	PrimaryActorTick.bCanEverTick = true;
//
//}
//
//// Called when the game starts or when spawned
//void AMyActorRepCpp::BeginPlay()
//{
//	Super::BeginPlay();
//	netFrequency=this->NetUpdateFrequency;
//}
//
//// Called every frame
//void AMyActorRepCpp::Tick(float DeltaTime)
//{
//	/*if (DeltaTickTime == 0) {
//		DeltaTickTime = DeltaTime;
//	}*/
//	Super::Tick(DeltaTime);
//
//	if (Role < ROLE_Authority)
//	{
//		AMyActorRepCpp::startMoveMesh(DeltaTime);
//	}
//
//}
//
//void AMyActorRepCpp::ClearMasOnServer()
//{
//	repParams.Empty();
//}
//
//
//
//void AMyActorRepCpp::forReplicationParamsAfterSetUp(FVector v, FRotator r)
//{
//	FRepParams rp;
//	rp.LocationRep = v;
//	rp.RotatorRep = r;
//	repParams.Add(rp);
//	if (isReplicatedParams) {
//		AMyActorRepCpp::getMasFromServerTest(repParams);
//		isReplicatedParams = false;
//
//	}
//
//}
//
//void AMyActorRepCpp::testDelay(const TArray<FRepParams>&  repParamsFromServer)
//{
//
//
//	repParams.Append(repParamsFromServer);
//
//
//	if (repParams.Num() > 10) {
//
//		timeInterplolate *= 0.8;
//		if (repParams.Num() > 10+ netFrequency) {
//			timeInterplolate *= 0.6;
//		}
//		else if (repParams.Num() > 10+ 2 * netFrequency) {
//			timeInterplolate *= 0.4;
//		}		
//	}
//	else if (repParams.Num() < 5) {		
//		doOnce = true;
//		timeInterplolate *= 1.05;
//	}
//}
//
//
//
////void AMyActorRepCpp::DelayForClient(UObject* WorldContextObject, float Duration, FLatentActionInfo LatentInfo)
////{
////	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
////	{
////		FLatentActionManager& LatentActionManager = World->GetLatentActionManager();
////		if (LatentActionManager.FindExistingAction<FDelayAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL)
////		{
////			LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID, new FDelayAction(Duration, LatentInfo));
////		}
////	}
////}
//
//
//
//
//
//
//void AMyActorRepCpp::startMoveMesh(float delta)
//{
//	
//	
//	
//	if (repParams.IsValidIndex(1)&& repParams.IsValidIndex(0)) {
//		
//		FVector temp = FMath::VInterpTo(repParams[0].LocationRep, repParams[1].LocationRep, delta, 2);
//		Cube2->SetWorldLocationAndRotation(temp, repParams[0].RotatorRep);
//		timeSumTick += delta;
//		if (timeInterplolate<= timeSumTick){
//			timeSumTick = 0;
//			repParams.RemoveAt(0);
//		}		
//	}
//}
//
////float AMyActorRepCpp::interpTo(float current, float target, float deltaTime, float speed) {
////	FMath::VInterpTo()
////	return current + (target-current) * deltaTime * speed;
////}
//
//
//void AMyActorRepCpp::sendToServer_Implementation(FVector v, FRotator r)
//{
//
//	//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("sendToServer!!"));
//
//	if (this->HasAuthority()) {
//		//GetWorldTimerManager().SetTimer(UnusedHandle, this, &AMyActorRepCpp::doTestRep, DeltaTickTime, false);
//		/*
//		if (Switcher) {
//			tempLocation = tempLocation + FVector(0, 0, 0.5);
//
//			Switcher = (tempLocation.Z <= 300.0);
//		}
//		else {
//			tempLocation = tempLocation - FVector(0, 0, 0.5);
//			Switcher = (tempLocation.Z <-100.0);
//		}*/
//		Cube2->SetWorldLocationAndRotation(v, r);
//
//		AMyActorRepCpp::forReplicationParamsAfterSetUp(v,r);
//	}
//
//
//
//}
//bool AMyActorRepCpp::sendToServer_Validate(FVector v, FRotator r) {
//	return true; 
//}
//
//void AMyActorRepCpp::PreReplication(IRepChangedPropertyTracker & ChangedPropertyTracker)
//{
//	
//	isReplicatedParams = true;
//
//}
//
//
//void AMyActorRepCpp::startReplicateOnClient_Implementation(const TArray<FRepParams>&  repParamsFromServer)
//{
//
//	//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::White, TEXT("startReplicateOnClient"));
//	testDelay(repParamsFromServer);
//
//}
//
//
//void AMyActorRepCpp::getMasFromServerTest_Implementation(const TArray<FRepParams> & repParamsFromServer)
//{
//	if (Role < ROLE_Authority)
//	{
//		AMyActorRepCpp::testDelay(repParamsFromServer);
//		//AMyActorRepCpp::startReplicateOnClient(repParamsFromServer);
//	}
//	if (Role == ROLE_Authority) {
//
//		repParams.Empty(); //AMyActorRepCpp::ClearMasOnServer();
//
//	}
//}
//
//
////void AMyActorRepCpp::SetupPlayerInputComponent(class UInputComponent* InputComponent)
////{
////	Super::SetupPlayerInputComponent(InputComponent);
////
////}
//
//
////void AMyActorRepCpp::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
////{
////	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
////	DOREPLIFETIME(AMyActorRepCpp, Cube2);
////}