// Fill out your copyright notice in the Description page of Project Settings.


#include "HexTileAdditionalData.h"

#include <Actor.h>

// Sets default values for this component's properties
UHexTileAdditionalData::UHexTileAdditionalData()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHexTileAdditionalData::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHexTileAdditionalData::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHexTileAdditionalData::SetHexTileData(FHexTileData TileData)
{
	HexTileData.HexTileActor = TileData.HexTileActor;
	HexTileData.WorldLocation = TileData.WorldLocation;
	HexTileData.GridLocation = TileData.GridLocation;
}

void UHexTileAdditionalData::GetHexTileData(FHexTileData& TileData)
{
	TileData.HexTileActor = HexTileData.HexTileActor;
	TileData.WorldLocation = HexTileData.WorldLocation;
	TileData.GridLocation = HexTileData.GridLocation;
}

