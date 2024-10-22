// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SteeringWheel.generated.h"

class AAirShip;

UCLASS()
class LD53_API ASteeringWheel : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "LD53")
	float Rotation = 0.0f;

	UPROPERTY(EditAnywhere, Category = "LD53")
	float Rate = 100.0f;

private:
	AAirShip* m_AirShip = nullptr;

public:	
	// Sets default values for this actor's properties
	ASteeringWheel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "LD53")
	void RotateWheel(float _direction);
};
