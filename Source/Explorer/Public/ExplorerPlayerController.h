// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ExplorerPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class EXPLORER_API AExplorerPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

protected:
	//Workaround for "Input Mode Game Only" bug, regarding mouse input.
	UFUNCTION(BlueprintCallable)
		void CustomGameOnlyInputMode(bool InConsumeCaptureMouseDown);
};