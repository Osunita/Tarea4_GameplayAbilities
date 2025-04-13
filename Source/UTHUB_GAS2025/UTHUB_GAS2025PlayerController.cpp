// Copyright Epic Games, Inc. All Rights Reserved.

#include "UTHUB_GAS2025PlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "UTHUB_GAS2025Character.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "InputAbilityMapping.h"
#include "DataDriven/GASDataComponent.h"
#include "Engine/LocalPlayer.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

AUTHUB_GAS2025PlayerController::AUTHUB_GAS2025PlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.f;
}

void AUTHUB_GAS2025PlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
}

void AUTHUB_GAS2025PlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	UEnhancedInputComponent* EnhancedInputComponent =Cast<UEnhancedInputComponent>(InputComponent);
	UUTHUB_ASC* ASC = GetPawn()->FindComponentByClass<UUTHUB_ASC>();
	if(EnhancedInputComponent && ASC)
	{
		if(UGASDataComponent* DataComponent = GetPawn()->FindComponentByClass<UGASDataComponent>())
		{
			for(auto [InputAction, AbilityClass] : DataComponent->InputAbilityMapping->Mappings)
			{
				ASC->AddAbilityFromClass(AbilityClass);
				EnhancedInputComponent->BindAction(InputAction,ETriggerEvent::Started, this, &ThisClass::ExecuteAbility);
			}
		}
	}
}

void AUTHUB_GAS2025PlayerController::ExecuteAbility(const FInputActionInstance& InputActionInstance)
{
	UGASDataComponent* DataComponent = GetPawn()->FindComponentByClass<UGASDataComponent>();
	UUTHUB_ASC* ASC = GetPawn()->FindComponentByClass<UUTHUB_ASC>();
	
	if(DataComponent && ASC)
	{
		//auto Spec = ASC->FindAbilitySpecFromClass(DataComponent->DefaultAbility);
		//ASC->CancelAbility(Spec->Ability);
		const UInputAction* Action = InputActionInstance.GetSourceAction();
		

		ASC->TryActivateAbilityByClass(DataComponent->InputAbilityMapping->Mappings[Action]);
	}
}

void AUTHUB_GAS2025PlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent)) {
		EnhancedInputComponent->BindAction(
			MoveAction,
			ETriggerEvent::Triggered,
			this,
			&AUTHUB_GAS2025PlayerController::OnMove
		);
	}
}

void AUTHUB_GAS2025PlayerController::OnMove(const FInputActionValue& Value) {
	if (APawn* ControlledPawn = GetPawn()) {
		// Obtiene el vector de input (W, A, S, D)
		const FVector2D MovementVector = Value.Get<FVector2D>();

		// Calcula la dirección relativa a la cámara (usando su rotación)
		const FRotator CameraRotation = GetControlRotation();
		const FRotator YawRotation(0, CameraRotation.Yaw, 0); // Solo el eje Yaw

		// Forward/Right basados en la cámara
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// Aplica el movimiento al Character
		ControlledPawn->AddMovementInput(ForwardDirection, MovementVector.Y); // W/S (Y-axis)
		ControlledPawn->AddMovementInput(RightDirection, MovementVector.X); // A/D (X-axis)
	}
}

void AUTHUB_GAS2025PlayerController::OnInputStarted()
{
	StopMovement();
}

// Triggered every frame when the input is held down
void AUTHUB_GAS2025PlayerController::OnSetDestinationTriggered()
{
	// We flag that the input is being pressed
	FollowTime += GetWorld()->GetDeltaSeconds();
	
	// We look for the location in the world where the player has pressed the input
	FHitResult Hit;
	bool bHitSuccessful = false;
	if (bIsTouch)
	{
		bHitSuccessful = GetHitResultUnderFinger(ETouchIndex::Touch1, ECollisionChannel::ECC_Visibility, true, Hit);
	}
	else
	{
		bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	}

	// If we hit a surface, cache the location
	if (bHitSuccessful)
	{
		CachedDestination = Hit.Location;
	}
	
	// Move towards mouse pointer or touch
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn != nullptr)
	{
		FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
		ControlledPawn->AddMovementInput(WorldDirection, 1.0, false);
	}
}

void AUTHUB_GAS2025PlayerController::OnSetDestinationReleased()
{
	// If it was a short press
	if (FollowTime <= ShortPressThreshold)
	{
		// We move there and spawn some particles
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, CachedDestination, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
	}

	FollowTime = 0.f;
}

// Triggered every frame when the input is held down
void AUTHUB_GAS2025PlayerController::OnTouchTriggered()

{
	bIsTouch = true;
	OnSetDestinationTriggered();
}

void AUTHUB_GAS2025PlayerController::OnTouchReleased()
{
	bIsTouch = false;
	OnSetDestinationReleased();
}
