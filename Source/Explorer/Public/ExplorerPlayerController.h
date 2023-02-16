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
	/* A custom version of UWidgetBlueprintLibrary::SetInputMode_GameOnly(), that doesn't change the viewport mouse capture mode.
	 @param	InConsumeCaptureMouseDown	Leave this "false" to avoid issues with mouse clicks.
	 */
	UFUNCTION(BlueprintCallable)
		void CustomGameOnlyInputMode(bool InConsumeCaptureMouseDown);
};