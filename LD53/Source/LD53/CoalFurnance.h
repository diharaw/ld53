// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CoalFurnance.generated.h"

UCLASS()
class LD53_API ACoalFurnance : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Members")
	class AAirShip* AirShip;

private:
	class UBoxComponent* m_TriggerVolume = nullptr;
	
public:	
	// Sets default values for this actor's properties
	ACoalFurnance();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
