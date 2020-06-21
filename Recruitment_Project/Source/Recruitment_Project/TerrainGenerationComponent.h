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
	int32 Type;

	int32 Material;

	FVector Location;
	
	UPaperSprite* Sprite;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RECRUITMENT_PROJECT_API UTerrainGenerationComponent : public UActorComponent
{
	GENERATED_BODY()

	// Private variables of the Terrain generation component class
	UPROPERTY(EditAnywhere, Category="Terrain Generation")
	TSubclassOf<ATerrainTile> TileBP;

	UPROPERTY(EditAnywhere, Category="Terrain Generation")
	int32 TerrainRows = 5;

	UPROPERTY(EditAnywhere, Category="Terrain Generation")
	int32 TerrainColumns = 7;

	FVector StartLocation = FVector(0);

	UPROPERTY(EditAnywhere, Category="Terrain Generation")
	int32 XOffset = 100;

	UPROPERTY(EditAnywhere, Category="Terrain Generation")
	int32 YOffset = 80;

	int32 ZOffset = -10;

	UPROPERTY(VisibleAnywhere, Category="Terrain Generation")
	TArray<FTile> TerrainTiles;

	UPROPERTY(VisibleAnywhere, Category="Terrain Generation")
	TArray<UPaperSprite*> TileSprites;

public:	
	// Sets default values for this component's properties
	UTerrainGenerationComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Public functions of the CustomGameMode class
	UFUNCTION(BlueprintCallable, Category = "Terrain Generation")
	void LoadTileSprites();

	UFUNCTION(BlueprintCallable, Category = "Terrain Generation")
	void InitTerrainTiles();

	UFUNCTION(BlueprintCallable, Category = "Terrain Generation")
	void GenerateRandomTerrain();	
};
