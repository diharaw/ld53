// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SailControlWheel.generated.h"

UCLASS()
class LD53_API ASailControlWheel : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "LD53")
	float Rate = 100.0f;

	UPROPERTY(EditAnywhere, Category = "LD53")
	class AAirShip* AirShip;

private:
	float m_Rotation = 0.0f;

public:	
	// Sets default values for this actor's properties
	ASailControlWheel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "LD53")
	void RotateWheel(float _direction);
};
