// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AirShipEngine.generated.h"

class AAirShipEnginePanel;

UCLASS()
class LD53_API AAirShipEngine : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "LD53")
	TArray<AAirShipEnginePanel*> Panels;

	UPROPERTY(EditAnywhere, Category = "LD53")
	float FireDamageRate = 5.0f;

private:
	float m_Health = 100.0f;
	int m_NumFires = 0;
	TArray<AAirShipEnginePanel*> m_Panels;

public:	
	// Sets default values for this actor's properties
	AAirShipEngine();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "LD53 Altitude Lever")
	void DoFireDamage();

	UFUNCTION(BlueprintCallable, Category = "LD53 Altitude Lever")
	void SetOnFire();

	UFUNCTION(BlueprintCallable, Category = "LD53 Altitude Lever")
	void OnFireExtinguished();
};
