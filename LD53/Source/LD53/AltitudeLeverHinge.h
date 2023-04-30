// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AltitudeLeverHinge.generated.h"

class AAirShip;

UCLASS()
class LD53_API AAltitudeLeverHinge : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "LD53")
	AAirShip* AirShip;

	UPROPERTY(EditAnywhere, Category = "LD53")
	float MaxLeverHalfAngle = 60.0f;

private:
	float m_TargetAngle = 0.0f;

public:	
	// Sets default values for this actor's properties
	AAltitudeLeverHinge();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "LD53 Altitude Lever Hinge")
	void MoveLever(float _amount);
};
