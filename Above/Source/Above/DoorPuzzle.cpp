// Fill out your copyright notice in the Description page of Project Settings.

#include "Above.h"
#include "DoorPuzzle.h"


// Sets default values
ADoorPuzzle::ADoorPuzzle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mPointerTarget = nullptr;
	mDrawLine = false;
	mContainedLastTrigger = false;
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
		DrawDebugLine(GetWorld(), mLastTriggerLocation, *mPointerTarget, FColor(0, 0, 255), false, -1, 0, 3);
	}

	for (int32 i = 0; i < mLineArray.Num(); i++) {
		DrawDebugLine(GetWorld(), mLineArray[i].x, mLineArray[i].y, FColor(0, 0, 255), false, -1, 0, 3);
	}
}
 
void ADoorPuzzle::InteractWithTrigger(int32 triggerNum, FVector newTriggerPos) {
	mContainedLastTrigger = true;

	// Check if button is already pressed
	if (!mButtonOrder.Contains(triggerNum)) {
		if (mButtonOrder.Num() > 0 && mButtonOrder.Num() < 5) {
			mLineArray.Add(DuoFVector(mLastTriggerLocation, newTriggerPos));
		}
		mButtonOrder.Push(triggerNum);
		LightButton(triggerNum);
		SoundEventButtonInteract(mButtonOrder.Num());
		mDrawLine = true;
		mContainedLastTrigger = false;
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
		mLineArray.Empty();
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
	mLineArray.Empty();
	mDrawLine = false;
}

void ADoorPuzzle::SetLastTriggerPos(FVector pos) {
	if (!mContainedLastTrigger) {
		mLastTriggerLocation = pos;
	}
}