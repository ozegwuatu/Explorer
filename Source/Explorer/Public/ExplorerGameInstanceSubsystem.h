// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ExplorerSaveGame.h"
#include "ExplorerGameInstanceSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class EXPLORER_API UExplorerGameInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	// USubsystem implementation Begin
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UPROPERTY(BlueprintReadWrite)
		TObjectPtr<UExplorerSaveGame> PlayerSaveGame;
};