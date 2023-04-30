// Fill out your copyright notice in the Description page of Project Settings.


#include "AirShip.h"
#include "Rudder.h"

float GetAngleDifferenceClockwise(float from, float to)
{
	float diff = fmod(from - to, 360.0); // diff now in (-360.0 ... 360.0) range
	if (diff >= 180.0) diff -= 360.0;     // diff now in (-360.0 ... 180.0) range
	else if (diff < -180.0) diff += 360.0;// diff now in [-180.0 ... 180.0) range
	return diff;
}

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
	
	GetWorld()->GetTimerManager().SetTimer(m_PowerConsumptionTimerHandle, this, &AAirShip::OnConsumePower, 1.0f, true);
	GetWorld()->GetTimerManager().SetTimer(m_WindDirectionChangeTimerHandle, this, &AAirShip::OnWindDirectionChange, TimeBetweenWindDirectionChanges, true);
	GetWorld()->GetTimerManager().SetTimer(m_ShipFaultTimerHandle, this, &AAirShip::OnShipFaultGeneration, TimeBetweenShipFaults, true);
}

void AAirShip::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorld()->GetTimerManager().ClearTimer(m_PowerConsumptionTimerHandle);
	GetWorld()->GetTimerManager().ClearTimer(m_WindDirectionChangeTimerHandle);
	GetWorld()->GetTimerManager().ClearTimer(m_ShipFaultTimerHandle);
	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
}

// Called every frame
void AAirShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	HandleHeading(DeltaTime);
	HandleAltitude(DeltaTime);
	HandleMovement(DeltaTime);
	HandleWindHeading(DeltaTime);
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

void AAirShip::AddCoalPiece()
{
	m_Power += PowerFromCoalPiece;
	m_Power = FMath::Clamp(m_Power, 0.0f, 100.0f);

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Added Coal Piece: %f"), m_Power));
}

void AAirShip::RotateSail(float _Direction)
{
	if (Sail)
	{
		m_SailRotation += GetWorld()->GetDeltaSeconds() * _Direction * SailRotationSpeed;

		FRotator SailRotation = FRotator(0.0f, m_SailRotation, 0.0f);

		Sail->SetActorRelativeRotation(SailRotation.Quaternion());
	}
}

bool AAirShip::HasPower()
{
	return m_Power > 0.0f;
}

float AAirShip::GetSailEffectiveness()
{
	//FVector WindDirection = FVector(m_WindHeading)
	return 0.0f;
}

float AAirShip::GetTargetAltitudeNormalized()
{
	return (TargetAltitude - MinAltitude) / (MaxAltitude - MinAltitude);
}

void AAirShip::HandleHeading(float _deltaTime)
{
	FRotator ShipRotation = GetActorRotation();

	float ActualTargetHeading = HasPower() ? TargetHeading : ShipRotation.Yaw;
	FRotator TargetHeadingRot = FRotator(0.0f, ActualTargetHeading, 0.0f);

	FRotator FinalRotation = FRotator(FQuat::Slerp(ShipRotation.Quaternion(), TargetHeadingRot.Quaternion(), _deltaTime * RateOfTurn));

	SetActorRotation(FinalRotation);

	if (HeadingIndicator)
	{
		FRotator headingRotation = HeadingIndicator->GetActorRotation();

		headingRotation.Yaw = TargetHeading;

		HeadingIndicator->SetActorRotation(headingRotation);
	}

	if (Rudder)
	{
		float diff = GetAngleDifferenceClockwise(ActualTargetHeading, FinalRotation.Yaw);

		FRotator rudderRotation = FRotator(0.0f, FMath::Clamp(-diff, -60.0f, 60.0f), 0.0f);

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
	float ActualRateOfClimb = HasPower() ? RateOfClimb : RateOfNoPowerDescent;
	float ActualTargetAltitude = HasPower() ? TargetAltitude : 0.0f;

	m_ActualAltitude = FMath::Lerp(m_ActualAltitude, ActualTargetAltitude, _deltaTime * ActualRateOfClimb);

	FVector position = GetActorLocation();

	position.Z = m_ActualAltitude;

	SetActorLocation(position);
}

void AAirShip::HandleWindHeading(float _deltaTime)
{
	if (WindHeadingIndicator)
	{
		FRotator WindHeadingRotation = WindHeadingIndicator->GetActorRotation();
		FRotator TargetWindHeadingRotation = FRotator(0.0f, m_WindHeading, 0.0f);

		FRotator FinalRotation = FRotator(FQuat::Slerp(WindHeadingRotation.Quaternion(), TargetWindHeadingRotation.Quaternion(), _deltaTime));

		WindHeadingIndicator->SetActorRotation(FinalRotation);
	}
}

void AAirShip::OnConsumePower()
{
	m_Power -= PowerConsumptionRate;
	m_Power = FMath::Clamp(m_Power, 0.0f, 100.0f);

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Ship Power: %f"), m_Power));
}

void AAirShip::OnShipFaultGeneration()
{

}

void AAirShip::OnWindDirectionChange()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Current Wind Heading: %f Degrees"), m_WindHeading));

	if (FMath::RandRange(0.0f, 1.0f) < WindChangeProbability)
	{
		m_WindHeading = FMath::RandRange(0.0f, 359.0f);
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Wind Heading Changed: %f Degrees"), m_WindHeading));
	}
}