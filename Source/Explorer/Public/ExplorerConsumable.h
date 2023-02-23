// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ExplorerItemBase.h"
#include "ExplorerInteractInterface.h"
#include "ExplorerConsumable.generated.h"

/**
 * 
 */
UCLASS()
class EXPLORER_API AExplorerConsumable : public AExplorerItemBase, public IExplorerInteractInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AExplorerConsumable();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Overriden from ExplorerInteractInterface.
	virtual void StartFocus_Implementation() override;
	virtual void EndFocus_Implementation() override;
	virtual void OnInteract_Implementation(AExplorerPlayer* CallingPlayer) override;
	virtual FItemInfo GetTargetItemInfo_Implementation() override;
	virtual void AttachItemToPlayer_Implementation(AExplorerPlayer* CallingPlayer) override;
	virtual void DetachItemFromPlayer_Implementation() override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
