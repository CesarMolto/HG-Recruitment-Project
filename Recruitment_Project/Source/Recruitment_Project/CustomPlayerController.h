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

	// Scoring component
	UScoringComponent* ScoringComponent;

	// Bullets left
	int32 Bullets = 20;

public:
	ACustomPlayerController();

	// Set ups the player input
	void SetupInputComponent();

	// Handles the click and touch event
	void HandleTouch();

	// Returns the bullet's ammount. Used by the interface widget
	UFUNCTION(BlueprintCallable)
	int32 GetBulletsLeft() const;

	// Indicates if the game should finish or not
	UFUNCTION(BlueprintCallable)
	bool ShouldGameFinish();
	
};
