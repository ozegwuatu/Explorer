// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ExplorerPlayer.h"
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
	//Activates one or more visual cues, that show the player an object can be interacted with.
	//Define this in Blueprint, to make use of AC_Outliner component.
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void StartFocus();

	//Deactivates all visual cues, that show the player an object can be interacted with.
	//Define this in Blueprint, to make use of AC_Outliner component.
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void EndFocus();

	//Triggers interact functionality on a valid object, such as picking up an item or opening a door.
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void OnInteract(AExplorerPlayer* CallingPlayer);
};