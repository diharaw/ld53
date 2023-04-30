// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickUppable.h"
#include "DeliveryItem.generated.h"

UCLASS()
class LD53_API ADeliveryItem : public APickUppable
{
	GENERATED_BODY()

public:
	int DestinationID = 0;
};
