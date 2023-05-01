// Fill out your copyright notice in the Description page of Project Settings.


#include "KillBox.h"
#include "Components/BoxComponent.h"
#include "CoalPiece.h"
#include "DeliveryItem.h"
#include "CoalSpawner.h"
#include "AirShip.h"
#include "FPSCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AKillBox::AKillBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AKillBox::BeginPlay()
{
	Super::BeginPlay();

	m_TriggerVolume = FindComponentByClass<UBoxComponent>();

	if (m_TriggerVolume)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Found Box Component"));

		m_TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &AKillBox::OverlapBegin);
		m_TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &AKillBox::OverlapEnd);
	}

	TArray<AActor*> AirShips;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAirShip::StaticClass(), AirShips);

	TArray<AActor*> CoalSpawners;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACoalSpawner::StaticClass(), CoalSpawners);

	if (AirShips.Num() > 0)
		m_AirShip = Cast<AAirShip>(AirShips[0]);

	if (CoalSpawners.Num() > 0)
		m_CoalSpawner = Cast<ACoalSpawner>(CoalSpawners[0]);
}

// Called every frame
void AKillBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AKillBox::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Overlapped!"));

	if (OtherActor->IsA<ACoalPiece>())
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Coal Piece Killed Off"));

		OtherActor->Destroy();

		if (m_CoalSpawner)
			m_CoalSpawner->DecreaseNumCoalChunks();
	}
	else if (OtherActor->IsA<AFPSCharacter>())
	{
		m_AirShip->ShowGameOverScreen(EGameOverReason::FellToDeath);
	}
	else if (OtherActor->IsA<AAirShip>())
	{
		m_AirShip->ShowGameOverScreen(EGameOverReason::ShipDestroyed);
	}
	else if (OtherActor->IsA<ADeliveryItem>())
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Delivery Item Killed Off"));

		OtherActor->Destroy();

		m_AirShip->OnItemLost();
	}
}

void AKillBox::OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}