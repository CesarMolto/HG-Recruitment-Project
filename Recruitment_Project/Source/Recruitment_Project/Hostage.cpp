// Copyright Cesar Molto Morilla


#include "Hostage.h"
#include "PaperSpriteComponent.h"
#include "GenericPlatform/GenericPlatformMath.h"

// Sets default values
AHostage::AHostage()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UPaperSpriteComponent* SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("HostageSprite"));
	RootComponent = SpriteComponent;
}

// Called every frame
void AHostage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(HostageState == EHostageState::Alive)
		Move(DeltaTime);
}

void MoveToNextLocation(float DeltaTime)
{
	/* float DeltaSpeed = Speed * DeltaTime;

	FVector CurrentLocation = GetActorLocation();

	// Calculate distance between current and next location on the X and Z Axis
	float XDistance = FGenericPlatformMath::Abs(NextLocation.X - CurrentLocation.X);
	float ZDistance = FGenericPlatformMath::Abs(NextLocation.Z - CurrentLocation.Z);

	FVector2D DeltaVector = FVector2D(XDistance, ZDistance).Normalize(0.1f); */

}

void AHostage::Move(float DeltaTime)
{
	// Calculate DeltaSpeed for a framerate independen movement
	float DeltaSpeed = Speed * DeltaTime;

	// Get the current actor location and the next location in the path
	FVector CurrentLocation = GetActorLocation();
	NextLocation = Pathway[NextLocationIndex];

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

void AHostage::SetPathway(TArray<FVector>& PathwayToSet)
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

