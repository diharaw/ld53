// Fill out your copyright notice in the Description page of Project Settings.


#include "AirShip.h"
#include "Rudder.h"
#include "AirShipEngine.h"
#include "Sail.h"
#include "Kismet/GameplayStatics.h"
#include "GameOverUserWidget.h"
#include "AltitudeLeverHinge.h"
#include "HeadingIndicator.h"
#include "WindHeadingIndicator.h"
#include "HUDUserWidget.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"

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

	m_NumRemainingDeliveryItems = NumTotalDeliveryItems;
	
	GetWorld()->GetTimerManager().SetTimer(m_PowerConsumptionTimerHandle, this, &AAirShip::OnConsumePower, 1.0f, true);
	GetWorld()->GetTimerManager().SetTimer(m_WindDirectionChangeTimerHandle, this, &AAirShip::OnWindDirectionChange, TimeBetweenWindDirectionChanges, true);
	GetWorld()->GetTimerManager().SetTimer(m_ShipFaultTimerHandle, this, &AAirShip::OnShipFaultGeneration, TimeBetweenShipFaults, true);

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAirShipEngine::StaticClass(), m_Engines);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASail::StaticClass(), m_Sails);

	TArray<AActor*> Rudders;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARudder::StaticClass(), Rudders);

	if (Rudders.Num() > 0)
		m_Rudder = Cast<ARudder>(Rudders[0]);

	TArray<AActor*> Hinges;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAltitudeLeverHinge::StaticClass(), Hinges);

	if (Hinges.Num() > 0)
		m_AltitudeLeverHinge = Cast<AAltitudeLeverHinge>(Hinges[0]);

	TArray<AActor*> HeadingIndicators;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AHeadingIndicator::StaticClass(), HeadingIndicators);

	if (HeadingIndicators.Num() > 0)
		m_HeadingIndicator = Cast<AHeadingIndicator>(HeadingIndicators[0]);

	TArray<AActor*> WindHeadingIndicators;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWindHeadingIndicator::StaticClass(), WindHeadingIndicators);

	if (WindHeadingIndicators.Num() > 0)
		m_WindHeadingIndicator = Cast<AWindHeadingIndicator>(WindHeadingIndicators[0]);

	m_ActualAltitude = TargetAltitude;
	m_ActualSpeed = TargetSpeed;

	m_AudioComponent = FindComponentByClass<UAudioComponent>();
	m_AudioComponent->Stop();
}

void AAirShip::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorld()->GetTimerManager().ClearTimer(m_PowerConsumptionTimerHandle);
	//GetWorld()->GetTimerManager().ClearTimer(m_WindDirectionChangeTimerHandle);
	GetWorld()->GetTimerManager().ClearTimer(m_ShipFaultTimerHandle);
	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
}

// Called every frame
void AAirShip::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	HandleHeading(_DeltaTime);
	HandleAltitude(_DeltaTime);
	HandleMovement(_DeltaTime);
	//HandleWindHeading(_DeltaTime);
}

void AAirShip::SetHUD(UHUDUserWidget* _HUD)
{
	m_HUD = _HUD;
}

void AAirShip::UpdateTargetSpeed(float _Speed)
{
	TargetSpeed = _Speed;
}

void AAirShip::UpdateTargetHeading(float _Heading)
{
	TargetHeading = _Heading;
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

	if (m_AudioComponent->IsPlaying())
		m_AudioComponent->Stop();
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Added Coal Piece: %f"), m_Power));
}

void AAirShip::RotateSail(float _Direction)
{
	for (int i = 0 ; i < m_Sails.Num(); i++)
	{
		m_SailRotation += GetWorld()->GetDeltaSeconds() * _Direction * SailRotationSpeed;

		FRotator SailRotation = FRotator(0.0f, m_SailRotation, 0.0f);

		m_Sails[i]->SetActorRelativeRotation(SailRotation.Quaternion());
	}
}

bool AAirShip::HasPower()
{
	return m_Power > 0.0f;
}

float AAirShip::GetSailEffectiveness()
{
	float AngleBetween = FMath::Clamp(GetAngleDifferenceClockwise(m_WindHeading, m_SailRotation), 0.0f, 180.0f);
	return FMath::Clamp(1.0f - FMath::Abs(cos(FMath::DegreesToRadians(AngleBetween))), MinSailEffectiveness, 1.0f);
}

float AAirShip::GetTargetAltitudeNormalized()
{
	return (TargetAltitude - MinAltitude) / (MaxAltitude - MinAltitude);
}

int AAirShip::GetNumRemainingDeliveryItems()
{
	return m_NumRemainingDeliveryItems;
}

int AAirShip::GetNumDeliveredItems()
{
	return m_NumDeliveredItems;
}

int AAirShip::GetNumTotalDeliveryItems()
{
	return NumTotalDeliveryItems;
}

void AAirShip::ShowGameOverScreen(EGameOverReason _Reason)
{
	if (GameOverMenu)
	{
		GetWorld()->GetFirstPlayerController()->SetPause(true);
		GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeGameAndUI());
		GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);

		GameOverMenu->AddToViewport();

		FString ScoreText;

		if (_Reason == EGameOverReason::ShipDestroyed)
		{
			ScoreText = TEXT("Your Ship Was Destroyed!");
			GameOverMenu->HideContinueButton();
		}
		else if (_Reason == EGameOverReason::FellToDeath)
		{
			ScoreText = TEXT("You Fell To Your Death!");
			GameOverMenu->HideContinueButton();
		}
		else
		{
			ScoreText = FString::Printf(TEXT("Delivered %i out of %i Packages!"), GetNumDeliveredItems(), GetNumTotalDeliveryItems());
			//GameOverMenu->ShowContinueButton(1);
			GameOverMenu->HideContinueButton();
		}

		GameOverMenu->ShowScoreText(ScoreText);
	}
}

