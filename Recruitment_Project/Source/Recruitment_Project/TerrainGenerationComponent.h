// Copyright Cesar Molto Morilla

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TerrainGenerationComponent.generated.h"

// Forward declarations
class ATerrainTile;
class UPaperSprite;

/**
 * Struct that contains the relevant tile's info. for the terrain generation
 */
USTRUCT()
struct RECRUITMENT_PROJECT_API FTile
{
	GENERATED_BODY()

public:
	int32 Type = 0;

	int32 Material = 0;

	FVector Location = FVector(0);
	
	UPaperSprite* Sprite = nullptr;
};

/**
 * Struct containing an array with the tiles info. of every path in the terrain (I need it because nested containers are not supported in UE4 e.g TArray<TArray<FTile>>)
 */
USTRUCT()
struct RECRUITMENT_PROJECT_API FPath
{
	GENERATED_BODY()

public:
	TArray<FTile> Tiles;
};

/**
 * Component responsible for the generation of the random terrain at the beginning of the game
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RECRUITMENT_PROJECT_API UTerrainGenerationComponent : public UActorComponent
{
	GENERATED_BODY()

	// Terrain size variables
	int32 TerrainRows = 5;
	int32 TerrainColumns = 7;

	// Tile size on the X and Z axis
	int32 TileWidth = 100;
	int32 TileHeight = 170; 

	// Distance between rows on the Y and Z axis
	int32 YOffset = -10; 
	int32 ZOffset = 80; 

	// Stocking arrays for the tile sprites and the terrain tiles
	TArray<FPath> TerrainTiles;
	TArray<UPaperSprite*> TileSprites;

public:	
	// Sets default values for this component's properties
	UTerrainGenerationComponent();

	// Loads the terrain tiles sprites from the content browser and saves them in a TArray
	void LoadTileSprites();

	// Calculates the start spawning point of the terrain tiles and changes the visible area of the camera for the random terrain to fit
	FVector GetStartSpawningLocation();

	// Initialises the random terrain size, and the tiles type, material, sprite, and location in the world. Also returns a referece to the TArray where the tiles are saved
	TArray<FPath>& GenerateRandomTerrain();

	// Spawns the terrain tiles initialised at InitTerrainTiles()
	void SpawnRandomTerrain();	

	bool HasThreeVisibleTiles(FPath PathToCheck, FPath PreviousPath);
};
