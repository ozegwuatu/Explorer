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

	/* Attempts to pick up an item. This function will be defined in Blueprint.
	 @param	ItemToPickUp	The item that the player is trying to pick up. It is expected to implement IExplorerInteractInterface.
	 */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "ExplorerPlayer|Inventory")
		void TryToPickUpItem(AActor* ItemToPickUp);

	/* Successfully adds an item to the player's inventory array.
	 TryToPickUpItem() should call this function, if the inventory widget's check is successful.
	 @param	ItemAdded	The item that is being added. It is expected to implement IExplorerInteractInterface.
	 */
	UFUNCTION(BlueprintCallable, Category = "ExplorerPlayer|Inventory")
		void AddItemToPlayerInventory(AActor* ItemAdded);

	/* Successfully removes an item from the player's inventory array.
	 The inventory widget's "Remove Item From Inventory Slot" function should call this one, when appropriate.
	 @param	ItemRemoved	The item that is being removed. It is expected to implement IExplorerInteractInterface.
	 */
	UFUNCTION(BlueprintCallable, Category = "ExplorerPlayer|Inventory")
		void RemoveItemFromPlayerInventory(AActor* ItemRemoved);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/* Scene and Actor Components */

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ExplorerPlayer")
		TObjectPtr<UCameraComponent> FPCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ExplorerPlayer")
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
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ExplorerPlayer")
		FGameplayTagContainer PlayerTags;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "ExplorerPlayer")
		FPlayerInteractSignature OnPlayerInteractUpdate;

	UPROPERTY(BlueprintReadWrite, Category = "ExplorerPlayer|Inventory")
		TArray<AActor*> PlayerInventory;

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

	UPROPERTY()
		TArray<AActor*> IgnoredActors;
	
	FHitResult InteractHitResult;
	
	FVector CameraLocation;
	
	FRotator CameraRotation;
};