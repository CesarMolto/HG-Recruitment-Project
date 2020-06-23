// Copyright Cesar Molto Morilla

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CustomPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class RECRUITMENT_PROJECT_API ACustomPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ACustomPlayerController();

	void SetupInputComponent();

	void HandleTouch();
	
};
