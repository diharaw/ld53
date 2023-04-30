// Fill out your copyright notice in the Description page of Project Settings.


#include "DeliveryItemSpawner.h"
#include "AirShip.h"
#include "DeliveryItem.h"
#include "DeliveryDestination.h"
#include "Kismet/GameplayStatics.h"

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

	if (AirShip)
	{
		TArray<AActor*> Destinations;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADeliveryDestination::StaticClass(), Destinations);

		if (Destinations.Num() != AirShip->GetNumTotalDeliveryItems())
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Mismatch between number of destinations and total number of delivery items!"));
			return;
		}

		const FColor ColorTable[] = {
			FColor::Red,
			FColor::Green,
			FColor::Blue,
			FColor::Yellow,
			FColor::Cyan,
			FColor::Magenta,
			FColor::Orange,
			FColor::Purple,
			FColor::Turquoise,
			FColor::Emerald
		};

		for (int i = 0; i < AirShip->GetNumTotalDeliveryItems(); i++)
		{
			FActorSpawnParameters SpawnInfo;
			SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

			FVector Location = GetActorLocation() + FVector(FMath::RandRange(-SpawnRadius, SpawnRadius), FMath::RandRange(-SpawnRadius, SpawnRadius), 0.0f);
			FRotator Rotation = GetActorRotation();

			AActor* NewActor = GetWorld()->SpawnActor(DeliveryItemClass, &Location, &Rotation, SpawnInfo);
			ADeliveryItem* DeliveryItem = Cast< ADeliveryItem>(NewActor);

			FColor Color = ColorTable[i];

			if (DeliveryItem)
				DeliveryItem->AssignIDAndColor(i, Color, DeliveryItemMaterial);

			ADeliveryDestination* DeliveryDestination = Cast<ADeliveryDestination>(Destinations[i]);

			if (DeliveryDestination)
				DeliveryDestination->AssignIDAndColor(i, Color, DeliveryMarkerMaterial);
		}
	}
}

// Called every frame
void ADeliveryItemSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

