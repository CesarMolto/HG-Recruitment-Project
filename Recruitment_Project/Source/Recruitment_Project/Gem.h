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

	UPaperSpriteComponent* SpriteComponent = nullptr;
	
public:	
	// Sets default values for this actor's properties
	AGem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
