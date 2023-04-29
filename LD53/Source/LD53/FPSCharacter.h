// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "FPSCharacter.generated.h"

class UCameraComponent;
class UPhysicsConstraintComponent;
class UStaticMeshComponent;
class ASteeringWheel;
class AAltitudeLever;
class APickUppable;

UCLASS()
class LD53_API AFPSCharacter : public ACharacter
{
	GENERATED_BODY()

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Interact Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* InteractAction;

	/** Interact Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ThrowAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, Category = "Members")
	float MaxTraceDistance = 100.0f;

	UPROPERTY(EditAnywhere, Category = "Members")
	float ObjectThrowImpulse = 100000.0f;

private:
	APickUppable* m_PickedUpObject = nullptr;
	ASteeringWheel* m_SteeringWheel = nullptr;
	AAltitudeLever* m_AltitudeLever = nullptr;
	AActor* m_HitActor = nullptr;
	FVector m_HitPoint = FVector::ZeroVector;
	UStaticMeshComponent* m_GrabSlotMesh = nullptr;
	UPhysicsConstraintComponent* m_GrabConstraint = nullptr;

public:
	// Sets default values for this character's properties
	AFPSCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Called for interact input */
	void Interact();

	/** Called for throw input */
	void Throw();

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void CheckForInteractableActor();
	void GrabObject();
	void DropObject();
};
