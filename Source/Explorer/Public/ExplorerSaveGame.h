// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "ExplorerSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class EXPLORER_API UExplorerSaveGame : public USaveGame
{
	GENERATED_BODY()

public:

protected:
	//The user name that will be used to identify a collection of save games.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		FString SaveSlotName;

	//The numerical index that will be used to identify an individual save game.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		uint8 UserIndex;
};