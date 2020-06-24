// Copyright Cesar Molto Morilla

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WaveManagementComponent.generated.h"

// Forward declarations
class AHostage;
class AEnemy;
class UPaperSprite;

/**
 * Struct containing an array with the tile's LOCATION of every path in the terrain (I need it because nested containers are not supported in UE4, e.g TArray<TArray<FVector>>)
 */
USTRUCT()
struct RECRUITMENT_PROJECT_API FPathLocations
{
	GENERATED_BODY()

public:
	TArray<FVector> TileLocations;
};

/**
 * Component responsible for the spawn and manage waves
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RECRUITMENT_PROJECT_API UWaveManagementComponent : public UActorComponent
{
	GENERATED_BODY()

	// Array that contains all the tile locations of the terrain
	TArray<FPathLocations> TerrainLocations;

	// Character size on the X axis (Spawn separation between characters)
	int32 CharacterWidth = 100;

	// Stocking arrays for the Hostage, Enemy, and Gem sprites
	TArray<UPaperSprite*> HostageSprites;
	TArray<UPaperSprite*> EnemySprites;
	TArray<UPaperSprite*> GemSprites;

public:	
	// Sets default values for this component's properties
	UWaveManagementComponent();

	// Initialises the wave management component. Sets the reference of the terrain locations and loads the hostage and enemy sprites
	void Init(TArray<FPathLocations> TerrainLocationsToSet);

	// Spawns a random number of waves (between the number of paths and 0)
	void SpawnWaves();
	// Spawns the hostage in the middle of the wave if it is not already on the screen
	AHostage* SpawnHostage(FVector& SpawningLocation,  int32 HostageID, int32 PathwayID, TArray<FVector>& Pathway);
	// Spawns the front and back enemies of the wave
	TArray<AEnemy*> SpawnEnemies(FVector& SpawningLocation, int32 NumEnemies, int32 PathwayID, TArray<FVector>& Pathway);

	// Checks if the pathway where the wave is going to spawn is not ocuppied by another wave
	bool IsPathwayFree(int PathwayID, TArray<AActor*>& FoundHostages, TArray<AActor*>& FoundEnemies);
	// Checks if the hostage to spawn is not already on the screen
	bool IsHostageOnScreen(int32 HostageID, TArray<AActor*>& FoundHostages);

	// Loads the sprites from the indicated route and saves them in the array paramenter
	void LoadSprites(FString Route, TArray<UPaperSprite*>& SpritesArray);
};
