// Fill out your copyright notice in the Description page of Project Settings.

#include "MouseGameplayController.h"

#include "GamePieceAdditionalData.h"
#include "TileBase.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UMouseGameplayController::UMouseGameplayController()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMouseGameplayController::BeginPlay()
{
	Super::BeginPlay();

	bLMBisPressed = false;
	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(),0);
	PlayerController->InputComponent->BindAction("Action",IE_Pressed,this,&UMouseGameplayController::MouseClicked);
	PlayerController->InputComponent->BindAction("Action",IE_Released,this,&UMouseGameplayController::MouseReleased);	
}


// Called every frame
void UMouseGameplayController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(bLMBisPressed)
	{
		DoCursorRaycast();	
	}
}


void UMouseGameplayController::MouseClicked()
{
	bLMBisPressed = true;
	UE_LOG(LogTemp,Warning,TEXT("Clicked"));
}


void UMouseGameplayController::MouseReleased()
{
	bLMBisPressed = false;
	UE_LOG(LogTemp,Warning,TEXT("Released"));
	ClearSelectedTilesMap();
}


void UMouseGameplayController::DoCursorRaycast()
{
	bool bIsHit = false;
	
	FHitResult Hit = FHitResult (ForceInit);
	if(PlayerController)
	{
		bIsHit = PlayerController->GetHitResultUnderCursor(ECC_Visibility,true,Hit);
	}

	if(bIsHit)
	{
		EvaluateCursorRaycastHitResult(Hit);
	}
}


void UMouseGameplayController::EvaluateCursorRaycastHitResult(FHitResult HitResult)
{	
	AActor* HitTile;
	UGamePieceAdditionalData* HitTileData;
	FGamePieceData GamePieceData;

	HitTile = HitResult.GetActor();
	HitTileData = HitTile->FindComponentByClass<UGamePieceAdditionalData>();
	if(HitTileData)
	{
		HitTileData->GetGamePieceAdditionalData(GamePieceData);
		if(SelectedGamePieces.Num() == 0)
		{
			SelectedType = GamePieceData.GamePieceType;
			LastAddedGamePieceLocation = FVector2D(GamePieceData.PositionOnHexGrid.X,GamePieceData.PositionOnHexGrid.Y);
			UE_LOG(LogTemp,Warning,TEXT("%s"),*LastAddedGamePieceLocation.ToString());
			AddToSelectedTiles(GamePieceData.PositionOnHexGrid,HitTile);
			return;
		}
		
		if(GamePieceData.GamePieceType == SelectedType)
		{
			if(!SelectedGamePieces.Contains(GamePieceData.PositionOnHexGrid))
			{							
				if(FMath::Abs(LastAddedGamePieceLocation.X - GamePieceData.PositionOnHexGrid.X)
				 + FMath::Abs(LastAddedGamePieceLocation.Y - GamePieceData.PositionOnHexGrid.Y) <= 1
				|| FMath::Abs(LastAddedGamePieceLocation.X - GamePieceData.PositionOnHexGrid.X) == 1
				&& FMath::Abs(LastAddedGamePieceLocation.Y - GamePieceData.PositionOnHexGrid.Y) == 1)
				{
					LastAddedGamePieceLocation = GamePieceData.PositionOnHexGrid;
					UE_LOG(LogTemp,Warning,TEXT("%s"),*LastAddedGamePieceLocation.ToString());
					AddToSelectedTiles(GamePieceData.PositionOnHexGrid,HitTile);
					UE_LOG(LogTemp,Warning,TEXT("Added Tile"));	
				}
			}			
		}				
	}
}


void UMouseGameplayController::AddToSelectedTiles(FVector2D TileLocation,AActor* HitTile)
{
	SelectedGamePieces.Add(TileLocation,HitTile);
}


void UMouseGameplayController::ClearSelectedTilesMap()
{	
	if(SelectedGamePieces.Num() >= 3)
	{
		for (auto& SelectedPieces: SelectedGamePieces)
		{
			SelectedPieces.Value->Destroy();

			//TODO: update HexGrid So tiles fall from above
		}
	}
	SelectedGamePieces.Empty();
}

