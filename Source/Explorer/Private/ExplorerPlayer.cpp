// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplorerPlayer.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "ExplorerInteractInterface.h"

// Sets default values
AExplorerPlayer::AExplorerPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FPCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FPCamera"));
	FPCamera->SetupAttachment(RootComponent);

	FPMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FPMesh"));
	FPMesh->SetupAttachment(FPCamera);
}

// Called when the game starts or when spawned
void AExplorerPlayer::BeginPlay()
{
	Super::BeginPlay();

	//The player themselves will be ignored by any line traces that they perform.
	IgnoredActors.Emplace(this);
}

// Called every frame
void AExplorerPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Regularly check if the player is looking at an interactable object within range.
	if (Gate.IsOpen()) InteractLineTrace();
}

// Called to bind functionality to input
void AExplorerPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Make sure that we are using a UEnhancedInputComponent; if not, the project is not configured correctly.
	if (TObjectPtr<UEnhancedInputComponent> PlayerEnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (IsValid(MoveForwardAction)) PlayerEnhancedInputComponent->BindAction(MoveForwardAction, ETriggerEvent::Triggered, this, &AExplorerPlayer::MoveForward);
		if (IsValid(MoveBackwardAction)) PlayerEnhancedInputComponent->BindAction(MoveBackwardAction, ETriggerEvent::Triggered, this, &AExplorerPlayer::MoveBackward);
		if (IsValid(StrafeLeftAction)) PlayerEnhancedInputComponent->BindAction(StrafeLeftAction, ETriggerEvent::Triggered, this, &AExplorerPlayer::StrafeLeft);
		if (IsValid(StrafeRightAction)) PlayerEnhancedInputComponent->BindAction(StrafeRightAction, ETriggerEvent::Triggered, this, &AExplorerPlayer::StrafeRight);
		if (IsValid(GamepadMoveAction)) PlayerEnhancedInputComponent->BindAction(GamepadMoveAction, ETriggerEvent::Triggered, this, &AExplorerPlayer::GamepadMove);
		
		if (IsValid(MouseLookAction)) PlayerEnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &AExplorerPlayer::MouseLook);
		if (IsValid(GamepadLookAction)) PlayerEnhancedInputComponent->BindAction(GamepadLookAction, ETriggerEvent::Triggered, this, &AExplorerPlayer::GamepadLook);

		if (IsValid(InteractAction)) PlayerEnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &AExplorerPlayer::Interact);
	}
}

void AExplorerPlayer::PawnClientRestart()
{
	Super::PawnClientRestart();

	// Make sure that we have a valid PlayerController.
	if (TObjectPtr<APlayerController> PC = Cast<APlayerController>(GetController()))
	{
		// Get the Enhanced Input Local Player Subsystem from the Local Player related to our Player Controller.
		if (TObjectPtr<UEnhancedInputLocalPlayerSubsystem> Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			// PawnClientRestart can run more than once in an Actor's lifetime, so start by clearing out any leftover mappings.
			Subsystem->ClearAllMappings();

			// Add each mapping context, along with their priority values. Higher values out-prioritize lower values.
			Subsystem->AddMappingContext(DefaultContext, 0);
		}
	}
}

void AExplorerPlayer::MoveForward(const FInputActionValue& Value)
{
	if (Value.GetMagnitude() != 0)
	{
		AddMovementInput(GetActorForwardVector(), Value[1]);
	}
}

void AExplorerPlayer::MoveBackward(const FInputActionValue& Value)
{
	if (Value.GetMagnitude() != 0)
	{
		AddMovementInput(GetActorForwardVector(), Value[1]);
	}
}

void AExplorerPlayer::StrafeLeft(const FInputActionValue& Value)
{
	if (Value.GetMagnitude() != 0)
	{
		AddMovementInput(GetActorRightVector(), Value[0]);
	}
}

void AExplorerPlayer::StrafeRight(const FInputActionValue& Value)
{
	if (Value.GetMagnitude() != 0)
	{
		AddMovementInput(GetActorRightVector(), Value[0]);
	}
}

