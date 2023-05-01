// Fill out your copyright notice in the Description page of Project Settings.


#include "Sail.h"

// Sets default values
ASail::ASail()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASail::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASail::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

