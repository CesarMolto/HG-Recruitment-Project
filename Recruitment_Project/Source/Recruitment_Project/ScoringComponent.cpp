// Copyright Cesar Molto Morilla


#include "ScoringComponent.h"

// Sets default values for this component's properties
UScoringComponent::UScoringComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UScoringComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UScoringComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UScoringComponent::UpdateBullets()
{
	Bullets --;
}

void UScoringComponent::UpdateKilledEnemies()
{
	KilledEnemies ++;
}

void UScoringComponent::UpdateCollectedGems()
{
	CollectedGems ++;
}

bool UScoringComponent::ShouldGameEnd()
{
	if(Bullets == 0)
		return true;
	
	return false;
}

