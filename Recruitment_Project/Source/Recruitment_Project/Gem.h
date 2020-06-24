// Copyright Cesar Molto Morilla

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gem.generated.h"

// Forward declarations
class UPaperSpriteComponent;

UCLASS()
class RECRUITMENT_PROJECT_API AGem : public AActor
{
	GENERATED_BODY()

	// Sprite component
	UPaperSpriteComponent* SpriteComponent = nullptr;
	
public:	
	// Sets default values for this actor's properties
	AGem();
};
