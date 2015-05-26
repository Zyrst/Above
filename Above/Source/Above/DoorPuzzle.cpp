// Fill out your copyright notice in the Description page of Project Settings.

#include "Above.h"
#include "DoorPuzzle.h"


// Sets default values
ADoorPuzzle::ADoorPuzzle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mPointerTarget = nullptr;
	mContainedLastTrigger = false;
	mDrawLine = false;
}

// Called when the game starts or when spawned
void ADoorPuzzle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADoorPuzzle::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if (mPointerTarget != nullptr && mDrawLine) {
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Trigger: %s"), *mPointerTarget->ToString()));
		//DrawDebugLine(GetWorld(), mLastTriggerLocation, *mPointerTarget, FColor(0, 0, 255), false, -1, 0, 3);
		DrawLine(mLastTriggerLocation, *mPointerTarget);
	}
}
 
void ADoorPuzzle::InteractWithTrigger(int32 triggerNum, FVector newTriggerPos) {
	mContainedLastTrigger = true;

	// Check if button is already pressed
	if (!mButtonOrder.Contains(triggerNum)) {
		if (mButtonOrder.Num() > 0 && mButtonOrder.Num() < 5) {
			DrawStaticLine(mLastTriggerLocation, newTriggerPos);
		}
		mButtonOrder.Push(triggerNum);
		LightButton(triggerNum);
		SoundEventButtonInteract(mButtonOrder.Num());
		mContainedLastTrigger = false;
		mDrawLine = true;
	}

	// Check if all buttons have been pressed
	if (mButtonOrder.Num() >= 5) {
		// Check if buttons pressed in correct order
		mIsInOrder = true;
		for (int32 i = 1; i < mButtonOrder.Num(); i++) {
			if (mButtonOrder[i] <= mButtonOrder[i - 1]) {
				mIsInOrder = false;
			}
		}

		// Unlock if in correct order
		if (mIsInOrder) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Door unlocked"));
			Unlock();
		}

		// Empty pressed buttons
		mButtonOrder.Empty();
		EmptyLines();
		mDrawLine = false;
	}
}

// Empty pressed buttons on let go of mouse button
void ADoorPuzzle::EndHoldButton() {
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Dropped trigger"));
	for (int32 i = 0; i < mButtonOrder.Num(); i++) {
		UnLightButton(i);
	}
	mButtonOrder.Empty();
	mPointerTarget = nullptr;
	EmptyLines();
	mDrawLine = false;
}

void ADoorPuzzle::SetLastTriggerPos(FVector pos) {
	if (!mContainedLastTrigger) {
		mLastTriggerLocation = pos;
	}
}