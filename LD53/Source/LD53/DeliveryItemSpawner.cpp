// Fill out your copyright notice in the Description page of Project Settings.


#include "DeliveryItemSpawner.h"
#include "AirShip.h"
#include "DeliveryItem.h"
#include "LD53GameMode.h"

// Sets default values
ADeliveryItemSpawner::ADeliveryItemSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADeliveryItemSpawner::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ADeliveryItemSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!m_HasSpawned && AirShip)
	{
		for (int i = 0; i < AirShip->GetNumTotalDeliveryItems(); i++)
		{
			FActorSpawnParameters SpawnInfo;
			SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

			FVector Location = GetActorLocation() + FVector(FMath::RandRange(-SpawnRadius, SpawnRadius), FMath::RandRange(-SpawnRadius, SpawnRadius), 0.0f);
			FRotator Rotation = GetActorRotation();

			AActor* NewActor = GetWorld()->SpawnActor(DeliveryItemClass, &Location, &Rotation, SpawnInfo);
			ADeliveryItem* DeliveryItem = Cast< ADeliveryItem>(NewActor);

			if (DeliveryItem)
				DeliveryItem->AssignIDAndColor(i, FColor::MakeRandomColor(), DeliveryItemMaterial);
		}

		m_HasSpawned = true;
	}
}

