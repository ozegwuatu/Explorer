// Fill out your copyright notice in the Description page of Project Settings.

#include "ExplorerItemBase.h"
#include "Components/BoxComponent.h"

// Sets default values
AExplorerItemBase::AExplorerItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item Mesh"));
	ItemMesh->SetupAttachment(RootComponent);

	ItemInteractRadius = CreateDefaultSubobject<UBoxComponent>(TEXT("Item Interact Radius"));
	ItemInteractRadius->SetupAttachment(ItemMesh);
}

// Called when the game starts or when spawned
void AExplorerItemBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AExplorerItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}