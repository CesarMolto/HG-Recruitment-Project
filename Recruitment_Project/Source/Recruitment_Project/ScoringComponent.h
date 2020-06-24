// Copyright Cesar Molto Morilla

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ScoringComponent.generated.h"

// Forward declarations
class AActor;

UCLASS()
class RECRUITMENT_PROJECT_API UScoringComponent : public UActorComponent
{
	GENERATED_BODY()

	// Number of killed hostages
	int32 KilledHostages = 0;
	// Number of killed enemies
	int32 KilledEnemies = 0;
	// Number of collected gems
	int32 CollectedGems = 0;

public:	
	// Sets default values for this component's properties
	UScoringComponent();

	// Updates the score variable based on the class hit actor
	void UpdateScore(AActor* HitActor);	

	// Get the number of freed hostages
	UFUNCTION(BlueprintCallable)
	int32 GetFreedHostages();

	// Feturns the number of killed hostages
	UFUNCTION(BlueprintCallable)
	int32 GetKilledHostages() const;

    // Returns the number of killed enemies
	UFUNCTION(BlueprintCallable)
	int32 GetKilledEnemies() const;

	// Returns the number of collected Gems
	UFUNCTION(BlueprintCallable)
	int32 GetCollectedGems() const;
};
