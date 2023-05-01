// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AltitudeLever.generated.h"

class AAltitudeLeverHinge;

UCLASS()
class LD53_API AAltitudeLever : public AActor
{
	GENERATED_BODY()

private:
	AAltitudeLeverHinge* m_AltitudeLeverHinge = nullptr;

public:	
	// Sets default values for this actor's properties
	AAltitudeLever();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "LD53 Altitude Lever")
	void MoveLever(float _amount);
};
