// Copyright Cesar Molto Morilla

#include "CustomPlayerController.h"
#include "ScoringComponent.h"

ACustomPlayerController::ACustomPlayerController()
{
    bShowMouseCursor = true;
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
    float XPos = 0, YPos = 0;

    GetMousePosition(XPos, YPos);

    FVector2D MousePosition = FVector2D(XPos, YPos);
    FHitResult HitResult;

    if(GetHitResultAtScreenPosition(MousePosition, ECollisionChannel::ECC_GameTraceChannel1, false, HitResult))
    {
        UE_LOG(LogTemp, Warning, TEXT("Hit Result: %s"), *HitResult.GetActor()->GetName());
    }
}