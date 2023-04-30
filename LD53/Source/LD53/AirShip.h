// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/StaticMesh.h"
#include "AirShip.generated.h"

class AAltitudeLeverHinge;
class ARudder;

UCLASS()
class LD53_API AAirShip : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "LD53")
	float MaxAltitude = 500.0f;

	UPROPERTY(EditAnywhere, Category = "LD53")
	float MinAltitude = 100.0f;

	UPROPERTY(EditAnywhere, Category = "LD53")
	float TargetSpeed = 100.0f;

	UPROPERTY(EditAnywhere, Category = "LD53")
	float TargetHeading = 0.0f;

	UPROPERTY(EditAnywhere, Category = "LD53")
	float TargetAltitude = 0.0f;

	UPROPERTY(EditAnywhere, Category = "LD53")
	float PowerFromCoalPiece = 20.0f;

	UPROPERTY(EditAnywhere, Category = "LD53")
	float PowerConsumptionRate = 0.25f;

	UPROPERTY(EditAnywhere, Category = "LD53")
	float RateOfTurn = 0.25f;

	UPROPERTY(EditAnywhere, Category = "LD53")
	float RateOfClimb = 1.0f;

	UPROPERTY(EditAnywhere, Category = "LD53")
	float RateOfNoPowerDescent = 1.0f;

	UPROPERTY(EditAnywhere, Category = "LD53")
	float TimeBetweenWindDirectionChanges = 180.0f;

	UPROPERTY(EditAnywhere, Category = "LD53")
	float TimeBetweenShipFaults = 30.0f;

	UPROPERTY(EditAnywhere, Category = "LD53")
	float WindChangeProbability = 0.5f;

	UPROPERTY(EditAnywhere, Category = "LD53")
	AActor* HeadingIndicator;

	UPROPERTY(EditAnywhere, Category = "LD53")
	AActor* WindHeadingIndicator;

	UPROPERTY(EditAnywhere, Category = "LD53")
	ARudder* Rudder;

	UPROPERTY(EditAnywhere, Category = "LD53")
	AAltitudeLeverHinge* AltitudeLeverHinge;

private:
	UStaticMeshComponent* m_Cube;
	float m_ActualSpeed = 0.0f;
	FTimerHandle m_PowerConsumptionTimerHandle;
	FTimerHandle m_ShipFaultTimerHandle;
	FTimerHandle m_WindDirectionChangeTimerHandle;
	float m_ActualAltitude = 0.0f;
	float m_Power = 100.0f;
	float m_WindHeading = 0.0f;

public:	
	// Sets default values for this actor's properties
	AAirShip();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "LD53 AirShip")
	void UpdateTargetSpeed(float _speed);

	UFUNCTION(BlueprintCallable, Category = "LD53 AirShip")
	void UpdateTargetHeading(float _heading);

	UFUNCTION(BlueprintCallable, Category = "LD53 AirShip")
	void UpdateTargetAltitude(float _Altitude);

	UFUNCTION(BlueprintCallable, Category = "LD53 AirShip")
	void UpdateTargetAltitudeNormalized(float _NormalizedAltitude);

	UFUNCTION(BlueprintCallable, Category = "LD53 AirShip")
	void AddCoalPiece();

	UFUNCTION(BlueprintCallable, Category = "LD53 AirShip")
	bool HasPower();

	float GetTargetAltitudeNormalized();

private:
	void HandleHeading(float _deltaTime);
	void HandleMovement(float _deltaTime);
	void HandleAltitude(float _deltaTime);
	void HandleWindHeading(float _deltaTime);
	void OnConsumePower();
	void OnShipFaultGeneration();
	void OnWindDirectionChange();
};
