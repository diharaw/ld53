// Copyright Epic Games, Inc. All Rights Reserved.

#include "LD53GameMode.h"
#include "LD53Character.h"
#include "AirShip.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

ALD53GameMode::ALD53GameMode() : Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/LD53/Blueprints/BP_FPSCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}

void ALD53GameMode::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> AirShips;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAirShip::StaticClass(), AirShips);

	if (AirShips.Num() > 0)
		m_AirShip = Cast<AAirShip>(AirShips[0]);
}

AAirShip* ALD53GameMode::GetAirShip()
{
	return m_AirShip;
}