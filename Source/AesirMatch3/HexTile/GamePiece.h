#pragma once

#include "GamePiece.generated.h"

UENUM()
enum EGamePieceType
{
	Blue,
	Red,
	Green,
	Yellow,
};

USTRUCT()
struct FGamePieceData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) AActor* GamePieceActor;
	UPROPERTY(EditAnywhere) TEnumAsByte<EGamePieceType> GamePieceType;
	UPROPERTY(EditAnywhere) FVector2D PositionOnHexGrid;
};
