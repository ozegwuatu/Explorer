// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplorerPlayerController.h"

void AExplorerPlayerController::BeginPlay()
{
	Super::BeginPlay();

	CustomGameOnlyInputMode(false);
}

void AExplorerPlayerController::CustomGameOnlyInputMode(bool InConsumeCaptureMouseDown)
{
	FInputModeGameOnly GameMode;

	GameMode.SetConsumeCaptureMouseDown(InConsumeCaptureMouseDown);

	SetInputMode(GameMode);
}