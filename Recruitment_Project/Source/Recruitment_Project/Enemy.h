// Copyright Cesar Molto Morilla

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy.generated.h"

UCLASS()
class RECRUITMENT_PROJECT_API AEnemy : public AActor
{
	GENERATED_BODY()

	int32 PathwayID = -1;
	
public:	
	// Sets default values for this actor's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	int32 GetPathwayID();
	void SetPathwayID(int32 IDToSet);

};