void AAirShip::OnItemDelivered()
{
	if (m_NumRemainingDeliveryItems > 0)
	{
		m_NumRemainingDeliveryItems--;
		m_NumDeliveredItems++;

		if (FailureCue)
		{
			UAudioComponent* AudioComponent = UGameplayStatics::SpawnSound2D(this, SuccessCue, 1.0f);

			if (AudioComponent)
				AudioComponent->Play();
		}

		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("Item Delivered! Remaining: %i"), m_NumRemainingDeliveryItems));

		if (m_NumRemainingDeliveryItems == 0)
			OnNoMoreItemsRemaining();
	}
}

void AAirShip::OnNoMoreItemsRemaining()
{
	ShowGameOverScreen(EGameOverReason::Completed);
}

void AAirShip::OnItemLost()
{
	if (m_NumRemainingDeliveryItems > 0)
	{
		m_NumRemainingDeliveryItems--;
		m_NumLostItems++;

		if (FailureCue)
		{
			UAudioComponent* AudioComponent = UGameplayStatics::SpawnSound2D(this, FailureCue, 1.0f);

			if (AudioComponent)
				AudioComponent->Play();
		}

		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("Item Lost! Remaining: %i"), m_NumRemainingDeliveryItems));

		if (m_NumRemainingDeliveryItems == 0)
			OnNoMoreItemsRemaining();
	}
}

void AAirShip::HandleHeading(float _DeltaTime)
{
	FRotator ShipRotation = GetActorRotation();

	float ActualTargetHeading = HasPower() ? TargetHeading : ShipRotation.Yaw;
	FRotator TargetHeadingRot = FRotator(0.0f, ActualTargetHeading, 0.0f);

	FRotator FinalRotation = FRotator(FQuat::Slerp(ShipRotation.Quaternion(), TargetHeadingRot.Quaternion(), _DeltaTime * RateOfTurn));

	SetActorRotation(FinalRotation);

	if (m_HeadingIndicator)
	{
		FRotator headingRotation = m_HeadingIndicator->GetActorRotation();

		headingRotation.Yaw = TargetHeading;

		m_HeadingIndicator->SetActorRotation(headingRotation);
	}

	if (m_Rudder)
	{
		float diff = GetAngleDifferenceClockwise(ActualTargetHeading, FinalRotation.Yaw);

		FRotator rudderRotation = FRotator(0.0f, FMath::Clamp(-diff, -60.0f, 60.0f), 0.0f);

		m_Rudder->SetActorRelativeRotation(rudderRotation);
	}
}

void AAirShip::HandleMovement(float _DeltaTime)
{
	m_ActualSpeed = FMath::Lerp(m_ActualSpeed, TargetSpeed, _DeltaTime);

	FVector position = GetActorLocation();

	position += GetActorForwardVector() * m_ActualSpeed * _DeltaTime;

	SetActorLocation(position);
}

void AAirShip::HandleAltitude(float _DeltaTime)
{
	float ActualRateOfClimb = HasPower() ? RateOfClimb : RateOfNoPowerDescent;
	float ActualTargetAltitude = HasPower() ? TargetAltitude : 0.0f;

	m_ActualAltitude = FMath::Lerp(m_ActualAltitude, ActualTargetAltitude, _DeltaTime * ActualRateOfClimb);

	FVector position = GetActorLocation();

	position.Z = m_ActualAltitude;

	SetActorLocation(position);
}

void AAirShip::HandleWindHeading(float _DeltaTime)
{
	if (m_WindHeadingIndicator)
	{
		FRotator WindHeadingRotation = m_WindHeadingIndicator->GetActorRotation();
		FRotator TargetWindHeadingRotation = FRotator(0.0f, m_WindHeading, 0.0f);

		FRotator FinalRotation = FRotator(FQuat::Slerp(WindHeadingRotation.Quaternion(), TargetWindHeadingRotation.Quaternion(), _DeltaTime));

		m_WindHeadingIndicator->SetActorRotation(FinalRotation);
	}
}

void AAirShip::OnConsumePower()
{
	m_Power -= PowerConsumptionRate;
	m_Power = FMath::Clamp(m_Power, 0.0f, 100.0f);

	if (m_Power == 0.0f)
	{
		if (m_HUD) { m_HUD->UpdatePowerLevelText(FString::Printf(TEXT("Ship Power: %f [Loosing Altitude]"), m_Power)); }

		if (!m_AudioComponent->IsPlaying())
			m_AudioComponent->Play();
	}
	else
		if (m_HUD) { m_HUD->UpdatePowerLevelText(FString::Printf(TEXT("Ship Power: %f"), m_Power)); }
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Ship Power: %f"), m_Power));
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Sail Effectiveness: %f"), GetSailEffectiveness()));
}

void AAirShip::OnShipFaultGeneration()
{

}

void AAirShip::OnWindDirectionChange()
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Current Wind Heading: %f Degrees"), m_WindHeading));

	if (FMath::RandRange(0.0f, 1.0f) < WindChangeProbability)
	{
		m_WindHeading = FMath::RandRange(0.0f, 359.0f);
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Wind Heading Changed: %f Degrees"), m_WindHeading));
	}
}