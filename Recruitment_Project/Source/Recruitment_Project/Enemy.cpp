// Copyright Cesar Molto Morilla


#include "Enemy.h"
#include "PaperSpriteComponent.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UPaperSpriteComponent* SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("EnemySprite"));
	RootComponent = SpriteComponent;
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
	Move(DeltaTime);

}

void AEnemy::Move(float DeltaTime)
{
	// Calculate DeltaSpeed for a framerate independen movement
	float DeltaSpeed = Speed * DeltaTime;

	// Get the current actor location and the next location in the path
	FVector CurrentLocation = GetActorLocation();
	FVector NextLocation = Pathway[NextLocationIndex];

	if(NextLocationIndex == Pathway.Num() - 1)
		NextLocation += FVector(100, 0, 0);	

	// Calculate distance between current and next location on the X and Z Axis
	float XDistance = FGenericPlatformMath::Abs(NextLocation.X - CurrentLocation.X);
	float ZDistance = FGenericPlatformMath::Abs(NextLocation.Z - CurrentLocation.Z);

	float XDeltaSpeed = DeltaSpeed;
	float ZDeltaSpeed = DeltaSpeed * 0.5f;

	if(XDistance < 0.5f && ZDistance < 0.5f)
	{
		if(NextLocationIndex < Pathway.Num() - 1)
			NextLocationIndex ++;
		else
			Destroy();		
	}
	else
	{
		if(CurrentLocation.X < NextLocation.X)
			CurrentLocation += FVector(XDeltaSpeed, 0, 0);
		else
			CurrentLocation -= FVector(XDeltaSpeed, 0, 0);

		if(CurrentLocation.Z < NextLocation.Z)
			CurrentLocation += FVector(0, 0, ZDeltaSpeed);
		else
			CurrentLocation -= FVector(0, 0, ZDeltaSpeed);

		SetActorLocation(CurrentLocation);
	}
}

void AEnemy::SetPathway(TArray<FVector>& PathwayToSet)
{
	Pathway = PathwayToSet;
}

int32 AEnemy::GetPathwayID()
{
	return PathwayID;
}

void AEnemy::SetPathwayID(int32 IDToSet)
{
	PathwayID = IDToSet;
}


