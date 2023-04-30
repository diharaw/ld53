// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CoalSpawner.generated.h"

UCLASS()
class LD53_API ACoalSpawner : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Members")
	float SpawnDelay = 1.0f;

	UPROPERTY(EditAnywhere, Category = "Members")
	int MaxCoalPieces = 10;

	UPROPERTY(EditAnywhere, Category = "Members")
	class AActor* SpawnPoint;

	UPROPERTY(EditAnywhere, Category = "Members")
	UClass* CoalClass;

private:
	class UBoxComponent* m_TriggerVolume = nullptr;
	bool m_IsPlayerPresent = false;
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
	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void OnSpawnCoalChunk();
};
