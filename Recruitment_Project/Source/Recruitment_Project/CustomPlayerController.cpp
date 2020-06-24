// Copyright Cesar Molto Morilla

#include "CustomPlayerController.h"
#include "ScoringComponent.h"

ACustomPlayerController::ACustomPlayerController()
{
    // Show cursor in game
    bShowMouseCursor = true;

    // Init scoring component
    ScoringComponent = CreateDefaultSubobject<UScoringComponent>(TEXT("ScoringComponent"));
}

void ACustomPlayerController::SetupInputComponent()
{
	if (!InputComponent) // Checks if there is already an Input component
	{
        // If not create it
		InputComponent = NewObject<UInputComponent>(this, TEXT("PlayerInputComponent"));
		InputComponent->RegisterComponent();
	}

    // Bind the action of touching or clicking on the screen
    InputComponent->BindAction("Touch", IE_Pressed, this, &ACustomPlayerController::HandleTouch);
}

void ACustomPlayerController::HandleTouch()
{
    // Lower the ammount of bullets by one
    Bullets -= 1;

    // Get click position on the screen
    float XPos = 0, YPos = 0;
    GetMousePosition(XPos, YPos);
    FVector2D MousePosition = FVector2D(XPos, YPos);

    //Get hit actor by the click on the screen
    FHitResult HitResult;
    if(GetHitResultAtScreenPosition(MousePosition, ECollisionChannel::ECC_GameTraceChannel1, false, HitResult))
    {
        AActor* HitActor = HitResult.GetActor();

        if(!ScoringComponent) { return; }
        ScoringComponent->UpdateScore(HitActor); // Send actor to the UpdateScore method of the Scoring component
    }
}

int32 ACustomPlayerController::GetBulletsLeft() const
{
    return Bullets;
}

bool ACustomPlayerController::ShouldGameFinish()
{
    if(Bullets == 0 || ScoringComponent->GetFreedHostages() == 5) // Check ff any of the coditions for finishing the game is true
        return true;

    return false;
}