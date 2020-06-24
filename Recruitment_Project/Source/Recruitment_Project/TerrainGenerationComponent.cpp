// Copyright Cesar Molto Morilla

#include "TerrainGenerationComponent.h"
#include "TerrainTile.h"
#include "PaperSprite.h"
#include "PaperSpriteComponent.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "Camera/CameraActor.h"

// Sets default values for this component's properties
UTerrainGenerationComponent::UTerrainGenerationComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

void UTerrainGenerationComponent::LoadTileSprites()
{
	// Find all tile objects in the Terrain's folder
	TArray<UObject*> TileTextures;
	EngineUtils::FindOrLoadAssetsByPath(TEXT("/Game/Assets/Images/Terrain"), TileTextures, EngineUtils::ATL_Regular);

	for (auto Asset : TileTextures) // Iterate through all the found objects
	{
		// Save the objects that are Paper Sprites in the TileSprites array
		UPaperSprite* Sprite = Cast<UPaperSprite>(Asset);
		if (Sprite != nullptr)
			TileSprites.Add(Sprite);
	}
}

FVector UTerrainGenerationComponent::GetStartSpawningLocation()	
{
	// Find all camera actors in the world
	TArray<AActor*> FoundActors;
 	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACameraActor::StaticClass(), FoundActors);

	if(!FoundActors[0]) { UE_LOG(LogTemp, Warning, TEXT("No camera actors were found in the world!")); return FVector(0); }

	// Get the first camera actor found
	ACameraActor* Camera = Cast<ACameraActor>(FoundActors[0]);

	if(!Camera) { UE_LOG(LogTemp, Warning, TEXT("Current active camera not found!")); return FVector(0); }

	// Get the camera component of the camera actor
	UCameraComponent* CameraComponent = Camera->FindComponentByClass<UCameraComponent>();

	if(!CameraComponent) { UE_LOG(LogTemp, Warning, TEXT("Current active camera COMPONENT not found!")); return FVector(0); }

	// Calculate new orthographic width for the terrain to fit in the screen
	int32 NewOrthoWidth = TerrainColumns * TileWidth;

	// Set new orthographic width to the camera
	CameraComponent->SetOrthoWidth(NewOrthoWidth);

	// Calculate the position on the screen where the terrain tiles will start spawning
	return FVector(-NewOrthoWidth/2 + TileWidth, 0, (-NewOrthoWidth)/2 + TileHeight/2);
}

