// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "ExplorerInventorySlotButton.h"
#include "ExplorerInventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class EXPLORER_API UExplorerInventoryWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:
	//All of the inventory slots contained within this widget.
	UPROPERTY(BlueprintReadWrite, Category = "ExplorerInventoryWidget")
	TArray<UExplorerInventorySlotButton*> InventorySlotArray;
	
	/* Checks to see if the item that the player interacted with can be picked up. This function will be defined in Blueprint.
	 Returns "true" if the item can be picked up, or "false" if the player's inventory is full.
	 OVERRIDE THIS FUNCTION IN BLUEPRINT TO RETURN A VALUE!
	 @param	ItemToCheck	The item that the player is trying to pick up. It is expected to implement IExplorerInteractInterface.
	 @param bIsSlotAvailable	This is being written as an out parameter, but will show up as a return value in Blueprint.
	 */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "ExplorerInventoryWidget|Item Management")
		void CheckForAvailableInventorySlot(AActor* ItemToCheck, bool& bIsSlotAvailable);

	/* Adds an item to the player's inventory widget. This function will be defined in Blueprint.
	 @param	SlotToFill	The inventory slot that will hold the item.
	 @param	ItemToAdd	The item that will be added to the player's inventory. It is expected to implement IExplorerInteractInterface.
	 */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "ExplorerInventoryWidget|Item Management")
		void AddItemToInventorySlot(UExplorerInventorySlotButton* SlotToFill, AActor* ItemToAdd);

	/* Removes an item from the player's inventory widget. This function will be defined in Blueprint.
	 @param	SlotToEmpty	The inventory slot that is holding the item.
	 @param	ItemToRemove	The item that will be removed from the player's inventory. It is expected to implement IExplorerInteractInterface.
	 */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "ExplorerInventoryWidget|Item Management")
		void RemoveItemFromInventorySlot(UExplorerInventorySlotButton* SlotToEmpty, AActor* ItemToRemove);

protected:
	
};