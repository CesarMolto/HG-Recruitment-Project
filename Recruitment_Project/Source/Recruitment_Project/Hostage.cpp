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
	MoveToNextLocation(DeltaTime);
}

void AHostage::MoveToNextLocation(float DeltaTime)
{
	// Calculate DeltaSpeed to have a framerate independent movement
	float DeltaSpeed = Speed * DeltaTime;

	// Initialise NextLocation for the first time with the first value of the Pathway variable
	if(NextLocation.IsZero() && PathwayIndex < Pathway.Num() - 1)
		NextLocation = Pathway[PathwayIndex];

	// Get current location of the actor
	FVector CurrentLocation = GetActorLocation();

	// Calculate distance between current and next location on the X and Z Axis
	float XDistance = FGenericPlatformMath::Abs(NextLocation.X - CurrentLocation.X);
	float ZDistance = FGenericPlatformMath::Abs(NextLocation.Z - CurrentLocation.Z);

	// Normalize the distances
	FVector2D DeltaVector = FVector2D(XDistance, ZDistance);
	DeltaVector.Normalize();

	// Get the delta speed for each axis
	float XDeltaSpeed = DeltaSpeed * DeltaVector.X;
	float ZDeltaSpeed = DeltaSpeed * DeltaVector.Y;

	// Move on the X axis
	if(XDistance > AcceptanceRadius)
	{
		if(CurrentLocation.X < NextLocation.X)
			CurrentLocation += FVector(XDeltaSpeed, 0, 0);
		else
			CurrentLocation -= FVector(XDeltaSpeed, 0, 0);
	}

	// Move on the Z axis
	if(ZDistance > AcceptanceRadius)
	{
		if(CurrentLocation.Z < NextLocation.Z)
			CurrentLocation += FVector(0, 0, ZDeltaSpeed);
		else
			CurrentLocation -= FVector(0, 0, ZDeltaSpeed);
	}

	// Already on the desired location; Update next location value
	if(XDistance < AcceptanceRadius && ZDistance < AcceptanceRadius)
	{
		// Update next location
		UpdateNextLocation();
	}
	else // Not yet on the desired location
	{
		// Update current actor's location
		SetActorLocation(CurrentLocation);
	}
}

void AHostage::UpdateNextLocation()
{
	if(HostageState == EHostageState::Alive)
	{
		if(PathwayIndex < Pathway.Num() - 1)
		{
			PathwayIndex ++;
			NextLocation = Pathway[PathwayIndex];
		}
		else if(PathwayIndex == Pathway.Num() - 1)
		{
			PathwayIndex ++;
			NextLocation += FVector(100, 0, 0);
		}
		else if(PathwayIndex == Pathway.Num())
		{
			Destroy();
		}
	}
	else if(HostageState == EHostageState::Free || HostageState == EHostageState::Dead)
	{
		NextLocation = GetActorLocation();
	}
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

void AHostage::SetPathway(TArray<FVector>& PathwayToSet)
{
	Pathway = PathwayToSet;
}


