// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LD53GameMode.generated.h"

class AAirShip;

UCLASS(minimalapi)
class ALD53GameMode : public AGameModeBase
{
	GENERATED_BODY()

private:
	AAirShip* m_AirShip;

public:
	ALD53GameMode();
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	AAirShip* GetAirShip();
};



