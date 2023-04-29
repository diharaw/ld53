// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUppable.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
APickUppable::APickUppable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APickUppable::BeginPlay()
{
	Super::BeginPlay();
	
	m_Mesh = FindComponentByClass<UStaticMeshComponent>();
}

// Called every frame
void APickUppable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UStaticMeshComponent* APickUppable::GetMesh()
{
	return m_Mesh;
}

void APickUppable::Throw(FVector _Impulse)
{
	if (m_Mesh)
		m_Mesh->AddImpulse(_Impulse);
}