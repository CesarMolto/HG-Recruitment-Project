// Copyright Cesar Molto Morilla


#include "Gem.h"
#include "PaperSpriteComponent.h"

// Sets default values
AGem::AGem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Intialise sprite component
	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("SpriteComponent"));
	// Set sprite component as root 
	RootComponent = SpriteComponent;
}


