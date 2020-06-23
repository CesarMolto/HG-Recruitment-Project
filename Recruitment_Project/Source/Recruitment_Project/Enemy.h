// Copyright Cesar Molto Morilla

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy.generated.h"

UCLASS()
class RECRUITMENT_PROJECT_API AEnemy : public AActor
{
	GENERATED_BODY()

	int32 PathwayIndex = 0;
	FVector NextLocation = FVector(0);
	float AcceptanceRadius = 0.5f;

	int32 PathwayID = -1;

	TArray<FVector> Pathway;

	int32 Speed = 70;
	
public:	
	// Sets default values for this actor's properties
	AEnemy();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Makes the hostage move to the location value in NextLocation
	void MoveToNextLocation(float DeltaTime);

	// Update the value of NextLocation to the next location in the Pathway array
	void UpdateNextLocation();
	
	// Gets the assigned pathway identification
	int32 GetPathwayID();
	// Sets the pathway identification
	void SetPathwayID(int32 IDToSet);

	// Sets the pathway the enemy will walk through
	void SetPathway(TArray<FVector>& PathwayToSet);
};
