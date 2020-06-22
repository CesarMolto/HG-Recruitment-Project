// Copyright Cesar Molto Morilla

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Hostage.generated.h"

// Forward declarations
class AEnemy;

UCLASS()
class RECRUITMENT_PROJECT_API AHostage : public AActor
{
	GENERATED_BODY()

	int32 ID = -1;
	int32 PathwayID = -1;

	TArray<FVector> Pathway;

	UPROPERTY(VisibleAnywhere, Category="Setup")
	AEnemy* FrontEnemy = nullptr;
	UPROPERTY(VisibleAnywhere, Category="Setup")
	AEnemy* BackEnemy = nullptr;
	
public:	
	// Sets default values for this actor's properties
	AHostage();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetPathway(TArray<FVector> PathwayToSet);

	void SetFrontEnemy(AEnemy* EnemyToSet);
	void SetBackEnemy(AEnemy* EnemyToSet);

	int32 GetID();
	void SetID(int32 IDToSet);

	int32 GetPathwayID();
	void SetPathwayID(int32 IDToSet);

};
