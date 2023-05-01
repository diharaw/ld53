// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CoalSpawner.generated.h"

UCLASS()
class LD53_API ACoalSpawner : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "LD53")
	float SpawnDelay = 1.0f;

	UPROPERTY(EditAnywhere, Category = "LD53")
	float SpawnRadius = 10.0f;

	UPROPERTY(EditAnywhere, Category = "LD53")
	int MaxCoalPieces = 10;

	UPROPERTY(EditAnywhere, Category = "LD53")
	UClass* CoalClass;

private:
	FTimerHandle m_SpawnTimerHandle;
	int m_NumSpawned = 0;

public:	
	// Sets default values for this actor's properties
	ACoalSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void DecreaseNumCoalChunks();

private:
	void OnSpawnCoalChunk();
};
