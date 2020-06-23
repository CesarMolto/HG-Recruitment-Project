// Copyright Cesar Molto Morilla

#include "WaveManagementComponent.h"
#include "Hostage.h"
#include "Enemy.h"
#include "PaperSprite.h"
#include "PaperSpriteComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"

// Sets default values for this component's properties
UWaveManagementComponent::UWaveManagementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UWaveManagementComponent::Init(TArray<FPathLocations> TerrainLocationsToSet)
{
	// Set terrain locations reference
	TerrainLocations = TerrainLocationsToSet;
	// Load hostage sprites
	LoadHostageSprites();
	// Load enemy sprites
	LoadEnemySprites();
}

void UWaveManagementComponent::SpawnWaves()
{
	// Initialise a random number of waves to spawn between 1 and the number of paths
	int32 NumWaves = FMath::RandRange(1, TerrainLocations.Num());

	// Start spawning the waves
	for(int32 i = 0; i < NumWaves; i++)
	{
		// Find all hostages on the screen
		TArray<AActor*> FoundHostages;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AHostage::StaticClass(), FoundHostages);

		// Find all enemies on the screen
		TArray<AActor*> FoundEnemies;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemy::StaticClass(), FoundEnemies);

		// Set random pathway where the current wave is going to try to spawn
		int32 RandomPath = FMath::RandRange(0, TerrainLocations.Num() - 1);

		if(IsPathwayFree(RandomPath, FoundHostages, FoundEnemies)) // Check if the selected pathway is free
		{
			// Get the selected pathway
			TArray<FVector> Pathway = TerrainLocations[RandomPath].TileLocations;
			// Calculate the Spawning position where the characters are going to start appearing
			FVector SpawningLocation = Pathway[0] - FVector(CharacterWidth, 0, 0);

			// Initialise the number of enemies and the hostage of the wave
			int32 NumEnemies = FMath::RandRange(2, 4);
			int32 RandomHostage = FMath::RandRange(0, 4);

			// Spawn front enemies
			TArray<AEnemy*> FrontEnemies = SpawnEnemies(SpawningLocation, NumEnemies / 2, RandomPath, Pathway);

			if(FrontEnemies.Num() <= 0) { UE_LOG(LogTemp, Warning, TEXT("An error ocurred when spawning the front enemies!")); return; }

			// Get the front enemy that was spawned the LAST
			AEnemy* FrontEnemy = FrontEnemies[FrontEnemies.Num() - 1];

			// Spawn hostage if it is not already on the screen
			AHostage* Hostage = nullptr;
			if(!IsHostageOnScreen(RandomHostage, FoundHostages))
				Hostage = SpawnHostage(SpawningLocation, RandomHostage, RandomPath, Pathway);

			// Spawn back enemies
			TArray<AEnemy*> BackEnemies = SpawnEnemies(SpawningLocation, NumEnemies - NumEnemies / 2, RandomPath, Pathway);

			if(BackEnemies.Num() <= 0) { UE_LOG(LogTemp, Warning, TEXT("An error ocurred when spawning the back enemies!")); return; }

			// Get the back enemy that was spawned the FIRST
			AEnemy* BackEnemy = BackEnemies[0];

			if(Hostage && FrontEnemy && BackEnemy) // If hostage exists
			{
				// Set references to the front and back enemy
				Hostage->SetFrontEnemy(FrontEnemy);
				Hostage->SetBackEnemy(BackEnemy);
			}
		}
	}
}

AHostage* UWaveManagementComponent::SpawnHostage(FVector& SpawningLocation, int32 HostageID, int32 PathwayID, TArray<FVector>& Pathway)
{
	// Set the hostage spawning location
	SpawningLocation -= FVector(CharacterWidth, 0, 0);
	// Get a reference to the spawned hostage
	auto SpawnedHostage =  GetWorld()->SpawnActor<AHostage>(SpawningLocation, FRotator(0));

	if(!SpawnedHostage) { UE_LOG(LogTemp, Warning, TEXT("Spawned hostage was not found!")); return nullptr; }

	// Set hostage ID, PathwayID, and Pathway reference
	SpawnedHostage->SetID(HostageID);
	SpawnedHostage->SetPathwayID(PathwayID);
	SpawnedHostage->SetPathway(Pathway);

	// Get the sprite component of the spawned hostage
	UPaperSpriteComponent* HostageSprite = SpawnedHostage->FindComponentByClass<UPaperSpriteComponent>();

	if(!HostageSprite) { UE_LOG(LogTemp, Warning, TEXT("Hostage sprite COMPONENT was not found!")); return nullptr; }

	if(!HostageSprites[HostageID]) { UE_LOG(LogTemp, Warning, TEXT("The hostage sprite value was not found!")); return nullptr; }

	// Set sprite value based on hostage ID
	HostageSprite->SetSprite(HostageSprites[HostageID]);

	// Return the reference to the spawned hostage
	return SpawnedHostage;
}

