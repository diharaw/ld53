// Fill out your copyright notice in the Description page of Project Settings.


#include "DeliveryDestination.h"
#include "Components/BoxComponent.h"
#include "DeliveryItem.h"
#include "CoalPiece.h"

// Sets default values
ADeliveryDestination::ADeliveryDestination()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ADeliveryDestination::BeginPlay()
{
	Super::BeginPlay();

	m_TriggerVolume = FindComponentByClass<UBoxComponent>();

	if (m_TriggerVolume)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Found Box Component"));

		m_TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &ADeliveryDestination::OverlapBegin);
		m_TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &ADeliveryDestination::OverlapEnd);
	}
}

// Called every frame
void ADeliveryDestination::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADeliveryDestination::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Overlapped!"));

	if (OtherActor->IsA<ACoalPiece>())
	{
	}
	else if (OtherActor->IsA<ADeliveryItem>())
	{
		ADeliveryItem* DeliveryItem = Cast<ADeliveryItem>(OtherActor);

		OtherActor->DisableComponentsSimulatePhysics();

		if (DeliveryItem->DestinationID == DestinationID)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("Item Delivered to Correct Destination!"));

			// TODO: mark delivery item as delivered
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("Item Delivered to Incorrect Destination!"));

			// TODO: mark delivery item as missed 
		}
	}
}

void ADeliveryDestination::OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}
