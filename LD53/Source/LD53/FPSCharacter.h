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
class ASailControlWheel;
class AAltitudeLever;
class APickUppable;
class AFireExtinguisher;

UCLASS()
class LD53_API AFPSCharacter : public ACharacter
{
	GENERATED_BODY()

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LD53", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LD53", meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LD53", meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LD53", meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Interact Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LD53", meta = (AllowPrivateAccess = "true"))
	class UInputAction* InteractAction;

	/** Interact Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LD53", meta = (AllowPrivateAccess = "true"))
	class UInputAction* ThrowAction;

	/** Pause Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LD53", meta = (AllowPrivateAccess = "true"))
	class UInputAction* PauseAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LD53", meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LD53", meta = (AllowPrivateAccess = "true"))
	UUserWidget* PauseMenu;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LD53", meta = (AllowPrivateAccess = "true"))
	class UHUDUserWidget* InGameHUD;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LD53", meta = (AllowPrivateAccess = "true"))
	class USoundCue* FootstepsCue;

	UPROPERTY(EditAnywhere, Category = "LD53")
	float MaxTraceDistance = 100.0f;

	UPROPERTY(EditAnywhere, Category = "LD53")
	float ObjectThrowImpulse = 100000.0f;

private:
	APickUppable* m_PickedUpObject = nullptr;
	ASteeringWheel* m_SteeringWheel = nullptr;
	ASailControlWheel* m_SailControlWheel = nullptr;
	AFireExtinguisher* m_FireExtinguisher = nullptr;
	AAltitudeLever* m_AltitudeLever = nullptr;
	AActor* m_HitActor = nullptr;
	FVector m_HitPoint = FVector::ZeroVector;
	UStaticMeshComponent* m_GrabSlotMesh = nullptr;
	UPhysicsConstraintComponent* m_GrabConstraint = nullptr;
	UAudioComponent* m_AudioComponent = nullptr;
	bool m_IsMoving = false;

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

	/** Called for throw input */
	void ThrowRelease();

	/** Called for pause input */
	void Pause();

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	void MoveStarted();
	void MoveEnded();

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

	void ShowGrabPrompt();
	void ShowDropPrompt();
	void ShowLetGoPrompt();
	void ShowRepairPrompt();
	void ShowThrowPrompt();
	void ShowUsePrompt();
	void HidePrimaryPrompt();
	void HideSecondaryPrompt();
};