TArray<AEnemy*> UWaveManagementComponent::SpawnEnemies(FVector& SpawningLocation, int32 NumEnemies, int32 PathwayID, TArray<FVector>& Pathway)
{
	// Initialise the array where the spawned enemies will be stocked
	TArray<AEnemy*> Enemies;

	for(int j = 0; j < NumEnemies; j++) // Spawn NumEnemies enemies
	{
		// Set the spawning location of the current enemy to prevent overlaping
		SpawningLocation = SpawningLocation - FVector(CharacterWidth, 0, 0);
		// Save a reference to the spawned enemy
		auto SpawnedEnemy =  GetWorld()->SpawnActor<AEnemy>(SpawningLocation, FRotator(0));

		if(!SpawnedEnemy) { UE_LOG(LogTemp, Warning, TEXT("SpawnedEnemy was not found!")); return Enemies; }
		
		// Set the pathwayID and the pathway of the spawned enemy
		SpawnedEnemy->SetPathwayID(PathwayID);
		SpawnedEnemy->SetPathway(Pathway);

		// Get the spawned enemy sprite component
		UPaperSpriteComponent* EnemySprite = SpawnedEnemy->FindComponentByClass<UPaperSpriteComponent>();

		if(!EnemySprite) { UE_LOG(LogTemp, Warning, TEXT("Enemy sprite COMPONENT was not found!")); return Enemies; }
		
		if(EnemySprites.Num() < 1) { UE_LOG(LogTemp, Warning, TEXT("The enemy sprites array is empty!")); return Enemies; }

		// Set new sprite value 
		EnemySprite->SetSprite(EnemySprites[0]);

		// Save spawned enemy reference in the enemies array
		Enemies.Add(SpawnedEnemy);
	}
	// Return the array with the spawned enemies references
	return Enemies;
}

bool UWaveManagementComponent::IsPathwayFree(int32 PathwayID, TArray<AActor*>& FoundHostages, TArray<AActor*>& FoundEnemies)
{	
	for(auto Hostage : FoundHostages)
	{
		if(PathwayID == Cast<AHostage>(Hostage)->GetPathwayID())
			return false;
	}

	for(auto Enemy : FoundEnemies)
	{
		if(PathwayID == Cast<AEnemy>(Enemy)->GetPathwayID())
			return false;
	}

	return true;
}

bool UWaveManagementComponent::IsHostageOnScreen(int32 HostageID, TArray<AActor*>& FoundHostages)
{	
	for(auto Hostage : FoundHostages)
	{
		if(HostageID == Cast<AHostage>(Hostage)->GetID())
			return true;
	}

	return false;
}

void UWaveManagementComponent::LoadHostageSprites()
{
	TArray<UObject*> HostageTextures;
	EngineUtils::FindOrLoadAssetsByPath(TEXT("/Game/Assets/Images/Hostages"), HostageTextures, EngineUtils::ATL_Regular);

	for (auto Asset : HostageTextures)
	{
		UPaperSprite* Sprite = Cast<UPaperSprite>(Asset);
		if (Sprite != nullptr)
			HostageSprites.Add(Sprite);
	}
}

void UWaveManagementComponent::LoadEnemySprites()
{
	TArray<UObject*> EnemyTextures;
	EngineUtils::FindOrLoadAssetsByPath(TEXT("/Game/Assets/Images/Enemy"), EnemyTextures, EngineUtils::ATL_Regular);

	for (auto Asset : EnemyTextures)
	{
		UPaperSprite* Sprite = Cast<UPaperSprite>(Asset);
		if (Sprite != nullptr)
			EnemySprites.Add(Sprite);
	}
}



