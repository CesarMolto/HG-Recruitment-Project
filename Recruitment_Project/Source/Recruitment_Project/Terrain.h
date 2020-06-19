// Copyright Cesar Molto Morilla

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Terrain.generated.h"

// Forward declarations
class ATerrainTile;

UCLASS()
class RECRUITMENT_PROJECT_API ATerrain : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATerrain();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	// Private variables of the Terrain class
	UPROPERTY(EditAnywhere, Category="Setup")
	TArray<TSubclassOf<ATerrainTile>> TerrainTiles;

};
