// Fill out your copyright notice in the Description page of Project Settings.

#include "ExplorerConsumable.h"
#include "ExplorerItemDataAsset.h"

// Sets default values
AExplorerConsumable::AExplorerConsumable()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void AExplorerConsumable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AExplorerConsumable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AExplorerConsumable::StartFocus_Implementation()
{
	//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 3, FColor::White, FString::Printf(TEXT("%s() successfully called"), *FString(__FUNCTION__))); //FOR TESTING
	
	OnItemInteractUpdate.Broadcast(true);
}

void AExplorerConsumable::EndFocus_Implementation()
{
	//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 3, FColor::White, FString::Printf(TEXT("%s() successfully called"), *FString(__FUNCTION__))); //FOR TESTING

	OnItemInteractUpdate.Broadcast(false);
}

void AExplorerConsumable::OnInteract_Implementation(AExplorerPlayer* CallingPlayer)
{
	//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 3, FColor::White, FString::Printf(TEXT("%s() successfully called"), *FString(__FUNCTION__))); //FOR TESTING

	CallingPlayer->TryToPickUpItem(this);
}

FItemInfo AExplorerConsumable::GetTargetItemInfo_Implementation()
{
	return ItemDataAsset->ItemInfo;
}