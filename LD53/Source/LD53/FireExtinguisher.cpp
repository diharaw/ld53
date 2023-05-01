// Fill out your copyright notice in the Description page of Project Settings.


#include "FireExtinguisher.h"
#include "AirShipEnginePanel.h"

void AFireExtinguisher::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_Active)
		UseFireExtinguisher(DeltaTime);
}

void AFireExtinguisher::Activate()
{
	m_Active = true;
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Fire Extinguisher Active"));
}

void AFireExtinguisher::Deactivate()
{
	m_Active = false;
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Fire Extinguisher Inactive"));
}

void AFireExtinguisher::UseFireExtinguisher(float _DeltaTime)
{
	//if (Nozzle)
	{
		// FHitResult will hold all data returned by our line collision query
		FHitResult Hit;

		// We set up a line trace from our current location to a point 1000cm ahead of us
		FVector TraceStart = GetActorLocation();
		FVector TraceEnd = GetActorLocation() + GetActorForwardVector() * 1000.0f;

		// You can use FCollisionQueryParams to further configure the query
		// Here we add ourselves to the ignored list so we won't block the trace
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(this);

		// To run the query, you need a pointer to the current level, which you can get from an Actor with GetWorld()
		// UWorld()->LineTraceSingleByChannel runs a line trace and returns the first actor hit over the provided collision channel.
		GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, ECC_Pawn, QueryParams);

		DrawDebugLine(GetWorld(), TraceStart, TraceEnd, Hit.bBlockingHit ? FColor::Green : FColor::Yellow, false, -1.0f, 0, 10.0f);

		// If the trace hit something, bBlockingHit will be true,
		// and its fields will be filled with detailed info about what was hit
		if (Hit.bBlockingHit && IsValid(Hit.GetActor()))
		{
			if (Hit.GetActor()->IsA<AAirShipEnginePanel>())
			{
				AAirShipEnginePanel* EnginePanel = Cast<AAirShipEnginePanel>(Hit.GetActor());
				EnginePanel->DoFireExtinguish(FireExtinguisherRate * _DeltaTime);
			}
		}
	}
}