// Copyright Cesar Molto Morilla

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CustomPlayerController.generated.h"

// Forward declarations
class UScoringComponent;

/**
 * Class responsible for managing the input of the player and the scoring of the game
 */
UCLASS()
class RECRUITMENT_PROJECT_API ACustomPlayerController : public APlayerController
{
	GENERATED_BODY()

	UScoringComponent* ScoringComponent;

	int32 Bullets = 20;

public:
	ACustomPlayerController();

	void SetupInputComponent();

	void HandleTouch();

	UFUNCTION(BlueprintCallable)
	int32 GetBulletsLeft() const;

	UFUNCTION(BlueprintCallable)
	bool ShouldGameFinish();
	
};
