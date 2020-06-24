// Copyright Cesar Molto Morilla

#include "ScoringComponent.h"
#include "Hostage.h"
#include "Enemy.h"
#include "Gem.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UScoringComponent::UScoringComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

void UScoringComponent::UpdateScore(AActor* HitActor)
{
	auto Class = HitActor->GetClass();

	if(Class == AHostage::StaticClass())
	{
		Cast<AHostage>(HitActor)->SetState(EHostageState::Dead);
		KilledHostages ++;
	}
	else if(Class == AEnemy::StaticClass())
	{
		Cast<AEnemy>(HitActor)->KillEnemy();
		KilledEnemies ++;
	}
	else if(Class == AGem::StaticClass())
	{
		HitActor->Destroy();
		CollectedGems ++;
	}
}

int32 UScoringComponent::GetFreedHostages()
{
	// Init variable to return
	int32 FreedHostages = 0;

	// Find all hostages on the screen
	TArray<AActor*> FoundHostages;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AHostage::StaticClass(), FoundHostages);

	for(auto Hostage : FoundHostages) // Iterates through all the hostages in the world
	{
		if(EHostageState::Free == Cast<AHostage>(Hostage)->GetHostageState()) // Checks the current hostage has been freed
			FreedHostages ++;
	}

	return FreedHostages;
}

int32 UScoringComponent::GetKilledHostages() const
{
	return KilledHostages;
}

int32 UScoringComponent::GetKilledEnemies() const
{
	return KilledEnemies;
}

int32 UScoringComponent::GetCollectedGems() const
{
	return CollectedGems;
}

