// Fill out your copyright notice in the Description page of Project Settings.


#include "CoalSpawner.h"
#include "Components/BoxComponent.h"
#include "FPSCharacter.h"
#include "CoalPiece.h"

// Sets default values
ACoalSpawner::ACoalSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACoalSpawner::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(m_SpawnTimerHandle, this, &ACoalSpawner::OnSpawnCoalChunk, SpawnDelay, true); 
}

void ACoalSpawner::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorld()->GetTimerManager().ClearTimer(m_SpawnTimerHandle);
	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
}

// Called every frame
void ACoalSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACoalSpawner::DecreaseNumCoalChunks()
{
	if (m_NumSpawned > 0)
		m_NumSpawned--;
}

void ACoalSpawner::OnSpawnCoalChunk()
{
	if (m_NumSpawned < MaxCoalPieces)
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		FVector Location = GetActorLocation() + FVector(FMath::RandRange(-SpawnRadius, SpawnRadius), FMath::RandRange(-SpawnRadius, SpawnRadius), 0.0f);
		FRotator Rotation = GetActorRotation();

		GetWorld()->SpawnActor(CoalClass, &Location, &Rotation, SpawnInfo);

		m_NumSpawned++;
	}
}