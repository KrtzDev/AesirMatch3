#pragma once

#include "HexTile.generated.h"

USTRUCT(BlueprintType)
struct FHexTileData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere) AActor* HexTileActor;
	UPROPERTY(EditAnywhere) FVector WorldLocation;
	UPROPERTY(EditAnywhere) FVector2D GridLocation;
};
