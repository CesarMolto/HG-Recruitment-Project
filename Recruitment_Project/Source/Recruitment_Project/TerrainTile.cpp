// Copyright Cesar Molto Morilla

#include "TerrainTile.h"
#include "PaperSpriteComponent.h"

// Sets default values
ATerrainTile::ATerrainTile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Init sprite component
	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("TileSprite"));
	// Set sprite component as root
	RootComponent = SpriteComponent;
}

