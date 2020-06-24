// Copyright Cesar Molto Morilla

#include "CustomPlayerController.h"
#include "ScoringComponent.h"

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
    Bullets -= 1;

    float XPos = 0, YPos = 0;
    GetMousePosition(XPos, YPos);
    FVector2D MousePosition = FVector2D(XPos, YPos);

    UE_LOG(LogTemp, Warning, TEXT("Mouse position X: %f, Y: %f"), XPos, YPos);

    FHitResult HitResult;
    if(GetHitResultAtScreenPosition(MousePosition, ECollisionChannel::ECC_GameTraceChannel1, false, HitResult))
    {
        AActor* HitActor = HitResult.GetActor();
        UE_LOG(LogTemp, Warning, TEXT("Hit Result: %s"), *HitActor->GetName());

        if(!ScoringComponent) { return; }
        ScoringComponent->UpdateScore(HitActor);
    }
}

int32 ACustomPlayerController::GetBulletsLeft() const
{
    return Bullets;
}

bool ACustomPlayerController::ShouldGameFinish()
{
    if(Bullets == 0 || ScoringComponent->GetFreedHostages() == 5)
        return true;

    return false;
}