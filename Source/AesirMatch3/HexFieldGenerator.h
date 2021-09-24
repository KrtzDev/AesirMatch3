// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include <Actor.h>

#include "Components/ActorComponent.h"
#include "HexTile/HexTile.h"

#include "HexFieldGenerator.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AESIRMATCH3_API UHexFieldGenerator : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHexFieldGenerator();
	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void SpawnHexTile(FVector Location, FVector2D GridLocation);
	void SpawnHexGrid(int32 MinX, int32 MaxX, int32 MinY, int32 MaxY, FVector BaseLocation);

private:

	UPROPERTY(EditAnywhere) TSubclassOf<AActor> HexTile;
};
