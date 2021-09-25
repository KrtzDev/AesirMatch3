// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePieceAdditionalData.h"

// Sets default values for this component's properties
UGamePieceAdditionalData::UGamePieceAdditionalData()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGamePieceAdditionalData::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGamePieceAdditionalData::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UGamePieceAdditionalData::SetGamePieceData(FGamePieceData PieceData)
{
	GamePieceData.GamePieceActor = PieceData.GamePieceActor;
	GamePieceData.GamePieceType = PieceData.GamePieceType;
	GamePieceData.PositionOnHexGrid = PieceData.PositionOnHexGrid;
}

void UGamePieceAdditionalData::GetGamePieceAdditionalData(FGamePieceData& PieceData)
{
	PieceData.GamePieceActor = GamePieceData.GamePieceActor;
	PieceData.GamePieceType = GamePieceData.GamePieceType;
	PieceData.PositionOnHexGrid = GamePieceData.PositionOnHexGrid;
}

