// Copyright Cesar Molto Morilla


#include "Hostage.h"
#include "Enemy.h"
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"
#include "GenericPlatform/GenericPlatformMath.h"

// Sets default values
AHostage::AHostage()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Intialise sprite component
	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("SpriteComponent"));
	// Set sprite component as root 
	RootComponent = SpriteComponent;
}

// Called every frame
void AHostage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// Hostage movement
	MoveToNextLocation(DeltaTime);
	// Check if front and back enemies are still alive
	CheckEnemies();
}

void AHostage::InitHostage(int32 IDToSet, int32 PathwayIDToSet, TArray<FVector>& PathwayToSet, int32 CharacterWidth)
{
	// Set hostage ID
	ID = IDToSet;
	// Set pathway ID
	PathwayID = PathwayIDToSet;
	// Set Pathway reference
	Pathway = PathwayToSet;

	// Init UI Location and Scale
	InitUILocationAndScale(CharacterWidth);
}

void AHostage::InitUILocationAndScale(int32 CharacterWidth)
{	
	// Get Screen width and height
	int32 ScreenWidth = Pathway.Num() * CharacterWidth;
	int32 ScreenHeight = ScreenWidth;

	// Initialise UIScale
	UIScale = FVector((float)ScreenWidth / 800.0f); // 800 is the maximus width of the screen

	// Calculate UILocation X and Z component
	int32 XUILocation = (ScreenWidth / 2) - ((ID + 1)  * CharacterWidth / 2);
	int32 ZUILocation = ScreenHeight / 2 - CharacterWidth / 2;

	// Initialise UILoction
	UILocation = FVector(XUILocation, -ID, ZUILocation);
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
	if(HostageState == EHostageState::Alive) // The hostage is alive
	{
		if(PathwayIndex < Pathway.Num() - 1) // The hostage is still going through the pathway locations
		{
			PathwayIndex ++;
			NextLocation = Pathway[PathwayIndex]; // Update NextLocation with the next Pathway location value
		}
		else if(PathwayIndex == Pathway.Num() - 1) // The hostage is in the last location of the Pathway
		{
			PathwayIndex ++;
			NextLocation += FVector(100, 0, 0); // Update NextLocation one last time to make the hostage move out of the screen
		}
		else if(PathwayIndex == Pathway.Num()) // The hostage is already out of the screen
		{
			// Destroy de hostage actor
			Destroy();
		}
	}
	else if(HostageState == EHostageState::Free || HostageState == EHostageState::Dead) // The hostage has to move to UILocation
	{
		// Assign UILocation value to the NextLocaiton variable
		NextLocation = UILocation;
		// Set Actor Location to NextLocation (Makes sure that the hostage does not shake once it has reached the UILocation)
		SetActorLocation(NextLocation);
	}
}

void AHostage::CheckEnemies()
{
	if(FrontEnemy && BackEnemy)
	{
		if(!FrontEnemy->IsEnemyAlive() && !BackEnemy->IsEnemyAlive() && HostageState == EHostageState::Alive)
			SetState(EHostageState::Free);
	}
}

void AHostage::SetDeadSprite(UPaperSprite* SpriteToSet)
{
	if(!SpriteToSet) { return; }
	DeadSprite = SpriteToSet;
}

void AHostage::SetState(EHostageState StateToSet)
{
	if(HostageState == EHostageState::Alive) // If the character is Alive
	{
		// Change state, move character to UILocation, and set UIScale
		HostageState = StateToSet;
		NextLocation = UILocation;
		SetActorScale3D(UIScale);

		// Increment movement speed
		Speed = 300;
		
		// Reset pathway ID
		PathwayID = -1;

		if(StateToSet == EHostageState::Dead) // If character was killed
		{
			if(SpriteComponent && DeadSprite)
				SpriteComponent->SetSprite(DeadSprite); // Set hostage dead sprite
		}	
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

int32 AHostage::GetPathwayID()
{
	return PathwayID;
}

EHostageState AHostage::GetHostageState() const
{
	return HostageState;
}


