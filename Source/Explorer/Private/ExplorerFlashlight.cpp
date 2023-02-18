// Fill out your copyright notice in the Description page of Project Settings.

#include "ExplorerFlashlight.h"
#include "ExplorerItemDataAsset.h"

// Sets default values
AExplorerFlashlight::AExplorerFlashlight()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void AExplorerFlashlight::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AExplorerFlashlight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AExplorerFlashlight::StartFocus_Implementation()
{
	//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 3, FColor::White, FString::Printf(TEXT("%s() successfully called"), *FString(__FUNCTION__))); //FOR TESTING
	
	OnItemInteractUpdate.Broadcast(true);
}

void AExplorerFlashlight::EndFocus_Implementation()
{
	//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 3, FColor::White, FString::Printf(TEXT("%s() successfully called"), *FString(__FUNCTION__))); //FOR TESTING

	OnItemInteractUpdate.Broadcast(false);
}

void AExplorerFlashlight::OnInteract_Implementation(AExplorerPlayer* CallingPlayer)
{
	//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 3, FColor::White, FString::Printf(TEXT("%s() successfully called"), *FString(__FUNCTION__))); //FOR TESTING
}

FItemInfo AExplorerFlashlight::GetFocusedItemInfo_Implementation()
{
	return ItemDataAsset->ItemInfo;
}