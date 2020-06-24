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

	int32 KilledHostages = 0;
	int32 KilledEnemies = 0;
	int32 CollectedGems = 0;

public:	
	// Sets default values for this component's properties
	UScoringComponent();

	void UpdateScore(AActor* HitActor);	

	UFUNCTION(BlueprintCallable)
	int32 GetFreedHostages();

	UFUNCTION(BlueprintCallable)
	int32 GetKilledHostages() const;

	UFUNCTION(BlueprintCallable)
	int32 GetKilledEnemies() const;

	UFUNCTION(BlueprintCallable)
	int32 GetCollectedGems() const;
};
