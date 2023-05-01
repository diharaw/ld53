// Fill out your copyright notice in the Description page of Project Settings.


#include "CoalFurnance.h"
#include "Components/BoxComponent.h"
#include "CoalPiece.h"
#include "CoalSpawner.h"
#include "AirShip.h"
#include "Kismet/GameplayStatics.h"

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

		if (m_AirShip)
			m_AirShip->AddCoalPiece();

		OtherActor->Destroy();

		if (m_CoalSpawner)
			m_CoalSpawner->DecreaseNumCoalChunks();
	}
}

void ACoalFurnance::OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}