TArray<FPath>& UTerrainGenerationComponent::GenerateRandomTerrain() 															
{																	
	// Load tile sprites from the content folder
	LoadTileSprites();

	// Initialise random terrain size
	TerrainRows = FMath::RandRange(4, 5);
	TerrainColumns = FMath::RandRange(7, 8);

	// Get the location where the tiles will start spawning
	FVector StartLocation = GetStartSpawningLocation();

	for(int32 i = 0; i  < TerrainRows; i++) // Travel the terrain pathways
	{
		// Initialise and add a new path to the terrain
		FPath Path = FPath();
		// TerrainTiles.Add(Path);

		// Initialise the first visible tile location in the current pathway (2nd and 3rd visible tiles will be the following ones)
		int32 VisibleTile = FMath::RandRange(0, TerrainColumns - 3); 

		// Type of the last tile added to the terrain (Range between 1 and 2, we don't want a ramp as the first tile of a path)
		int32 LastType = FMath::RandRange(1, 2); 

		for(int32 j = 0; j < TerrainColumns; j++) // Travel the terrain pathway's tiles
		{
			// Initialise the new terrain tile
			FTile Tile = FTile(); 

			// Initialise new tile's type --> 0:Normal Block, 1:West Ramp, 2:East Ramp, 3:Big Block

			if(LastType == 0) // Last placed tile is a normal block
				Tile.Type = FMath::RandRange(0, 1); // Next tile is wether a normal block or a west ramp
			else if(LastType == 1) // Last placed tile is a west ramp
				Tile.Type = 3; // Next tile is big block
			else if(LastType == 2) // Last placed tile is a east ramp
				Tile.Type = 0; // Next tile is a normal block
			else // Last placed tile is a big block
				Tile.Type = FMath::RandRange(2, 3); // Next tile is wether a big block or an east ramp

			LastType = Tile.Type;

			// Initialise tile's material if tile is a normal block
			if(Tile.Type == 0)
			{
				Tile.Material = FMath::RandRange(4, TileSprites.Num() - 1);
			}

			// Initialise tile's sprite based on type and material
			if(Tile.Type + Tile.Material < TileSprites.Num())
				Tile.Sprite = TileSprites[Tile.Type + Tile.Material];

			// Initialise tile's location based on type
			Tile.Location = StartLocation + FVector(TileWidth * j, YOffset * i, ZOffset * i);
			
			 if(Tile.Type == 1 || Tile.Type == 2) // If the tile is a ramp, an offset of 40 units on the Z axis needs to be applied
				Tile.Location += FVector(0, 0, 40);

			// Add tile to the terrain array
			Path.Tiles.Add(Tile);
		}

		// Ensure there are at least three visible tiles in every pathway
		if(i != 0) // Not initialising the first path
		{
			if(HasThreeVisibleTiles(Path, TerrainTiles[i - 1])) // If new path has at least three completely visible tiles
				TerrainTiles.Add(Path); // Add path to the TerrainTiles array
			else // Otherwise
				i --; // Reinitialise path
		}
		else // The first path is always going to be completely visible
		{
			TerrainTiles.Add(Path);
		}	
	}
	// Spawn the terrain tiles in the world
	SpawnRandomTerrain(); 

	// Return the array containing the terrain tiles info.
	return TerrainTiles;
}

void UTerrainGenerationComponent::SpawnRandomTerrain() 
{
	for(int32 i = 0; i < TerrainTiles.Num(); i++) // Travel the paths of the terrain
	{
		for(int32 j = 0; j < TerrainTiles[i].Tiles.Num(); j++) // Travel the tiles of the current path
		{			
			// Spawn tile at the appropiate world location
			auto SpawnedTile = GetWorld()->SpawnActor<ATerrainTile>(TerrainTiles[i].Tiles[j].Location, FRotator(0));

			if(!SpawnedTile) { UE_LOG(LogTemp, Warning, TEXT("Spawned tile was not found!")); return; }

			// Get the sprite component of the new spawned tile
			UPaperSpriteComponent* TileSprite = SpawnedTile->FindComponentByClass<UPaperSpriteComponent>(); 

			if(!TileSprite) { UE_LOG(LogTemp, Warning, TEXT("Sprite component was not found!")); return; }
			
			// Set appropiate sprite value in the sprite component
			TileSprite->SetSprite(TerrainTiles[i].Tiles[j].Sprite);
		}
	}
}

bool UTerrainGenerationComponent::HasThreeVisibleTiles(FPath PathToCheck, FPath PreviousPath)
{
	// Init counter for visible tiles
	int32 VisibleTiles = 0;

	for(int32 i = 0; i < PathToCheck.Tiles.Num() && i < PreviousPath.Tiles.Num(); i++)
	{
		int32 PreviousType = PreviousPath.Tiles[i].Type;
		int32 CheckType = PathToCheck.Tiles[i].Type;

		if(PreviousType == 0)
		{
			if(CheckType >= PreviousType)
				VisibleTiles ++;
			else
				VisibleTiles = 0;	
		}
		else if(PreviousType == 1)
		{
			if(CheckType == 1 || CheckType == 3)
				VisibleTiles ++;
			else
				VisibleTiles = 0;
		}
		else if(PreviousType == 2)
		{
			if(CheckType == 2 || CheckType == 3)
				VisibleTiles ++;
			else
				VisibleTiles = 0;
		}
		else
		{
			if(CheckType == 3)
				VisibleTiles ++;
			else
				VisibleTiles = 0;
		}			

		if(VisibleTiles == 3)
			return true;
	}

	return false;
}

