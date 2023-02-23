// Fill out your copyright notice in the Description page of Project Settings.

#include "ExplorerConsumable.h"
#include "ExplorerItemDataAsset.h"
#include "Components/BoxComponent.h"

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

void AExplorerConsumable::AttachItemToPlayer_Implementation(AExplorerPlayer* CallingPlayer)
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

	//The item's interact radius will no longer respond to traces.
	ItemInteractRadius->SetCollisionProfileName(TEXT("NoCollision"));

	//Finally, the item is attached to the player.
	AttachToComponent(CallingPlayer->GetMesh(), PickupRules);
}

void AExplorerConsumable::DetachItemFromPlayer_Implementation()
{
	//The item will no longer have an owner.
	SetOwner(nullptr);

	//The item's mesh becomes visible, and both collision and physics simulation are reactivated.
	ItemMesh->SetUseCCD(true);
	ItemMesh->SetVisibility(true);
	ItemMesh->SetSimulatePhysics(true);
	ItemMesh->SetCollisionProfileName(TEXT("PhysicsActor"));

	//The item's interact radius will respond to traces once again.
	ItemInteractRadius->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	ItemInteractRadius->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	//Finally, the item is detached from the player.
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
}