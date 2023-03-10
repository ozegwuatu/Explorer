// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "ExplorerItemBase.h"
#include "ExplorerInventorySlotButton.generated.h"

/**
 * 
 */
UCLASS()
class EXPLORER_API UExplorerInventorySlotButton : public UCommonButtonBase
{
	GENERATED_BODY()

public:
	/* The class of item contained in this inventory slot. It is expected to implement IExplorerInteractInterface.
	This variable is an array of class references, in case the item is stackable.
	*/
	UPROPERTY(BlueprintReadWrite, Category = "ExplorerInventorySlotButton")
		TArray<TSoftClassPtr<AExplorerItemBase>> ItemArray;

	//If "false", then any type of item can be placed in this slot. If "true", then only stackable items of the same class can be placed in it.
	UPROPERTY(BlueprintReadWrite, Category = "ExplorerInventorySlotButton")
		bool bIsSlotFilled;
	
protected:
	
};