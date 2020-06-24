// Copyright Cesar Molto Morilla

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Hostage.generated.h"

// Forward declarations
class AEnemy;
class UPaperSprite;
class UPaperSpriteComponent;

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

	// Sprite component
	UPaperSpriteComponent* SpriteComponent = nullptr;

	// Sprite to set when the hostages is killed
	UPaperSprite* DeadSprite = nullptr;

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
	float AcceptanceRadius = 1;
	int32 PathwayIndex = 0;

	// References to the back and front enemy
	AEnemy* FrontEnemy = nullptr;
	AEnemy* BackEnemy = nullptr;

	// Top-Rigth screen location. The hostage is placed there when it gets killed or freed
	FVector UILocation;
	FVector UIScale;

	// Hostage state reference
	EHostageState HostageState = EHostageState::Alive;
	
public:	
	// Sets default values for this pawn's properties
	AHostage();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void InitHostage(int32 IDToSet, int32 PathwayIDToSet, TArray<FVector>& PathwayToSet, int32 CharacterWidth);

	// Makes the hostage move to the location value in NextLocation
	void MoveToNextLocation(float DeltaTime);

	// Update the value of NextLocation based on the hostage state
	void UpdateNextLocation();

	// Sets the UI location on the top-right corner of the screen
	void SetUILocationAndScale(int32 CharacterWidth);

	// Sets a reference to the front enemy
	void SetFrontEnemy(AEnemy* EnemyToSet);
	// Sets a reference to the back enemy
	void SetBackEnemy(AEnemy* EnemyToSet);

	// Returns the hostage identification value
	int32 GetID();

	// Gets the assigned pathway identification
	int32 GetPathwayID();

	// Sets the value of the Dead sprite variable
	void SetDeadSprite(UPaperSprite* SpriteToSet);

	// Sets a new hostage state
	void SetState(EHostageState StateToSet);

	// Returns the current hostage state
	EHostageState GetHostageState() const;

	// Checks if the front and back enemies are still alive
	void CheckEnemies();

	void InitUILocationAndScale(int32 CharacterWidth);
};
