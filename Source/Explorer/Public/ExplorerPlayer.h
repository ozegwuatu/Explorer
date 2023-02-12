// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameplayTagContainer.h"
#include "InputActionValue.h"
#include "CustomGate.h"
#include "ExplorerPlayer.generated.h"

//Forward declarations.
class USpringArmComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;

UCLASS()
class EXPLORER_API AExplorerPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AExplorerPlayer();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Required for Enhanced Input plugin.
	virtual void PawnClientRestart() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TObjectPtr<UCameraComponent> FPCamera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ExplorerPlayer|Enhanced Input|Actions")
		TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ExplorerPlayer|Enhanced Input|Actions")
		TObjectPtr<UInputAction> MouseLookAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ExplorerPlayer|Enhanced Input|Actions")
		TObjectPtr<UInputAction> GamepadLookAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ExplorerPlayer|Enhanced Input|Actions")
		TObjectPtr<UInputAction> InteractAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ExplorerPlayer|Enhanced Input")
		TObjectPtr<UInputMappingContext> DefaultContext;

	//Allow the player to change this in options menu.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ExplorerPlayer")
		float MouseLookSensitivity = 1.f;

	//Allow the player to change this in options menu.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ExplorerPlayer")
		float GamepadLookSensitivity = 50.f;

	//The maximum distance at which the player can interact with a valid object.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ExplorerPlayer")
		float InteractRadius = 100.f;

	//Gameplay Tags that affect what the player can and can't do.
	UPROPERTY(BlueprintReadWrite)
		FGameplayTagContainer PlayerTags;

	//Custom C++ gate.
	UPROPERTY(VisibleAnywhere)
		FGate Gate = FGate(false);

	UPROPERTY()
		TObjectPtr<AActor> FocusedActor;

	void Move(const FInputActionValue& Value);

	void MouseLook(const FInputActionValue& Value);
	void GamepadLook(const FInputActionValue& Value);

	void Interact();

	void CheckForInteractables();

	FHitResult InteractHitResult;
};