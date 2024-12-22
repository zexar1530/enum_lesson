// Fill out your copyright notice in the Description page of Project Settings.

#include "CppBaseActor.h"
#include "Engine/Engine.h"



ACppBaseActor::ACppBaseActor()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);
}

void ACppBaseActor::BeginPlay()
{
	Super::BeginPlay();
	InitialLocation = this->GetActorLocation();
}

// Called every frame
void ACppBaseActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//void ACppBaseActor::ShowActorInformation()
//{
//	UE_LOG(LogTemp, Display, TEXT("Instance name: %s"), *PlayerName);
//	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, PlayerName, true, FVector2D(2.0f, 2.0f));
//	UE_LOG(LogTemp, Display, TEXT("EnemyNum: %d"), EnemyNum);
//	UE_LOG(LogTemp, Display, TEXT("IsAlive: %i"), IsALive);
//}

void ACppBaseActor::SinMovement()
{
	InitialLocation.Z += FMath::Sin(Frequency * GetWorld()->GetTimeSeconds()) * Amplitude;
	this->SetActorLocation(InitialLocation);
}

FVector ACppBaseActor::GetInitialLocation()
{
	return InitialLocation;
}

void ACppBaseActor::SetInitialLocation(FVector location)
{
	InitialLocation = location;
}
