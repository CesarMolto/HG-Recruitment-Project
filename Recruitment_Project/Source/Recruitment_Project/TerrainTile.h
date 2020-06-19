// Copyright Cesar Molto Morilla

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TerrainTile.generated.h"

// Forward declarations
class UPaperSprite;

UCLASS()
class RECRUITMENT_PROJECT_API ATerrainTile : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category="Setup")
	int32 TileType = 0;

	UPROPERTY(VisibleAnywhere, Category="Setup")
	int32 TileMaterial = 0;
	
public:	
	// Sets default values for this actor's properties
	ATerrainTile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
