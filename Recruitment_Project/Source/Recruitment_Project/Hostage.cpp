// Copyright Cesar Molto Morilla


#include "Hostage.h"

// Sets default values
AHostage::AHostage()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHostage::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHostage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHostage::SetPathway(TArray<FVector> PathwayToSet)
{
	Pathway = PathwayToSet;
}

void AHostage::SetFrontEnemy(AEnemy* EnemyToSet)
{
	FrontEnemy = EnemyToSet;
}

void AHostage::SetBackEnemy(AEnemy* EnemyToSet)
{
	BackEnemy = EnemyToSet;
}


int32 AHostage::GetID()
{
	return ID;
}

void AHostage::SetID(int32 IDToSet)
{
	ID = IDToSet;
}

int32 AHostage::GetPathwayID()
{
	return PathwayID;
}

void AHostage::SetPathwayID(int32 IDToSet)
{
	PathwayID = IDToSet;
}

