// Copyright Cesar Molto Morilla

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy.generated.h"

// Forward declarations
class UPaperSprite;
class UPaperSpriteComponent;

UCLASS()
class RECRUITMENT_PROJECT_API AEnemy : public AActor
{
	GENERATED_BODY()

	UPaperSpriteComponent* SpriteComponent = nullptr;

	// Sprite to set when the hostages is killed
	UPaperSprite* DeadSprite = nullptr;

	int32 PathwayIndex = 0;
	FVector NextLocation = FVector(0);
	float AcceptanceRadius = 0.5f;

	int32 PathwayID = -1;

	bool IsAlive = true;

	TArray<FVector> Pathway;

	int32 Speed = 70;

	UPaperSprite* RewardSprite;
	
public:	
	// Sets default values for this actor's properties
	AEnemy();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Makes the hostage move to the location value in NextLocation
	void MoveToNextLocation(float DeltaTime);

	// Updates the value of NextLocation to the next location value in the Pathway array
	void UpdateNextLocation();
	
	// Gets the assigned pathway identification
	int32 GetPathwayID();
	// Sets the pathway identification
	void SetPathwayID(int32 IDToSet);

	// Sets the pathway the enemy will walk through
	void SetPathway(TArray<FVector>& PathwayToSet);

	void SetDeadSprite(UPaperSprite* SpriteToSet);

	void SetRewardSprite(UPaperSprite* SpriteToSet);

	void KillEnemy();

	bool IsEnemyAlive();

	void SpawnReward();
};
