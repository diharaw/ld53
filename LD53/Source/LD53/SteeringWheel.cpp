// Fill out your copyright notice in the Description page of Project Settings.


#include "SteeringWheel.h"
#include "AirShip.h"

// Sets default values
ASteeringWheel::ASteeringWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASteeringWheel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASteeringWheel::Tick(float DeltaTime)
{
	FRotator rotation = GetActorRotation();

	rotation.Roll = Rotation;
	
	SetActorRotation(rotation);
}

void ASteeringWheel::RotateWheel(float _direction)
{
	Rotation += (_direction * Rate * GetWorld()->DeltaTimeSeconds);
	
	// Set target heading on AirShip
	if (AirShip)
		AirShip->UpdateTargetHeading(Rotation);
}
