// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacle.h"
#include "AirShip.h"
#include "Components/SphereComponent.h"

// Sets default values
AObstacle::AObstacle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AObstacle::BeginPlay()
{
	Super::BeginPlay();

	m_TriggerVolume = FindComponentByClass<USphereComponent>();

	if (m_TriggerVolume)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Found Box Component"));

		m_TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &AObstacle::OverlapBegin);
		m_TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &AObstacle::OverlapEnd);
	}
}

// Called every frame
void AObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AObstacle::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA<AAirShip>())
	{
		AAirShip* AirShip = Cast<AAirShip>(OtherActor);
		AirShip->ShowGameOverScreen(EGameOverReason::ShipDestroyed);
	}
}

void AObstacle::OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

