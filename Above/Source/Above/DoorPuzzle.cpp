// Fill out your copyright notice in the Description page of Project Settings.

#include "Above.h"
#include "DoorPuzzle.h"


// Sets default values
ADoorPuzzle::ADoorPuzzle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mPointerTarget = nullptr;
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
	/*
	if (mPointerTarget != nullptr) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Trigger: %s"), *mPointerTarget->ToString()));
		DrawDebugLine(GetWorld(), FVector(0, 0, 0), *mPointerTarget, FColor(0, 0, 255), false, -1, 0, 12.333);
	}
	*/
}
 
void ADoorPuzzle::InteractWithTrigger(int32 triggerNum, FVector& vectorPointer) {
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Trigger: %d"), triggerNum));

	mPointerTarget = &vectorPointer;

	// Check if button is already pressed
	if (!mButtonOrder.Contains(triggerNum)) {
		mButtonOrder.Push(triggerNum);
		LightButton(triggerNum);
	}

	// Check if all buttons have been pressed
	if (mButtonOrder.Num() >= 5) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Array size 5"));

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
	}
}

// Empty pressed buttons on let go of mouse button
void ADoorPuzzle::EndHoldButton() {
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Dropped trigger"));
	mButtonOrder.Empty();
}

void ADoorPuzzle::Unlock_Implementation() {

}

void ADoorPuzzle::LightButton_Implementation(int32 buttonNum) {

}