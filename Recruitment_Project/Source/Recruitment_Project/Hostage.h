// Copyright Cesar Molto Morilla

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Hostage.generated.h"

// Forward declarations
class AEnemy;

// Enum for hostage state
UENUM()
enum class EHostageState : uint8
{
	Alive,
	Free,
	Dead
};

UCLASS()
class RECRUITMENT_PROJECT_API AHostage : public AActor
{
	GENERATED_BODY()

	// Hostage identification. Used to recognize the hostage --> 
	int32 ID = -1;
	// Pathway identification. Identificates the pathway where the hostage has been spawned
	int32 PathwayID = -1;

	// Reference to the pathway the hostage has to follow
	TArray<FVector> Pathway;

	// Movement speed 
	int32 Speed = 70;
	// Movement location index. Used to iterate through the Pathway locations
	FVector NextLocation = FVector(0);
	float AcceptanceRadius = 0.5f;
	int32 PathwayIndex = 0;

	// References to the back and front enemy
	AEnemy* FrontEnemy = nullptr;
	AEnemy* BackEnemy = nullptr;

	// Top-Rigth screen location. The hostage is placed here when its dead or free
	FVector FreedomLocation;

	// Hostage state reference
	EHostageState HostageState = EHostageState::Alive;
	
public:	
	// Sets default values for this pawn's properties
	AHostage();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Makes the hostage move to the location value in NextLocation
	void MoveToNextLocation(float DeltaTime);

	// Update the value of NextLocation based on the hostage state
	void UpdateNextLocation();

	// Sets a reference to the front enemy
	void SetFrontEnemy(AEnemy* EnemyToSet);
	// Sets a reference to the back enemy
	void SetBackEnemy(AEnemy* EnemyToSet);

	// Returns the hostage identification value
	int32 GetID();
	// Sets the hostage identification value
	void SetID(int32 IDToSet);

	// Gets the assigned pathway identification
	int32 GetPathwayID();
	// Sets the pathway identification
	void SetPathwayID(int32 IDToSet);

	// Sets the pathway the hostage is walking through
	void SetPathway(TArray<FVector>& PathwayToSet);

	// Returns the current hostage state
	EHostageState GetHostageState() const;
};
