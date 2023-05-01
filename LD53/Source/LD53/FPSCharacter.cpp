// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "SteeringWheel.h"
#include "AltitudeLever.h"
#include "PickUppable.h"
#include "SailControlWheel.h"
#include "FireExtinguisher.h"
#include "Blueprint/UserWidget.h"

// Sets default values
AFPSCharacter::AFPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;
}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	m_GrabConstraint = FindComponentByClass<UPhysicsConstraintComponent>();
	m_GrabSlotMesh = FindComponentByClass<UStaticMeshComponent>();

	if (HUD)
		HUD->AddToViewport();
}

// Called every frame
void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckForInteractableActor();
}

// Called to bind functionality to input
void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Throw
		EnhancedInputComponent->BindAction(ThrowAction, ETriggerEvent::Started, this, &AFPSCharacter::Throw);
		EnhancedInputComponent->BindAction(ThrowAction, ETriggerEvent::Completed, this, &AFPSCharacter::ThrowRelease);

		//Pause
		EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Started, this, &AFPSCharacter::Pause);
		
		//Interacting
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &AFPSCharacter::Interact);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AFPSCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AFPSCharacter::Look);
	}
}

void AFPSCharacter::Interact()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Interact"));

	if (m_PickedUpObject)
	{
		DropObject();
		m_PickedUpObject = nullptr;

		if (m_FireExtinguisher)
		{
			m_FireExtinguisher->Deactivate();
			m_FireExtinguisher = nullptr;
		}
	}
	else if (m_SteeringWheel)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Exited Steering Mode"));
		m_SteeringWheel = nullptr;
	}
	else if (m_SailControlWheel)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Exited Sail Control Mode"));
		m_SailControlWheel = nullptr;
	}
	else if (m_AltitudeLever)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Exited Altitude Mode"));
		m_AltitudeLever = nullptr;
	}
	else
	{
		if (m_HitActor)
		{
			if (m_HitActor->IsA<ASteeringWheel>())
			{
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Entered Steering Mode"));
				m_SteeringWheel = Cast<ASteeringWheel>(m_HitActor);
			}
			else if (m_HitActor->IsA<ASailControlWheel>())
			{
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Entered Sail Control Mode"));
				m_SailControlWheel = Cast<ASailControlWheel>(m_HitActor);
			}
			else if (m_HitActor->IsA<AAltitudeLever>())
			{
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Entered Altitude Mode"));
				m_AltitudeLever = Cast<AAltitudeLever>(m_HitActor);
			}
			else if (m_HitActor->IsA<APickUppable>())
			{
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Entered Pick Up Mode"));
				m_PickedUpObject = Cast<APickUppable>(m_HitActor);
				GrabObject();

				if (m_HitActor->IsA<AFireExtinguisher>())
					m_FireExtinguisher = Cast<AFireExtinguisher>(m_HitActor);
			}
		}
	}
}

void AFPSCharacter::Throw()
{
	if (m_FireExtinguisher)
		m_FireExtinguisher->Activate();
	else if (m_PickedUpObject)
	{
		DropObject();
		m_PickedUpObject->Throw(FirstPersonCameraComponent->GetForwardVector() * ObjectThrowImpulse);
		m_PickedUpObject = nullptr;
	}
}

void AFPSCharacter::ThrowRelease()
{
	if (m_FireExtinguisher)
		m_FireExtinguisher->Deactivate();
}

void AFPSCharacter::Pause()
{
	GetWorld()->GetFirstPlayerController()->SetPause(true);
	GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeGameAndUI());
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);

	PauseMenu->AddToViewport();
}

void AFPSCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{ 
		if (!m_PickedUpObject)
		{
			if (m_SteeringWheel)
			{
				m_SteeringWheel->RotateWheel(MovementVector.X);
				return;
			}
			else if (m_SailControlWheel)
			{
				m_SailControlWheel->RotateWheel(MovementVector.X);
				return;
			}
			else if (m_AltitudeLever)
				return;
		}
		
		// add movement
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AFPSCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		if (m_AltitudeLever)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Altitude Offset: %f"), LookAxisVector.Y));
			m_AltitudeLever->MoveLever(-LookAxisVector.Y * 10.0f);
		}
		
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AFPSCharacter::CheckForInteractableActor()
{
	// FHitResult will hold all data returned by our line collision query
	FHitResult Hit;

	// We set up a line trace from our current location to a point 1000cm ahead of us
	FVector TraceStart = FirstPersonCameraComponent->GetComponentLocation();
	FVector TraceEnd = FirstPersonCameraComponent->GetComponentLocation() + FirstPersonCameraComponent->GetForwardVector() * MaxTraceDistance;

	// You can use FCollisionQueryParams to further configure the query
	// Here we add ourselves to the ignored list so we won't block the trace
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	// To run the query, you need a pointer to the current level, which you can get from an Actor with GetWorld()
	// UWorld()->LineTraceSingleByChannel runs a line trace and returns the first actor hit over the provided collision channel.
	GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, ECC_Pawn, QueryParams);

	//DrawDebugLine(GetWorld(), TraceStart, TraceEnd, Hit.bBlockingHit ? FColor::Blue : FColor::Red, false, -1.0f, 0, 1.0f);
	
	// If the trace hit something, bBlockingHit will be true,
	// and its fields will be filled with detailed info about what was hit
	if (Hit.bBlockingHit && IsValid(Hit.GetActor()))
	{
		m_HitPoint = Hit.ImpactPoint;
		m_HitActor = Hit.GetActor();
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Hit Actor: %s"), *Hit.GetActor()->GetName()));
	}
	else
	{
		m_HitPoint = FVector::ZeroVector;
		m_HitActor = nullptr;
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("No Hit Actor"));
	}
}

void AFPSCharacter::GrabObject()
{
	m_PickedUpObject->SetActorLocationAndRotation(m_GrabSlotMesh->GetComponentLocation(), m_GrabSlotMesh->GetComponentRotation(), false, nullptr, ETeleportType::TeleportPhysics);
	m_GrabConstraint->SetConstrainedComponents(m_GrabSlotMesh, "", m_PickedUpObject->GetMesh(), "");
	m_PickedUpObject->GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
}

void AFPSCharacter::DropObject()
{
	m_PickedUpObject->GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
	m_GrabConstraint->BreakConstraint();
}