// Copyright Cesar Molto Morilla

#include "CustomGameMode.h"
#include "CustomPlayerController.h"
#include "TimerManager.h"

// Sets default values for this component's properties
ACustomGameMode::ACustomGameMode()
{
    PlayerControllerClass = ACustomPlayerController::StaticClass();
    DefaultPawnClass = nullptr;

    TerrainComponent = CreateDefaultSubobject<UTerrainGenerationComponent>(TEXT("TerrainComponent"));
    WaveComponent = CreateDefaultSubobject<UWaveManagementComponent>(TEXT("WaveComponent"));
}

// Called when the game starts
void ACustomGameMode::BeginPlay()
{
	Super::BeginPlay();

	/* GENERATE RANDOM TERRAIN */
    // Find Terrain Generation component
    if(!TerrainComponent) { UE_LOG(LogTemp, Warning, TEXT("Terrain generation component not found!")); return; }

    // Generate and save a reference to the terrain
    Terrain = TerrainComponent->GenerateRandomTerrain();

    /* INITIALISE WAVE MANAGEMENT */
    if(!WaveComponent) { UE_LOG(LogTemp, Warning, TEXT("Wave management component not found!")); return; }

    InitTerrainLocations();

    // Initialise component with the terrain locations array
    WaveComponent->Init(TerrainLocations);

    // Set timer to call the wave management component's SpawnWaves() method every 3 seconds
    FTimerHandle TimerHandle = FTimerHandle();
    GetWorldTimerManager().SetTimer(TimerHandle, WaveComponent, &UWaveManagementComponent::SpawnWaves, 3.0f, true, 1.0f);
}

void ACustomGameMode::InitTerrainLocations()
{
    for(int i = 0; i < Terrain.Num(); i++) // Travel through the Terrain paths
    {
        // Initialise and add a new FPathLocations to the TerrainLocations
        FPathLocations Pathway;
        TerrainLocations.Add(Pathway);

        for(int j = 0; j < Terrain[i].Tiles.Num(); j++) // Travel through all the tiles in the Terrain
        {   
            // Get the type of the current tyle
            int32 Type = Terrain[i].Tiles[j].Type;

            // Initialise tile location offsets on the Y and Z axis (These offsets will prevent overlaping and ensure that the character is well placed over the tile)
            int32 YOffset = 5;
            int32 ZOffset = 30;

            // Save current tile modified location in the array of terrain locations 
            if(Type == 3)       // If the current tile is a tall block
                ZOffset = 70;   // Add an offset of 70 units on the Z axis
            else if(Type == 2)  // If the current tile is an east ramp
                ZOffset = -10;  // Add an offset of -10 units on the Z axis

            // Save the modified location
            TerrainLocations[i].TileLocations.Add(Terrain[i].Tiles[j].Location + FVector(0, YOffset, ZOffset));       
        }
    }
}