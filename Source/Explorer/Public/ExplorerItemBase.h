// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ExplorerItemBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FItemInteractSignature, bool, bFocusStarted);

//Forward declarations.
class UBoxComponent;
class UExplorerItemDataAsset;

UCLASS()
class EXPLORER_API AExplorerItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExplorerItemBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
		TObjectPtr<USceneComponent> Root;

	UPROPERTY(VisibleAnywhere)
		TObjectPtr<UStaticMeshComponent> ItemMesh;

	UPROPERTY(VisibleAnywhere)
		TObjectPtr<UBoxComponent> ItemInteractRadius;

	//The data asset that the item's information will be pulled from.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ExplorerItem")
		TObjectPtr<UExplorerItemDataAsset> ItemDataAsset;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
		FItemInteractSignature OnItemInteractUpdate;
};
