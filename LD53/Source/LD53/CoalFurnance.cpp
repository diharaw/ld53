// Fill out your copyright notice in the Description page of Project Settings.


#include "CoalFurnance.h"
#include "Components/BoxComponent.h"
#include "CoalPiece.h"
#include "AirShip.h"

// Sets default values
ACoalFurnance::ACoalFurnance()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACoalFurnance::BeginPlay()
{
	Super::BeginPlay();
	
	m_TriggerVolume = FindComponentByClass<UBoxComponent>();

	if (m_TriggerVolume)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Found Box Component"));

		m_TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &ACoalFurnance::OverlapBegin);
		m_TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &ACoalFurnance::OverlapEnd);
	}
}

// Called every frame
void ACoalFurnance::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACoalFurnance::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Overlapped!"));

	if (OtherActor->IsA<ACoalPiece>())
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Found Coal Piece"));

		if (AirShip)
			AirShip->AddCoalPiece();

		OtherActor->Destroy();
	}
}

void ACoalFurnance::OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}