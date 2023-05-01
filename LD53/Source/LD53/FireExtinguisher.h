// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickUppable.h"
#include "FireExtinguisher.generated.h"

UCLASS()
class LD53_API AFireExtinguisher : public APickUppable
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "LD53")
	float FireExtinguisherRate = 10.0f;

	UPROPERTY(EditAnywhere, Category = "LD53")
	AActor* Nozzle;

private:
	bool m_Active = false;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "LD53")
	void Activate();

	UFUNCTION(BlueprintCallable, Category = "LD53")
	void Deactivate();

private:
	void UseFireExtinguisher(float _DeltaTime);
};
