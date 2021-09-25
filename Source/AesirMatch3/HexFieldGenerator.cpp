// Fill out your copyright notice in the Description page of Project Settings.


#include "HexFieldGenerator.h"

#include <string>
#include <ThirdParty/CryptoPP/5.6.5/include/argnames.h>

#include "GamePieceAdditionalData.h"
#include "HexTileAdditionalData.h"
#include "DataStructs/GamePiece.h"

// Sets default values for this component's properties
UHexFieldGenerator::UHexFieldGenerator()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHexFieldGenerator::BeginPlay()
{
	Super::BeginPlay();

	// ...

	SpawnHexGrid(0,MaxGridSizeX,0,MaxGridSizeY,GetOwner()->GetActorLocation());
	FillHexGrid(HexGrid);
	
}


// Called every frame
void UHexFieldGenerator::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHexFieldGenerator::SpawnHexGrid(int32 MinX, int32 MaxX, int32 MinY, int32 MaxY, FVector BaseLocation)
{
	int32 ix, iy;
	float x, y, z;
	float tileWidth, tileHeight, horizontalSpacing, verticalSpacing;
	float tileSideLength;
	FVector SpawnLocation;


	//tileSideLength = FGenericPlatformMath::Tan(FMath::DegreesToRadians(30) * 100.0f * 2);

	UE_LOG(LogTemp,Warning,TEXT("%d"),tileSideLength);
	tileSideLength = 105;
	tileWidth = tileSideLength * 2.0f;
	tileHeight = FGenericPlatformMath::Sqrt(3.0f) * tileSideLength;;
	horizontalSpacing = tileWidth * (3.0f / 4.0f);
	verticalSpacing = tileHeight;
	
	for(ix = MinX; ix < MaxX; ix++)
	{
		for (iy = MinY; iy < MaxY; iy++)
		{
			x = ix * verticalSpacing;
			y = iy * horizontalSpacing;
			z = 0.0f;

			if((iy % 2) == 0)
			{
				x += verticalSpacing/2.0f;
			}
			
			SpawnLocation = FVector(-x, y, z) + BaseLocation;
			SpawnHexTile(SpawnLocation,FVector2D(ix,iy));
		}
	}
}

void UHexFieldGenerator::SpawnHexTile(FVector Location,FVector2D GridLocation)
{
	FActorSpawnParameters SpawnParameters;
	UHexTileAdditionalData* HexTileData;
	FHexTileData TileData;
	FRotator Rotation = FRotator::ZeroRotator;
	AActor* SpawnedTile;
	

	SpawnedTile = GetWorld()->SpawnActor(HexTile, &Location, &Rotation, SpawnParameters);
	HexTileData = SpawnedTile->FindComponentByClass<UHexTileAdditionalData>();
	if(HexTileData)
	{
		TileData.HexTileActor = SpawnedTile;
		TileData.WorldLocation = Location;
		TileData.GridLocation = GridLocation;
		HexTileData->SetHexTileData(TileData);
	}
	HexGrid.Add(GridLocation,SpawnedTile);
}

void UHexFieldGenerator::FillHexGrid(TMap<FVector2D,AActor*> GeneratedHexGrid)
{
	for (auto& GeneratedHexTile : GeneratedHexGrid)
	{		
		FVector SpawnLocation = GeneratedHexTile.Value->GetActorLocation();
		SpawnGamePiece(SpawnLocation,GeneratedHexTile.Key);	
	}
}

void UHexFieldGenerator::SpawnGamePiece(FVector SpawnLocation, FVector2D HexGridPosition)
{
	FActorSpawnParameters SpawnParameters;
	FRotator Rotation = FRotator::ZeroRotator;
	AActor* SpawnedGamePiece;
	UGamePieceAdditionalData* GamePieceData;
	FGamePieceData PieceData;

	SpawnedGamePiece = GetWorld()->SpawnActor(GamePieces[FMath::RandRange(0,GamePieces.Num()-1)], &SpawnLocation, &Rotation, SpawnParameters);
	GamePieceData = SpawnedGamePiece->FindComponentByClass<UGamePieceAdditionalData>();
	if(GamePieceData)
	{
		PieceData.GamePieceActor = SpawnedGamePiece;
		PieceData.GamePieceType = GamePieceData->GamePieceData.GamePieceType;
		PieceData.PositionOnHexGrid = HexGridPosition;
		GamePieceData->SetGamePieceData(PieceData);
	}
}

