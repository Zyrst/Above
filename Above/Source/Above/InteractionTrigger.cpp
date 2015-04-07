// Fill out your copyright notice in the Description page of Project Settings.

#include "Above.h"
#include "InteractionTrigger.h"


// Sets default values
AInteractionTrigger::AInteractionTrigger(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mRootComponent = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("RootCompenent"));
	RootComponent = mRootComponent;

	mHoverTextDefaultValue = "Interact";

	// Initialize hover text
	mHoverText = ObjectInitializer.CreateDefaultSubobject<UTextRenderComponent>(this, TEXT("HoverText"));
	mHoverText->AttachParent = mRootComponent;
	mHoverText->SetTextRenderColor(FColor(255, 0, 0));
	mHoverText->SetHiddenInGame(true);
	mHoverText->SetText(mHoverTextDefaultValue);
}

// Called when the game starts or when spawned
void AInteractionTrigger::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AInteractionTrigger::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

// Function overridden in blueprints
void AInteractionTrigger::Interact_Implementation() {
}

// Show text on start of hover
void AInteractionTrigger::StartHover() {
	mHoverText->SetHiddenInGame(false);
}

// Hide text on end of hover
void AInteractionTrigger::EndHover() {
	mHoverText->SetHiddenInGame(true);
}

// End of hold
void AInteractionTrigger::EndHold() {
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("End hold"));
}