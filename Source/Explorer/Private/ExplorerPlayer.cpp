// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplorerPlayer.h"
#include "GameFramework/SpringArmComponent.h"
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

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(GetMesh());

	FPCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FPCamera"));
	FPCamera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void AExplorerPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AExplorerPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Regularly check if the player is looking at an interactable object within range.
	//if (Gate.IsOpen()) CheckForInteractables();
}

// Called to bind functionality to input
void AExplorerPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Make sure that we are using a UEnhancedInputComponent; if not, the project is not configured correctly.
	if (TObjectPtr<UEnhancedInputComponent> PlayerEnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (IsValid(MoveAction)) PlayerEnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AExplorerPlayer::Move);
		
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

void AExplorerPlayer::Move(const FInputActionValue& Value)
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
	//CHECK IF FocusedActor IS STILL VALID, THEN CHECK IT FOR INTERFACE
	//IF FocusedActor IS STILL VALID AND HAS INTERFACE, CALL OnInteract() ON FocusedActor
	//REMOVE INTERACTION GAMEPLAY TAG
}

void AExplorerPlayer::CheckForInteractables()
{
	//CHECK IF HIT ACTOR IS VALID
		//IF HIT ACTOR IS VALID, THEN CHECK IF HIT ACTOR IS THE SAME AS FocusedActor
			//IF HIT ACTOR IS NOT THE SAME AS FocusedActor, THEN END FOCUS ON FocusedActor,  REMOVE INTERACTION GAMEPLAY TAG, AND CHECK HIT ACTOR FOR INTERFACE
				//IF HIT ACTOR HAS INTERFACE, THEN START FOCUS ON IT AND ADD INTERACTION GAMEPLAY TAG
			//EITHER WAY, FocusedActor IS NOW SET TO HIT ACTOR
		//IF HIT ACTOR IS NOT VALID, END FOCUS ON FocusedActor, REMOVE INTERACTION GAMEPLAY TAG, AND SET FocusedActor TO NULLPTR
}