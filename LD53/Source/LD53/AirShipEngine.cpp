// Fill out your copyright notice in the Description page of Project Settings.


#include "AirShipEngine.h"
#include "AirShipEnginePanel.h"

// Sets default values
AAirShipEngine::AAirShipEngine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAirShipEngine::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAirShipEngine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAirShipEngine::DoFireDamage()
{
	m_Health -= FireDamageRate * GetWorld()->GetDeltaSeconds();

	if (m_Health <= 0.0f)
	{
		
	}
}

void AAirShipEngine::SetOnFire()
{
	for (int i = 0; i < Panels.Num(); i++)
	{
		if (i == 0)
		{
			Panels[i]->SetOnFire(this);
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("Engine On Fire!"));
			m_NumFires++;
		}
		else
		{
			if (FMath::RandRange(0.0f, 1.0f) < 0.5f)
			{
				Panels[i]->SetOnFire(this);
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("Engine On Fire!"));
				m_NumFires++;
			}
		}
	}
}

void AAirShipEngine::OnFireExtinguished()
{
	if (m_NumFires > 0)
	{
		m_NumFires--;

		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("Fire Put Out!"));

		if (m_NumFires == 0)
		{
			m_Health = 100.0f;
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("All Fires Put Out!"));
			// TODO: fault solved
		}
	}
}