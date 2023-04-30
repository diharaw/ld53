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

	UPROPERTY(EditAnywhere, Category = "Members")
	float MaxAltitude = 500.0f;

	UPROPERTY(EditAnywhere, Category = "Members")
	float MinAltitude = 100.0f;

	UPROPERTY(EditAnywhere, Category = "Members")
	float TargetSpeed = 100.0f;

	UPROPERTY(EditAnywhere, Category = "Members")
	float TargetHeading = 0.0f;

	UPROPERTY(EditAnywhere, Category = "Members")
	float TargetAltitude = 0.0f;

	UPROPERTY(EditAnywhere, Category = "Members")
	float PowerFromCoalPiece = 20.0f;

	UPROPERTY(EditAnywhere, Category = "Members")
	float PowerConsumptionRate = 5.0f;

	UPROPERTY(EditAnywhere, Category = "Members")
	AActor* HeadingIndicator;

	UPROPERTY(EditAnywhere, Category = "Members")
	ARudder* Rudder;

	UPROPERTY(EditAnywhere, Category = "Members")
	AAltitudeLeverHinge* AltitudeLeverHinge;

private:
	UStaticMeshComponent* m_Cube;
	float m_ActualSpeed = 0.0f;
	FRotator m_TargetHeadingRot;
	float m_ActualAltitude = 0.0f;
	float m_Power = 100.0f;

public:	
	// Sets default values for this actor's properties
	AAirShip();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

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

	float GetTargetAltitudeNormalized();

private:
	void HandleHeading(float _deltaTime);
	void HandleMovement(float _deltaTime);
	void HandleAltitude(float _deltaTime);
	void ConsumePower();
};
