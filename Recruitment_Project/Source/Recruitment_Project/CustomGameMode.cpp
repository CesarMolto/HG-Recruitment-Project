// Copyright Cesar Molto Morilla

#include "CustomGameMode.h"
#include "TerrainTile.h"
#include "PaperSprite.h"
#include "EngineUtils.h"
#include "Math/UnrealMathUtility.h"

void ACustomGameMode::LoadTileSprites()
{
	TArray<UObject*> Textures;
	EngineUtils::FindOrLoadAssetsByPath(TEXT("/Game/Assets/Images/Terrain"), Textures, EngineUtils::ATL_Regular);

	for (auto asset : Textures)
	{
		UPaperSprite* Sprite = Cast<UPaperSprite>(asset);
		if (Sprite != nullptr)
			TileSprites.Add(Sprite);
	}
}

void ACustomGameMode::InitTerrainTiles()
{
	int32 previousTile = FMath::RandRange(0, 3);

	for(int32 i = 0; i < TerrainRows*TerrainColumns; i++)
	{
		int32 nextTile = FMath::RandRange(0, 3);

		if(previousTile == 0 || previousTile == 3)
		{
			while(nextTile != 0 && nextTile != 2)
				nextTile = FMath::RandRange(0, 3);
		}
		else if(previousTile == 1 || previousTile == 2)
		{
			while(nextTile != 1 && nextTile != 3)
				nextTile = FMath::RandRange(0, 3);
		}

		TerrainTiles.Add(nextTile);

		previousTile = nextTile;
	}
}

void ACustomGameMode::GenerateRandomTerrain()
{
}