// Fill out your copyright notice in the Description page of Project Settings.


#include "SailControlWheel.h"
#include "AirShip.h"

// Sets default values
ASailControlWheel::ASailControlWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASailControlWheel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASailControlWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator rotation = GetActorRotation();

	rotation.Yaw = m_Rotation;

	SetActorRelativeRotation(rotation);
}

void ASailControlWheel::RotateWheel(float _direction)
{
	m_Rotation += (_direction * Rate * GetWorld()->DeltaTimeSeconds);

	if (AirShip)
		AirShip->RotateSail(_direction);
}
