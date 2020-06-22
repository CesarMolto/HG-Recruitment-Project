// Copyright Cesar Molto Morilla


#include "Enemy.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int32 AEnemy::GetPathwayID()
{
	return PathwayID;
}

void AEnemy::SetPathwayID(int32 IDToSet)
{
	PathwayID = IDToSet;
}


