// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DeliveryItemSpawner.generated.h"

class AAirShip;

UCLASS()
class LD53_API ADeliveryItemSpawner : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "LD53")
	UClass* DeliveryItemClass;

	UPROPERTY(EditAnywhere, Category = "LD53")
	UMaterialInstance* DeliveryItemMaterial;

	UPROPERTY(EditAnywhere, Category = "LD53")
	UMaterialInstance* DeliveryMarkerMaterial;

	UPROPERTY(EditAnywhere, Category = "LD53")
	float SpawnRadius = 10.0f;

private:
	AAirShip* m_AirShip = nullptr;

public:	
	// Sets default values for this actor's properties
	ADeliveryItemSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
