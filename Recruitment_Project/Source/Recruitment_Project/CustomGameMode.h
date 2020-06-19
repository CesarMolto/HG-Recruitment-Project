// Copyright Cesar Molto Morilla

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CustomGameMode.generated.h"

// Forward declarations
class ATerrainTile;
class UPaperSprite;

/**
 * Manager class responsible for terrain generation and scoring.
 */
UCLASS()
class RECRUITMENT_PROJECT_API ACustomGameMode : public AGameModeBase
{
	GENERATED_BODY()

	// Private variables of the CustomGameMode class
	UPROPERTY(EditAnywhere, Category="Terrain Generation")
	int32 TerrainRows = 5;

	UPROPERTY(EditAnywhere, Category="Terrain Generation")
	int32 TerrainColumns = 7;
	
	UPROPERTY(VisibleAnywhere, Category="Terrain Generation")
	TArray<int32> TerrainTiles;

	UPROPERTY(VisibleAnywhere, Category="Terrain Generation")
	TArray<UPaperSprite*> TileSprites;

public:
	// Public functions of the CustomGameMode class
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void LoadTileSprites();

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void InitTerrainTiles();

	UFUNCTION(BlueprintCallable, Category = "Terrain Generation")
	void GenerateRandomTerrain();
};
