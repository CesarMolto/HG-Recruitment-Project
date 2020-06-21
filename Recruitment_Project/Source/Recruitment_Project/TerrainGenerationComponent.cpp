// Copyright Cesar Molto Morilla

#include "TerrainGenerationComponent.h"
#include "TerrainTile.h"
#include "PaperSprite.h"
#include "PaperSpriteComponent.h"
#include "EngineUtils.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "Camera/CameraActor.h"

// Sets default values for this component's properties
UTerrainGenerationComponent::UTerrainGenerationComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

// Called when the game starts
void UTerrainGenerationComponent::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> FoundActors;
 	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACameraActor::StaticClass(), FoundActors);

	ACameraActor* Camera = Cast<ACameraActor>(FoundActors[0]);

	if(!Camera) { UE_LOG(LogTemp, Warning, TEXT("Current active camera not found!")); return; }

	UCameraComponent* CameraComponent = Camera->FindComponentByClass<UCameraComponent>();

	if(!CameraComponent) { UE_LOG(LogTemp, Warning, TEXT("Current active camera COMPONENT not found!")); return; }

	// int32 AspectRatio = CameraComponent->
	int32 NewOrthoWidth = TerrainColumns * XOffset;
	
	CameraComponent->SetOrthoWidth(NewOrthoWidth);

	StartLocation = FVector(-NewOrthoWidth/2 + XOffset/2, 0, (-NewOrthoWidth/1.25)/2 + 170/2);
}

void UTerrainGenerationComponent::LoadTileSprites()
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

void UTerrainGenerationComponent::InitTerrainTiles()
{
	int32 PreviousType = FMath::RandRange(0, 3);
	int32 PreviousMaterial = FMath::RandRange(0, 3);

	for(int32 i = 0; i < TerrainRows*TerrainColumns; i++)
	{
		for(int32 j = 0; j < TerrainColumns; j++)
		{
			FTile NextTile = FTile();

			NextTile.Type = FMath::RandRange(0, 3);

			if(PreviousType == 0 || PreviousType == 3)
			{
				while(NextTile.Type != 0 && NextTile.Type != 2)
					NextTile.Type = FMath::RandRange(0, 3);
			}
			else if(PreviousType == 1 || PreviousType == 2)
			{
				while(NextTile.Type != 1 && NextTile.Type != 3)
					NextTile.Type = FMath::RandRange(0, 3);
			}

			PreviousType = NextTile.Type;

			NextTile.Sprite = TileSprites[0];

			TerrainTiles.Add(NextTile);
		}
	}
}

void UTerrainGenerationComponent::GenerateRandomTerrain()
{
	for(int32 i = 0; i < TerrainRows; i++)
	{
		for(int32 j = 0; j < TerrainColumns; j++)
		{
			if(!TileBP) { UE_LOG(LogTemp, Warning, TEXT("Tile blueprint to spawn was not found!")); return; }

			auto SpawnedTile = GetWorld()->SpawnActor<ATerrainTile>(TileBP, StartLocation + FVector(XOffset * j, -10 * i, YOffset * i), FRotator(0, 0, 0));
			UPaperSpriteComponent* TileSprite = SpawnedTile->FindComponentByClass<UPaperSpriteComponent>(); 

			if(!SpawnedTile) { UE_LOG(LogTemp, Warning, TEXT("Spawned tile was not found!")); return; }
			
			TileSprite->SetSprite(TerrainTiles[i].Sprite);
		}
	}
}

