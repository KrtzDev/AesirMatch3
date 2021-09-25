// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include <Actor.h>

#include "Components/ActorComponent.h"
#include "DataStructs/GamePiece.h"

#include "MouseGameplayController.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AESIRMATCH3_API UMouseGameplayController : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMouseGameplayController();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void MouseClicked();
	void MouseReleased();
	void DoCursorRaycast();
	void EvaluateCursorRaycastHitResult(FHitResult HitResult);
	void AddToSelectedTiles(FVector2D TileLocation, AActor* HitTile);
	void ClearSelectedTilesMap();
	void RemoveTilesFromBoard();

private:
	bool bLMBisPressed;
	UPROPERTY(EditAnywhere) APlayerController* PlayerController;
	UPROPERTY(EditAnywhere) TMap<FVector2D,AActor*> SelectedGamePieces;
	UPROPERTY(EditAnywhere) TEnumAsByte<EGamePieceType> SelectedType;
	UPROPERTY(EditAnywhere) FVector2D LastAddedGamePieceLocation;
};
