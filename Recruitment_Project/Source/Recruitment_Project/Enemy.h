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

	// Sprite component
	UPaperSpriteComponent* SpriteComponent = nullptr;

	// Sprite to set when the enemy is killed
	UPaperSprite* DeadSprite = nullptr;
	// Sprite of the reward the enemy might drop when killed
	UPaperSprite* RewardSprite;

	// State variable of the enemy. Set to false when the enemy is killed
	bool IsAlive = true;

	// Pathway identification. Identificates the pathway where the enemy has been spawned
	int32 PathwayID = -1;

	// Reference to the pathway the enemy has to walk through
	TArray<FVector> Pathway;

	// Movement speed
	int32 Speed = 70;
	// Pathway index. Used to iterate through the Pathway locations
	int32 PathwayIndex = 0;
	// Stocks the location the enemy will go next
	FVector NextLocation = FVector(0);
	// Acceptance radius when moving to a new location
	float AcceptanceRadius = 1;
	
public:	
	// Sets default values for this actor's properties
	AEnemy();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Inits the basic enemy variables such as ID, PathwayID, or Pathway
	void InitEnemy(int32 PathwayIDToSet, TArray<FVector>& PathwayToSet);

	// Makes the hostage move to the location value in NextLocation
	void MoveToNextLocation(float DeltaTime);

	// Updates the value of NextLocation to the next location value in the Pathway array
	void UpdateNextLocation();

	// Inits the value of the Dead sprite variable
	void SetDeadSprite(UPaperSprite* SpriteToSet);

	// Inits the value of the Reward sprite variable
	void SetRewardSprite(UPaperSprite* SpriteToSet);

	//  Resets all the enemy variable and destroys the actor afer 1 second
	void KillEnemy();

	// Spawns a Gem with a chance of 50%
	void SpawnReward();
	
	// Gets the assigned pathway identification
	int32 GetPathwayID();

	// Returns the current state of the enemy. Alive or Dead
	bool IsEnemyAlive();
};
