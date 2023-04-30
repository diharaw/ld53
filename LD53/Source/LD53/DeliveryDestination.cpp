// Fill out your copyright notice in the Description page of Project Settings.


#include "DeliveryDestination.h"
#include "Components/BoxComponent.h"
#include "DeliveryItem.h"
#include "CoalPiece.h"
#include "AirShip.h"
#include "LD53GameMode.h"

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

void ADeliveryDestination::AssignIDAndColor(int _ID, FColor _Color, UMaterialInstance* _Material)
{
	m_DestinationID = _ID;
	m_Mesh = FindComponentByClass<UStaticMeshComponent>();

	if (m_Mesh && _Material)
	{
		UMaterialInstanceDynamic* DynamicMaterialInst = UMaterialInstanceDynamic::Create(_Material, m_Mesh);

		DynamicMaterialInst->SetVectorParameterValue("Colour", _Color);

		m_Mesh->SetMaterial(0, DynamicMaterialInst);
	}
}

int ADeliveryDestination::GetDestinationID()
{
	return m_DestinationID;
}

void ADeliveryDestination::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Overlapped!"));

	if (OtherActor->IsA<ACoalPiece>())
	{
	}
	else if (OtherActor->IsA<ADeliveryItem>())
	{
		ALD53GameMode* GameMode = Cast<ALD53GameMode>(GetWorld()->GetAuthGameMode());
		ADeliveryItem* DeliveryItem = Cast<ADeliveryItem>(OtherActor);

		OtherActor->DisableComponentsSimulatePhysics();

		if (DeliveryItem->GetDestinationID() == m_DestinationID)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("Item Delivered to Correct Destination!"));
			GameMode->GetAirShip()->OnItemDelivered();
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("Item Delivered to Incorrect Destination!"));
			GameMode->GetAirShip()->OnItemLost();
		}
	}
}

void ADeliveryDestination::OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}
