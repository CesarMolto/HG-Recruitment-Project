// Copyright Cesar Molto Morilla

#include "CustomGameMode.h"

// Called when the game starts
void ACustomGameMode::BeginPlay()
{
	Super::BeginPlay();

	// Generate random terrain
    UTerrainGenerationComponent* TerrainGenerationComponent = FindComponentByClass<UTerrainGenerationComponent>(); 
    if(!TerrainGenerationComponent) { UE_LOG(LogTemp, Warning, TEXT("Terrain generation component not found!")); return; }
    Terrain = TerrainGenerationComponent->GenerateRandomTerrain();

    // Initialise wave management component with the terrain locations
    UWaveManagementComponent* WaveManagementComponent = FindComponentByClass<UWaveManagementComponent>(); 
    if(!WaveManagementComponent) { UE_LOG(LogTemp, Warning, TEXT("Wave management component not found!")); return; }
    WaveManagementComponent->Init(GetTerrainLocations());
    WaveManagementComponent->SpawnWaves(); // TODO --> Move to the tick method and call this function every X seconds
}

// Called every frame
void ACustomGameMode::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
}

TArray<FPathLocations> ACustomGameMode::GetTerrainLocations()
{
    // Declare the TArray of FPathLocation the method is going to return
    TArray<FPathLocations> TerrainLocations;

    for(int i = 0; i < Terrain.Num(); i++) // Travel through the Terrain reference's paths
    {
        // Initialise and add a new FPathLocations to the TerrainLocations
        FPathLocations Pathway;
        TerrainLocations.Add(Pathway);

        for(int j = 0; j < Terrain[i].Tiles.Num(); j++) // Travel through all the tiles in the Terrain's reference
        {   
            // Save current tile modified location in the terrain locations array (Modified to prevent overlaping with the characters)
            if(Terrain[i].Tiles[j].Type == 3) // If the current tile is a tall block
                TerrainLocations[i].TileLocations.Add(Terrain[i].Tiles[j].Location + FVector(0, 5, 80)); // Add + 5 units on the Y axis and +80 units on the Z axis
            else // If the current tile is not a tall block
                TerrainLocations[i].TileLocations.Add(Terrain[i].Tiles[j].Location + FVector(0, 5, 30)); // Add +5 units on the Y axis and +30 units on the Z axis
        }
    }

    // Return the array containing all the terrain tiles locations
    return TerrainLocations;
}