// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ExplorerPlayer.h"
#include "ExplorerItemDataAsset.h"
#include "ExplorerInteractInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UExplorerInteractInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class EXPLORER_API IExplorerInteractInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	/* Activates one or more visual cues, that show the player an object can be interacted with.
	Define this in Blueprint, to make use of AC_Outliner component.
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ExplorerInteractInterface")
		void StartFocus();

	/* Deactivates all visual cues, that show the player an object can be interacted with.
	Define this in Blueprint, to make use of AC_Outliner component.
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ExplorerInteractInterface")
		void EndFocus();

	/* Triggers interact functionality on a valid object, such as picking up an item or opening a door.
	 @param	CallingPlayer	The player that interacted with this object.
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ExplorerInteractInterface")
		void OnInteract(AExplorerPlayer* CallingPlayer);

	//Returns the item's FItemInfo struct.
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ExplorerInteractInterface|Item Info")
		FItemInfo GetTargetItemInfo();

	//Returns the interactable object's name, primarily meant for displaying it in the player's HUD.
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ExplorerInteractInterface|Item Info")
		FName GetTargetInteractableName();
};