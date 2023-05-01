// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/StaticMesh.h"
#include "AirShip.generated.h"

class AAltitudeLeverHinge;
class ARudder;

UENUM(BlueprintType)
enum class EGameOverReason : uint8 {
	FellToDeath       UMETA(DisplayName = "Fell To Death"),
	ShipDestroyed     UMETA(DisplayName = "Ship Destroyed"),
	Completed         UMETA(DisplayName = "Completed"),
};

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
	float SailRotationSpeed = 1.0f;

	UPROPERTY(EditAnywhere, Category = "LD53")
	float MinSailEffectiveness = 0.25f;

	UPROPERTY(EditAnywhere, Category = "LD53")
	AActor* HeadingIndicator;

	UPROPERTY(EditAnywhere, Category = "LD53")
	AActor* WindHeadingIndicator;

	UPROPERTY(EditAnywhere, Category = "LD53")
	AActor* Sail;

	UPROPERTY(EditAnywhere, Category = "LD53")
	ARudder* Rudder;

	UPROPERTY(EditAnywhere, Category = "LD53")
	AAltitudeLeverHinge* AltitudeLeverHinge;

	UPROPERTY(EditAnywhere, Category = "LD53")
	int NumTotalDeliveryItems;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LD53", meta = (AllowPrivateAccess = "true"))
	class UGameOverUserWidget* GameOverMenu;

private:
	UStaticMeshComponent* m_Cube;
	float m_ActualSpeed = 0.0f;
	FTimerHandle m_PowerConsumptionTimerHandle;
	FTimerHandle m_ShipFaultTimerHandle;
	FTimerHandle m_WindDirectionChangeTimerHandle;
	TArray<AActor*> m_Engines;
	float m_ActualAltitude = 0.0f;
	float m_Power = 100.0f;
	float m_WindHeading = 0.0f;
	float m_SailRotation = 0.0f;
	int m_NumRemainingDeliveryItems = 0;
	int m_NumDeliveredItems = 0;
	int m_NumLostItems = 0;

	bool m_SetFire = false;

public:	
	// Sets default values for this actor's properties
	AAirShip();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float _DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "LD53")
	void UpdateTargetSpeed(float _speed);

	UFUNCTION(BlueprintCallable, Category = "LD53")
	void UpdateTargetHeading(float _heading);

	UFUNCTION(BlueprintCallable, Category = "LD53")
	void UpdateTargetAltitude(float _Altitude);

	UFUNCTION(BlueprintCallable, Category = "LD53")
	void UpdateTargetAltitudeNormalized(float _NormalizedAltitude);

	UFUNCTION(BlueprintCallable, Category = "LD53")
	void AddCoalPiece();

	UFUNCTION(BlueprintCallable, Category = "LD53")
	void RotateSail(float _Direction);

	UFUNCTION(BlueprintCallable, Category = "LD53")
	bool HasPower();

	UFUNCTION(BlueprintCallable, Category = "LD53")
	float GetSailEffectiveness();

	UFUNCTION(BlueprintCallable, Category = "LD53")
	float GetTargetAltitudeNormalized();

	UFUNCTION(BlueprintCallable, Category = "LD53")
	int GetNumRemainingDeliveryItems();

	UFUNCTION(BlueprintCallable, Category = "LD53")
	int GetNumDeliveredItems();

	UFUNCTION(BlueprintCallable, Category = "LD53")
	int GetNumTotalDeliveryItems();

	UFUNCTION(BlueprintCallable, Category = "LD53")
	void ShowGameOverScreen(EGameOverReason _Reason);

	UFUNCTION(BlueprintCallable, Category = "LD53")
	void OnItemDelivered();

	UFUNCTION(BlueprintCallable, Category = "LD53")
	void OnNoMoreItemsRemaining();

	UFUNCTION(BlueprintCallable, Category = "LD53")
	void OnItemLost();

private:
	void HandleHeading(float _DeltaTime);
	void HandleMovement(float _DeltaTime);
	void HandleAltitude(float _DeltaTime);
	void HandleWindHeading(float _DeltaTime);
	void OnConsumePower();
	void OnShipFaultGeneration();
	void OnWindDirectionChange();
};
