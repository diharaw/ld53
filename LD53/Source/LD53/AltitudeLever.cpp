// Fill out your copyright notice in the Description page of Project Settings.


#include "AltitudeLever.h"
#include "AltitudeLeverHinge.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AAltitudeLever::AAltitudeLever()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAltitudeLever::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<AActor*> Hinges;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAltitudeLeverHinge::StaticClass(), Hinges);

	if (Hinges.Num() > 0)
		m_AltitudeLeverHinge = Cast<AAltitudeLeverHinge>(Hinges[0]);

}

// Called every frame
void AAltitudeLever::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAltitudeLever::MoveLever(float _amount)
{
	if (m_AltitudeLeverHinge)
		m_AltitudeLeverHinge->MoveLever(_amount);
}