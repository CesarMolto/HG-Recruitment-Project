// Copyright Cesar Molto Morilla

#include "CustomPlayerController.h"
#include "ScoringComponent.h"
#include "Hostage.h"
#include "Enemy.h"
#include "Gem.h"

ACustomPlayerController::ACustomPlayerController()
{
    bShowMouseCursor = true;

    ScoringComponent = CreateDefaultSubobject<UScoringComponent>(TEXT("ScoringComponent"));
}

void ACustomPlayerController::SetupInputComponent()
{
    // A subclass could create a different InputComponent class but still want the default bindings
	if (!InputComponent)
	{
		InputComponent = NewObject<UInputComponent>(this, TEXT("PlayerInputComponent"));
		InputComponent->RegisterComponent();
	}

    InputComponent->BindAction("Touch", IE_Pressed, this, &ACustomPlayerController::HandleTouch);
}

void ACustomPlayerController::HandleTouch()
{
    if(!ScoringComponent) { return; }

    ScoringComponent->UpdateBullets();

    float XPos = 0, YPos = 0;
    GetMousePosition(XPos, YPos);
    FVector2D MousePosition = FVector2D(XPos, YPos);

    UE_LOG(LogTemp, Warning, TEXT("Mouse position X: %f, Y: %f"), XPos, YPos);

    FHitResult HitResult;
    if(GetHitResultAtScreenPosition(MousePosition, ECollisionChannel::ECC_GameTraceChannel1, false, HitResult))
    {
        AActor* Actor = HitResult.GetActor();
        UE_LOG(LogTemp, Warning, TEXT("Hit Result: %s"), *Actor->GetName());

        if(Actor->GetClass() == AHostage::StaticClass())
        {
            Cast<AHostage>(Actor)->SetState(EHostageState::Dead);
        }
        else if(Actor->GetClass() == AEnemy::StaticClass())
        {
            Cast<AEnemy>(Actor)->KillEnemy();
            ScoringComponent->UpdateKilledEnemies();
        }
        else if(Actor->GetClass() == AGem::StaticClass())
        {
            Actor->Destroy();
            ScoringComponent->UpdateCollectedGems();
        }
    }
}