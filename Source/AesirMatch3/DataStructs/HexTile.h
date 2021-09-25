#pragma once
#include "GamePiece.h"

#include "HexTile.generated.h"

USTRUCT()
struct FHexTileData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere) AActor* HexTileActor;
	UPROPERTY(EditAnywhere) FVector WorldLocation;
	UPROPERTY(EditAnywhere) FVector2D GridLocation;
	UPROPERTY(EditAnywhere) bool bHasGamePiece;
};
