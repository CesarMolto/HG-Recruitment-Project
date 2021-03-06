// Copyright Cesar Molto Morilla


#include "Enemy.h"
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"
#include "Gem.h"
#include "EngineUtils.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Intialise sprite component
	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("SpriteComponent"));
	// Set sprite component as root 
	RootComponent = SpriteComponent;
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(IsAlive) // Only move when alive
		MoveToNextLocation(DeltaTime);
}

void AEnemy::InitEnemy(int32 PathwayIDToSet, TArray<FVector>& PathwayToSet)
{
	// Set pathway ID
	PathwayID = PathwayIDToSet;
	// Set pathway reference
	Pathway = PathwayToSet;
}

void AEnemy::MoveToNextLocation(float DeltaTime)
{
	// Calculate DeltaSpeed to have a framerate independent movement
	float DeltaSpeed = Speed * DeltaTime;

	// Initialise NextLocation for the first time with the first value of the Pathway variable
	if(NextLocation.IsZero() && PathwayIndex < Pathway.Num() - 1)
		NextLocation = Pathway[PathwayIndex];

	// Get current location of the actor
	FVector CurrentLocation = GetActorLocation();

	// Calculate distance between current and next location on the X and Z Axis
	float XDistance = FGenericPlatformMath::Abs(NextLocation.X - CurrentLocation.X);
	float ZDistance = FGenericPlatformMath::Abs(NextLocation.Z - CurrentLocation.Z);

	// Normalize the distances
	FVector2D DeltaVector = FVector2D(XDistance, ZDistance);
	DeltaVector.Normalize();

	// Get the delta speed for each axis
	float XDeltaSpeed = DeltaSpeed * DeltaVector.X;
	float ZDeltaSpeed = DeltaSpeed * DeltaVector.Y;

	// Move on the X axis
	if(XDistance > AcceptanceRadius)
	{
		if(CurrentLocation.X < NextLocation.X)
			CurrentLocation += FVector(XDeltaSpeed, 0, 0);
		else
			CurrentLocation -= FVector(XDeltaSpeed, 0, 0);
	}

	// Move on the Z axis
	if(ZDistance > AcceptanceRadius)
	{
		if(CurrentLocation.Z < NextLocation.Z)
			CurrentLocation += FVector(0, 0, ZDeltaSpeed);
		else
			CurrentLocation -= FVector(0, 0, ZDeltaSpeed);
	}

	// Already on the desired location; Update next location value
	if(XDistance < AcceptanceRadius && ZDistance < AcceptanceRadius)
	{
		// Update NextLocation value
		UpdateNextLocation();
	}
	else // Not yet on the desired location
	{
		// Update current actor's location
		SetActorLocation(CurrentLocation);
	}
}

void AEnemy::UpdateNextLocation()
{
	if(PathwayIndex < Pathway.Num() - 1) // The enemy is still going through the pathway values
	{
		PathwayIndex ++;
		NextLocation = Pathway[PathwayIndex]; // Update NextLocation with the next Pathway location value
	}
	else if(PathwayIndex == Pathway.Num() - 1) // The enemy is in the last location of the Pathway
	{
		PathwayIndex ++;
		NextLocation += FVector(100, 0, 0); // Update NextLocation one last time to make the enemy move out of the screen
	}
	else if(PathwayIndex == Pathway.Num()) // The enemy is already out of the screen
	{
		// Destroy the enemy actor
		Destroy();
	}
}

void AEnemy::SetDeadSprite(UPaperSprite* SpriteToSet)
{
	if(!SpriteToSet) { return; }
	DeadSprite = SpriteToSet;
}

void AEnemy::SetRewardSprite(UPaperSprite* SpriteToSet)
{
	if(!SpriteToSet) { return; }
	RewardSprite = SpriteToSet;
}

void AEnemy::KillEnemy()
{
	if(IsAlive) // Only do something if the enemy is alive
	{
		// Set IsAlive to false
		IsAlive = false;

		// Spawn reward with a chance of 50%
		SpawnReward();

		// Set actor location 2 units behind on the Y axis (Prevent overlaping with the other actors)
		SetActorLocation(GetActorLocation() - FVector(0, 2, 0));

		// Set dead sprite
		if(SpriteComponent && DeadSprite)
			SpriteComponent->SetSprite(DeadSprite);
		
		// Reset pathwayID value
		PathwayID = -1;
		
		// Destroy actor after 1s
		SetLifeSpan(1);
	}
}

void AEnemy::SpawnReward()
{
	int32 ShouldSpawn = FMath::RandRange(0, 1); // 50% Chance of spawning

	if(ShouldSpawn > 0) // If should spawn
	{
		// Spawn new gem actor in the world
		AGem* SpawnedGem = GetWorld()->SpawnActor<AGem>(GetActorLocation() - FVector(0, 1, 0), FRotator(0));
		
		if(!SpawnedGem) { UE_LOG(LogTemp, Warning, TEXT("SpawnedGem was not found!")); return; }

		// Get the spawned gem sprite component
		UPaperSpriteComponent* GemSprite = SpawnedGem->FindComponentByClass<UPaperSpriteComponent>();

		if(!GemSprite) { UE_LOG(LogTemp, Warning, TEXT("Gem sprite COMPONENT was not found!")); return; }

		// Init the gem sprite component value with the reward sprite variable
		if(RewardSprite)
			GemSprite->SetSprite(RewardSprite);
	}
}

int32 AEnemy::GetPathwayID()
{
	return PathwayID;
}

bool AEnemy::IsEnemyAlive()
{
	return IsAlive;
}



