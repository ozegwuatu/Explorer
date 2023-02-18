// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "ExplorerItemBase.h"
#include "ExplorerItemDataAsset.generated.h"

/**
 * 
 */


USTRUCT(BlueprintType)
struct FItemInfo
{
	GENERATED_BODY()

	//The name of the item.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Info")
		FName ItemName;

	//The description of the item, shown when the player examines it.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Info")
		FText ItemDescription;

	//The thumbnail that will be used to represent the item, in the player's inventory.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Info")
		TSoftObjectPtr<UTexture2D> ItemIcon;

	//The class of this item, primarily used for spawning purposes.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Info")
		TSoftClassPtr<AExplorerItemBase> ItemClass;

	//The maximum amount of this item that the player can hold.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Info")
		int32 MaxQuantity;

	//The maximum amount of this item that can be in a stack, if applicable.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Info")
		int32 MaxStackCount;

	//The amount of time it takes (in seconds) for this item to expire, if applicable.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Info")
		float ExpireTime;

	//Gameplay Tags that are associated with the item.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Info")
		FGameplayTagContainer ItemTags;

	//FItemInfo default values.
	FItemInfo() : MaxQuantity(1), MaxStackCount(1), ExpireTime(30.f) {}
};

UCLASS()
class EXPLORER_API UExplorerItemDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Info")
		FItemInfo ItemInfo;

protected:
	
};