// Fill out your copyright notice in the Description page of Project Settings.


#include "AirShip.h"
#include "Rudder.h"

// Sets default values
AAirShip::AAirShip()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAirShip::BeginPlay()
{
	Super::BeginPlay();
	
	//m_Cube = FindComponentByClass< UStaticMeshComponent>();
}

// Called every frame
void AAirShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	HandleHeading(DeltaTime);
	HandleAltitude(DeltaTime);
	HandleMovement(DeltaTime);
}

void AAirShip::UpdateTargetSpeed(float _speed)
{
	TargetSpeed = _speed;
}

void AAirShip::UpdateTargetHeading(float _heading)
{
	TargetHeading = _heading;
}

void AAirShip::UpdateTargetAltitude(float _Altitude)
{
	TargetAltitude = _Altitude;
}

void AAirShip::UpdateTargetAltitudeNormalized(float _NormalizedAltitude)
{
	TargetAltitude = MinAltitude + _NormalizedAltitude * (MaxAltitude - MinAltitude);
}

float AAirShip::GetTargetAltitudeNormalized()
{
	return (TargetAltitude - MinAltitude) / (MaxAltitude - MinAltitude);
}

void AAirShip::HandleHeading(float _deltaTime)
{
	m_TargetHeadingRot = FRotator(0.0f, TargetHeading, 0.0f);

	FRotator rotation = GetActorRotation();

	rotation = FRotator(FQuat::Slerp(rotation.Quaternion(), m_TargetHeadingRot.Quaternion(), _deltaTime));

	SetActorRotation(rotation);

	if (HeadingIndicator)
	{
		FRotator headingRotation = HeadingIndicator->GetActorRotation();

		headingRotation.Yaw = TargetHeading;

		HeadingIndicator->SetActorRotation(headingRotation);
	}

	if (Rudder)
	{
		FRotator rudderRotation = FRotator(0.0f, FMath::Clamp(-TargetHeading, -60.0f, 60.0f), 0.0f);

		Rudder->SetActorRelativeRotation(rudderRotation);
	}
}

void AAirShip::HandleMovement(float _deltaTime)
{
	m_ActualSpeed = FMath::Lerp(m_ActualSpeed, TargetSpeed, _deltaTime);

	FVector position = GetActorLocation();

	position += GetActorForwardVector() * m_ActualSpeed * _deltaTime;

	SetActorLocation(position);
}

void AAirShip::HandleAltitude(float _deltaTime)
{
	m_ActualAltitude = FMath::Lerp(m_ActualAltitude, TargetAltitude, _deltaTime);

	FVector position = GetActorLocation();

	position.Z = m_ActualAltitude;

	SetActorLocation(position);
}
