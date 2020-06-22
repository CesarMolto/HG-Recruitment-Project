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
	TerrainLocations = TerrainLocationsToSet;
	LoadHostageSprites();
	LoadEnemySprites();
}

void UWaveManagementComponent::SpawnWaves()
{
	// Spawn as many waves as paths the terrain has
	for(int32 i = 0; i < TerrainLocations.Num(); i++)
	{
		TArray<AActor*> FoundHostages;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AHostage::StaticClass(), FoundHostages);

		TArray<AActor*> FoundEnemies;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemy::StaticClass(), FoundEnemies);

		int32 RandomPath = FMath::RandRange(0, TerrainLocations.Num() - 1);

		if(IsPathwayFree(RandomPath, FoundHostages, FoundEnemies))
		{
			FVector SpawningLocation = TerrainLocations[RandomPath].TileLocations[0];

			int32 NumEnemies = FMath::RandRange(2, 4);
			int32 RandomHostage = FMath::RandRange(0, 4);

			// Spawn front enemies
			TArray<AEnemy*> FrontEnemies = SpawnEnemies(SpawningLocation, NumEnemies / 2, RandomPath);

			if(FrontEnemies.Num() <= 0) { return; }

			AEnemy* FrontEnemy = FrontEnemies[FrontEnemies.Num() - 1];

			// Spawn hostage if it is not already on the screen
			AHostage* Hostage = nullptr;
			if(!IsHostageOnScreen(RandomHostage, FoundHostages))
			{
				Hostage = SpawnHostage(SpawningLocation, RandomHostage, RandomPath);
			}

			// Spawn back enemies
			TArray<AEnemy*> BackEnemies = SpawnEnemies(SpawningLocation, NumEnemies / 2, RandomPath);

			if(BackEnemies.Num() <= 0) { return; }

			AEnemy* BackEnemy = BackEnemies[0];

			if(Hostage && FrontEnemy && BackEnemy)
			{
				Hostage->SetFrontEnemy(FrontEnemy);
				Hostage->SetBackEnemy(BackEnemy);
			}
		}
	}
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

bool UWaveManagementComponent::IsHostageOnScreen(int32 HostageID, TArray<AActor*>& FoundHostages)
{	
	for(auto Hostage : FoundHostages)
	{
		if(HostageID == Cast<AHostage>(Hostage)->GetID())
			return true;
	}

	return false;
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

AHostage* UWaveManagementComponent::SpawnHostage(FVector& SpawningLocation, int32 HostageID, int32 PathwayID)
{
	if(!HostageBP) { UE_LOG(LogTemp, Warning, TEXT("Hostage blueprint to spawn was not found!")); return nullptr; }

	SpawningLocation = SpawningLocation - FVector(CharacterWidth, 0, 0);
	auto SpawnedHostage =  GetWorld()->SpawnActor<AHostage>(HostageBP, SpawningLocation, FRotator(0));

	if(!SpawnedHostage) { UE_LOG(LogTemp, Warning, TEXT("Spawned hostage was not found!")); return nullptr; }

	SpawnedHostage->SetID(HostageID);
	SpawnedHostage->SetPathwayID(PathwayID);

	UPaperSpriteComponent* HostageSprite = SpawnedHostage->FindComponentByClass<UPaperSpriteComponent>();

	if(!HostageSprite) { UE_LOG(LogTemp, Warning, TEXT("Hostage sprite COMPONENT was not found!")); return nullptr; }

	HostageSprite->SetSprite(HostageSprites[HostageID]);

	return SpawnedHostage;
}

TArray<AEnemy*> UWaveManagementComponent::SpawnEnemies(FVector& SpawningLocation, int32 NumEnemies, int32 PathwayID)
{
	TArray<AEnemy*> Enemies;

	for(int j = 0; j < NumEnemies; j++)
	{
		if(!EnemyBP) { UE_LOG(LogTemp, Warning, TEXT("Enemy blueprint to spawn was not found!")); return Enemies; }

		SpawningLocation = SpawningLocation - FVector(CharacterWidth, 0, 0);
		auto SpawnedEnemy =  GetWorld()->SpawnActor<AEnemy>(EnemyBP, SpawningLocation, FRotator(0));

		if(!SpawnedEnemy) { UE_LOG(LogTemp, Warning, TEXT("SpawnedEnemy was not found!")); return Enemies; }
		
		SpawnedEnemy->SetPathwayID(PathwayID);

		Enemies.Add(SpawnedEnemy);
	}

	return Enemies;
}



