// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickUppable.generated.h"

class UStaticMeshComponent;

UCLASS()
class LD53_API APickUppable : public AActor
{
	GENERATED_BODY()
	
protected:
	UStaticMeshComponent* m_Mesh = nullptr;

public:	
	// Sets default values for this actor's properties
	APickUppable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "LD53 PickUppable")
	UStaticMeshComponent* GetMesh();

	UFUNCTION(BlueprintCallable, Category = "LD53 PickUppable")
	void Throw(FVector _Impulse);
};
