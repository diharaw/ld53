// Fill out your copyright notice in the Description page of Project Settings.


#include "AltitudeLeverHinge.h"
#include "AirShip.h"

// Sets default values
AAltitudeLeverHinge::AAltitudeLeverHinge()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAltitudeLeverHinge::BeginPlay()
{
	Super::BeginPlay();

	if (AirShip)
	{
		m_TargetAngle = -(2.0f * AirShip->GetTargetAltitudeNormalized() - 1.0f) * MaxLeverHalfAngle;
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Initial Target Angle: %f"), m_TargetAngle));

		FRotator TargetRotation = FRotator(m_TargetAngle, 0.0f, 0.0f);
		SetActorRelativeRotation(TargetRotation);
	}
}

// Called every frame
void AAltitudeLeverHinge::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//MoveLever(DeltaTime * 5.0f);
}

void AAltitudeLeverHinge::MoveLever(float _amount)
{
	if (AirShip)
	{
		m_TargetAngle -= _amount;
		m_TargetAngle = FMath::Clamp(m_TargetAngle, -MaxLeverHalfAngle, MaxLeverHalfAngle);

		FRotator TargetRotation = FRotator(m_TargetAngle, 0.0f, 0.0f);
		SetActorRelativeRotation(TargetRotation);

		AirShip->UpdateTargetAltitudeNormalized(1.0f - (m_TargetAngle + MaxLeverHalfAngle) / (MaxLeverHalfAngle * 2.0f));
	}
}