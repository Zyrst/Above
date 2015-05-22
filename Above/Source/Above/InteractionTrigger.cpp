// Fill out your copyright notice in the Description page of Project Settings.

#include "Above.h"
#include "InteractionTrigger.h"
#include "AboveSettings.h"


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

	mPointerTarget = nullptr;
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

	if (mPointerTarget != nullptr) {
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Trigger: %s"), *mPointerTarget->ToString()));
	}
}

void AInteractionTrigger::SetPointerTarget(FVector& vectorPointer) {
	mPointerTarget = &vectorPointer;

	if (mPuzzleLockRef != nullptr) {
		mPuzzleLockRef->mPointerTarget = mPointerTarget;
	}
}

FVector& AInteractionTrigger::GetPointerTarget() {
	return *mPointerTarget;
}

// Show text on start of hover
void AInteractionTrigger::StartHover() {
	mHoverText->SetHiddenInGame(false);
	EventStartHover();

	for (int32 i = 0; i < mHighlightMaterials.Num(); i++) 
		mHighlightMaterials[i]->SetScalarParameterValue(mHightlightParameterName, 1.0f);
}

// Hide text on end of hover
void AInteractionTrigger::EndHover() {
	mHoverText->SetHiddenInGame(true);
	EventEndHover();

	for (int32 i = 0; i < mHighlightMaterials.Num(); i++)
		mHighlightMaterials[i]->SetScalarParameterValue(mHightlightParameterName, 0.0f);
}

void AInteractionTrigger::SetHighlightMaterial(UMaterialInstanceDynamic* material) {
	//mHighlightMaterial = material;
	mHighlightMaterials.Add(material);


	AAboveSettings* settings = (AAboveSettings*)GetWorld()->GetWorldSettings();
	for (int32 i = 0; i < mHighlightMaterials.Num(); i++)
		mHighlightMaterials[i]->SetVectorParameterValue(settings->mHighlightColorParameterName, settings->mHighlightColor);
}