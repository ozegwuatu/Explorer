// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameplayTagContainer.h"
#include "InputActionValue.h"
#include "CustomGate.h"
#include "ExplorerPlayer.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FPlayerInteractSignature, bool, bCanInteract, AActor*, FocusedItem);

//Forward declarations.
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

	/* Scene and Actor Components */

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TObjectPtr<UCameraComponent> FPCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TObjectPtr<USkeletalMeshComponent> FPMesh;

	/* EnhancedInput Actions and Mapping Contexts */

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ExplorerPlayer|Enhanced Input|Actions|Mouse and Keyboard")
		TObjectPtr<UInputAction> MoveForwardAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ExplorerPlayer|Enhanced Input|Actions|Mouse and Keyboard")
		TObjectPtr<UInputAction> MoveBackwardAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ExplorerPlayer|Enhanced Input|Actions|Mouse and Keyboard")
		TObjectPtr<UInputAction> StrafeLeftAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ExplorerPlayer|Enhanced Input|Actions|Mouse and Keyboard")
		TObjectPtr<UInputAction> StrafeRightAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ExplorerPlayer|Enhanced Input|Actions|Gamepad")
		TObjectPtr<UInputAction> GamepadMoveAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ExplorerPlayer|Enhanced Input|Actions|Mouse and Keyboard")
		TObjectPtr<UInputAction> MouseLookAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ExplorerPlayer|Enhanced Input|Actions|Gamepad")
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
		float PlayerInteractRadius = 100.f;

	//Gameplay Tags that affect what the player can and can't do.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		FGameplayTagContainer PlayerTags;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
		FPlayerInteractSignature OnPlayerInteractUpdate;

	//Custom C++ gate.
	UPROPERTY(VisibleAnywhere)
		FGate Gate = FGate(false);

	//Open the custom C++ gate from Blueprint.
	UFUNCTION(BlueprintCallable, Category = "ExplorerPlayer|Custom Gate")
		void OpenCustomGate();

	//Close the custom C++ gate from Blueprint.
	UFUNCTION(BlueprintCallable, Category = "ExplorerPlayer|Custom Gate")
		void CloseCustomGate();

	//Check if the custom C++ gate is open or not, from Blueprint.
	UFUNCTION(BlueprintPure, Category = "ExplorerPlayer|Custom Gate")
		bool CheckCustomGate();

	void MoveForward(const FInputActionValue& Value);
	void MoveBackward(const FInputActionValue& Value);
	void StrafeLeft(const FInputActionValue& Value);
	void StrafeRight(const FInputActionValue& Value);
	void GamepadMove(const FInputActionValue& Value);

	void MouseLook(const FInputActionValue& Value);
	void GamepadLook(const FInputActionValue& Value);

	void Interact();
	void InteractLineTrace();
	void CheckForInteractableObjects();

	TObjectPtr<AActor> FocusedActor;
	
	TArray<TObjectPtr<AActor>> IgnoredActors;
	
	FHitResult InteractHitResult;
	
	FVector CameraLocation;
	
	FRotator CameraRotation;
};