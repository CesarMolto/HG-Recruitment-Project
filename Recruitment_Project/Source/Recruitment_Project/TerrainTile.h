// Copyright Cesar Molto Morilla

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TerrainTile.generated.h"

// Forward declarations
class UPaperSpriteComponent;

UCLASS()
class RECRUITMENT_PROJECT_API ATerrainTile : public AActor
{
	GENERATED_BODY()

	// Sprite component
	UPaperSpriteComponent* SpriteComponent;
	
public:	
	// Sets default values for this actor's properties
	ATerrainTile();
};
