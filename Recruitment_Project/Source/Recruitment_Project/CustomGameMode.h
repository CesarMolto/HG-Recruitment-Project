// Copyright Cesar Molto Morilla

#pragma once

#include "TerrainGenerationComponent.h"
#include "WaveManagementComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CustomGameMode.generated.h"

/**
 * Class responsible for the Terrain Generation and Wave Management
 */
UCLASS()
class RECRUITMENT_PROJECT_API ACustomGameMode : public AGameModeBase
{
	GENERATED_BODY()

	// Random generated terrain's info. reference
	TArray<FPath> Terrain;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Sets default values for this actor's properties
	ACustomGameMode();

	// Returns an array of FPathLocations containing the location of every tile in the terrain
	TArray<FPathLocations> GetTerrainLocations();
};
