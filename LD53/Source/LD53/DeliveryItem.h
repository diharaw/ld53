// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickUppable.h"
#include "DeliveryItem.generated.h"

class UMaterialInstanceDynamic;

UCLASS()
class LD53_API ADeliveryItem : public APickUppable
{
	GENERATED_BODY()

private:
	int m_DestinationID = 0;

public:
	UFUNCTION(BlueprintCallable, Category = "LD53 Altitude Lever")
	void AssignIDAndColor(int _ID, FColor _Color, UMaterial* _Material);

	UFUNCTION(BlueprintCallable, Category = "LD53 Altitude Lever")
	int GetDestinationID();
};
