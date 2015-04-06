// Fill out your copyright notice in the Description page of Project Settings.

#include "Above.h"
#include "InteractionTrigger.h"


// Sets default values
AInteractionTrigger::AInteractionTrigger(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mHoverTextValue = "Cunt";

	// Initialize hover text
	mHoverText = ObjectInitializer.CreateDefaultSubobject<UTextRenderComponent>(this, TEXT("HoverText"));
	mHoverText->AttachParent = GetRootComponent();
	mHoverText->SetTextRenderColor(FColor(255, 0, 0));
	mHoverText->SetVisibility(false);
	mHoverText->SetText(mHoverTextValue);
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

void AInteractionTrigger::Interact(){
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta , FString::Printf(TEXT("Interaction called: %s"), *this->GetName()));


}

void AInteractionTrigger::StartHover() {
	mHoverText->SetVisibility(true);
}

void AInteractionTrigger::EndHover() {
	mHoverText->SetVisibility(false);
}