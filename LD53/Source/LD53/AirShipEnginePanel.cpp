// Fill out your copyright notice in the Description page of Project Settings.


#include "AirShipEnginePanel.h"
#include "AirShipEngine.h"

// Sets default values
AAirShipEnginePanel::AAirShipEnginePanel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAirShipEnginePanel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAirShipEnginePanel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_FireHealth > 0.0f && m_AirShipEngine)
		m_AirShipEngine->DoFireDamage();
}

void AAirShipEnginePanel::SetOnFire(AAirShipEngine* _AirShipEngine)
{
	m_AirShipEngine = _AirShipEngine;
	m_FireHealth = 100.0f;
}

void AAirShipEnginePanel::DoFireExtinguish(float _Amount)
{
	if (m_FireHealth > 0.0f)
	{
		m_FireHealth -= _Amount;

		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("Fire Health: %f"), m_FireHealth));

		if (m_FireHealth <= 0.0f)
		{
			m_FireHealth = 0.0f;

			if (m_AirShipEngine)
				m_AirShipEngine->OnFireExtinguished();
		}
	}
}