void AExplorerPlayer::GamepadMove(const FInputActionValue& Value)
{
	if (Value.GetMagnitude() != 0)
	{
		AddMovementInput(GetActorForwardVector(), Value[1]);
		AddMovementInput(GetActorRightVector(), Value[0]);
	}
}

void AExplorerPlayer::MouseLook(const FInputActionValue& Value)
{
	if (Value.GetMagnitude() != 0)
	{
		AddControllerPitchInput(Value[1] * MouseLookSensitivity);
		AddControllerYawInput(Value[0] * MouseLookSensitivity);
	}
}

void AExplorerPlayer::GamepadLook(const FInputActionValue& Value)
{
	if (Value.GetMagnitude() != 0)
	{
		AddControllerPitchInput(Value[1] * GamepadLookSensitivity * GetWorld()->GetDeltaSeconds());
		AddControllerYawInput(Value[0] * GamepadLookSensitivity * GetWorld()->GetDeltaSeconds());
	}
}

void AExplorerPlayer::Interact()
{
	if (!PlayerTags.HasTagExact(FGameplayTag::RequestGameplayTag(TEXT("Player.Interact")))) return;

	if (IsValid(FocusedActor))
	{
		//If the focused actor is still valid and has an interface, execute interact functionality and disable player interaction.
		if (TObjectPtr<IExplorerInteractInterface> Interface = Cast<IExplorerInteractInterface>(FocusedActor))
		{
			Interface->Execute_OnInteract(FocusedActor, this);

			//PlayerTags.RemoveTag(FGameplayTag::RequestGameplayTag(TEXT("Player.Interact"))); //DISABLING UNTIL INVENTORY SYSTEM IS IN PLACE
		}
	}
}

void AExplorerPlayer::InteractLineTrace()
{
	if (IsValid(GetInstigatorController()))
	{
		//Store the location and rotation of the player's camera, in a pair of out parameters.
		GetInstigatorController()->GetPlayerViewPoint(CameraLocation, CameraRotation);

		FVector CameraTraceEndLocation = CameraLocation + CameraRotation.Vector() * PlayerInteractRadius;

		//Perform a line trace from the center of the player's camera, to the maximum extent of their interact range.
		UKismetSystemLibrary::LineTraceSingle(this, CameraLocation, CameraTraceEndLocation, ETraceTypeQuery::TraceTypeQuery4, false, IgnoredActors, EDrawDebugTrace::ForDuration, InteractHitResult, true, FLinearColor::Red, FLinearColor::Green, 2.f);
	}

	CheckForInteractableObjects();
}

void AExplorerPlayer::CheckForInteractableObjects()
{
	TObjectPtr<AActor> HitActor = InteractHitResult.GetActor();

	if (IsValid(HitActor))
	{
		//For when the hit actor is different than the last focused actor.
		if (HitActor != FocusedActor)
		{
			//End focus on the focused actor, and disable player interaction if applicable.
			if (TObjectPtr<IExplorerInteractInterface> Interface = Cast<IExplorerInteractInterface>(FocusedActor))
			{
				Interface->Execute_EndFocus(FocusedActor);

				PlayerTags.RemoveTag(FGameplayTag::RequestGameplayTag(TEXT("Player.Interact")));
			}

			//Start focus on the hit actor, and enable player interaction if applicable.
			if (TObjectPtr<IExplorerInteractInterface> Interface = Cast<IExplorerInteractInterface>(HitActor))
			{
				Interface->Execute_StartFocus(HitActor);

				PlayerTags.AddTag(FGameplayTag::RequestGameplayTag(TEXT("Player.Interact")));
			}
		}

		//A reference to the hit actor will be stored regardless.
		FocusedActor = HitActor;
	}
	//For when no actor has been hit at all.
	else
	{
		//End focus on the focused actor, and disable player interaction if applicable.
		if (TObjectPtr<IExplorerInteractInterface> Interface = Cast<IExplorerInteractInterface>(FocusedActor))
		{
			Interface->Execute_EndFocus(FocusedActor);

			PlayerTags.RemoveTag(FGameplayTag::RequestGameplayTag(TEXT("Player.Interact")));
		}

		//No actor has been hit, so no reference needs to be stored.
		FocusedActor = nullptr;
	}
}