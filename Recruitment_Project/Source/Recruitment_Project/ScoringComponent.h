// Copyright Cesar Molto Morilla

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ScoringComponent.generated.h"


UCLASS()
class RECRUITMENT_PROJECT_API UScoringComponent : public UActorComponent
{
	GENERATED_BODY()

	int32 Bullets = 20;

	int32 FreedHostages = 0;
	int32 KilledEnemies = 0;
	int32 CollectedGems = 0;

public:	
	// Sets default values for this component's properties
	UScoringComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void UpdateBullets();
	void UpdateKilledEnemies();
	void UpdateCollectedGems();

	bool ShouldGameEnd();	
};
