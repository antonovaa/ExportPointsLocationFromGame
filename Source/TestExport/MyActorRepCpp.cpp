// Fill out your copyright notice in the Description page of Project Settings.

#include "MyActorRepCpp.h"


// Sets default values
AMyActorRepCpp::AMyActorRepCpp()
{
	bReplicates = true;
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyActorRepCpp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyActorRepCpp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyActorRepCpp::PreReplication(IRepChangedPropertyTracker & ChangedPropertyTracker)
{
	bool b = false;
	b= ChangedPropertyTracker.IsReplay();
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, FString::Printf(TEXT("Replicated %s"),(b ? "True" : "False")));

}

//void AMyActorRepCpp::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
//{
//	DOREPLIFETIME(AActor, Owner);
//}