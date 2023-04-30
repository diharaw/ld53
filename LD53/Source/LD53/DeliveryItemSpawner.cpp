// Fill out your copyright notice in the Description page of Project Settings.


#include "DeliveryItemSpawner.h"
#include "AirShip.h"
#include "DeliveryItem.h"
#include "LD53GameMode.h"

// Sets default values
ADeliveryItemSpawner::ADeliveryItemSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ADeliveryItemSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	ALD53GameMode* GameMode = Cast<ALD53GameMode>(GetWorld()->GetAuthGameMode());

	for (int i = 0; i < GameMode->GetAirShip()->GetNumDeliveryItems(); i++)
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		FVector Location = SpawnPoint->GetActorLocation() + FVector(FMath::RandRange(-SpawnRadius, SpawnRadius), FMath::RandRange(-SpawnRadius, SpawnRadius), 0.0f);
		FRotator Rotation = SpawnPoint->GetActorRotation();

		AActor* NewActor = GetWorld()->SpawnActor(DeliveryItemClass, &Location, &Rotation, SpawnInfo);
		ADeliveryItem* DeliveryItem = Cast< ADeliveryItem>(NewActor);

		if (DeliveryItem)
			DeliveryItem->AssignIDAndColor(i, FColor::MakeRandomColor(), DeliveryItemMaterial);
	}
}

// Called every frame
void ADeliveryItemSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

