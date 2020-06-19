// Copyright Cesar Molto Morilla

#include "Terrain.h"
#include "TerrainTile.h"

// Sets default values
ATerrain::ATerrain()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATerrain::BeginPlay()
{
	Super::BeginPlay();

	auto SpawnedTile = GetWorld()->SpawnActor<ATerrainTile>(TerrainTiles[0], GetActorLocation(), GetActorRotation());
}

// Called every frame
void ATerrain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

