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
 * Struct containing an array with the tiles LOCATION of every path in the terrain (I need it because nested containers are not supported in UE4 e.g TArray<TArray<FVector>>)
 */
USTRUCT()
struct RECRUITMENT_PROJECT_API FPathLocations
{
	GENERATED_BODY()

public:
	TArray<FVector> TileLocations;
};

/**
 * Component responsible for the wave management of the game
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RECRUITMENT_PROJECT_API UWaveManagementComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Setup")
	TSubclassOf<AHostage> HostageBP;

	UPROPERTY(EditAnywhere, Category="Setup")
	TSubclassOf<AEnemy> EnemyBP;

	TArray<FPathLocations> TerrainLocations;

	int32 CharacterWidth = 100;

	TArray<UPaperSprite*> HostageSprites;
	TArray<UPaperSprite*> EnemySprites;

public:	
	// Sets default values for this component's properties
	UWaveManagementComponent();

	void Init(TArray<FPathLocations> TerrainLocationsToSet);

	void SpawnWaves();

	TArray<AEnemy*> SpawnEnemies(FVector& SpawningLocation, int32 NumEnemies, int32 PathwayID);
	AHostage* SpawnHostage(FVector& SpawningLocation,  int32 HostageID, int32 PathwayID);

	void LoadHostageSprites();
	void LoadEnemySprites();

	bool IsHostageOnScreen(int32 HostageID, TArray<AActor*>& FoundHostages);
	bool IsPathwayFree(int PathwayID, TArray<AActor*>& FoundHostages, TArray<AActor*>& FoundEnemies);
};
