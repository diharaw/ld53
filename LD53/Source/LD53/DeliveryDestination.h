// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DeliveryDestination.generated.h"

UCLASS()
class LD53_API ADeliveryDestination : public AActor
{
	GENERATED_BODY()

private:
	int m_DestinationID = 0;
	class UStaticMeshComponent* m_Mesh = nullptr;
	class UBoxComponent* m_TriggerVolume = nullptr;

public:	
	// Sets default values for this actor's properties
	ADeliveryDestination();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "LD53 Altitude Lever")
	void AssignIDAndColor(int _ID, FColor _Color, UMaterialInstance* _Material);

	UFUNCTION(BlueprintCallable, Category = "LD53 Altitude Lever")
	int GetDestinationID();

private:
	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
