// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AirShipEnginePanel.generated.h"

UCLASS()
class LD53_API AAirShipEnginePanel : public AActor
{
	GENERATED_BODY()

private:
	float m_FireHealth = 0.0f;
	class AAirShipEngine* m_AirShipEngine = nullptr;

public:	
	// Sets default values for this actor's properties
	AAirShipEnginePanel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "LD53 Altitude Lever")
	void SetOnFire(AAirShipEngine* _AirShipEngine);

	UFUNCTION(BlueprintCallable, Category = "LD53 Altitude Lever")
	void DoFireExtinguish(float _Amount);
};
