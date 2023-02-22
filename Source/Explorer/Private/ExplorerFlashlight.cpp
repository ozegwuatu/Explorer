// Fill out your copyright notice in the Description page of Project Settings.

#include "ExplorerFlashlight.h"
#include "ExplorerItemDataAsset.h"
#include "Components/BoxComponent.h"

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

	CallingPlayer->TryToPickUpItem(this);
}

FItemInfo AExplorerFlashlight::GetTargetItemInfo_Implementation()
{
	return ItemDataAsset->ItemInfo;
}

void AExplorerFlashlight::AttachItemToPlayer_Implementation(AExplorerPlayer* CallingPlayer)
{
	FAttachmentTransformRules PickupRules(EAttachmentRule::SnapToTarget, true);

	ItemMesh->SetWorldTransform(RootComponent->GetComponentTransform(), false, nullptr, ETeleportType::ResetPhysics);

	//The player becomes the owner of the item.
	SetOwner(CallingPlayer);

	//The item's mesh becomes invisible, and no longer has any collision or physics simulation.
	ItemMesh->SetUseCCD(false);
	ItemMesh->SetVisibility(false);
	ItemMesh->SetSimulatePhysics(false);
	ItemMesh->SetCollisionProfileName(TEXT("NoCollision"));

	//The item's interact radius should no longer have collision, either.
	ItemInteractRadius->SetCollisionProfileName(TEXT("NoCollision"));

	//Finally, the item is attached to the player.
	AttachToComponent(CallingPlayer->GetMesh(), PickupRules);
}