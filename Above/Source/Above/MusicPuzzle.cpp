// Fill out your copyright notice in the Description page of Project Settings.

#include "Above.h"
#include "MusicPuzzle.h"
#include "AboveGameMode.h"
#include "AboveSettings.h"


// Sets default values
AMusicPuzzle::AMusicPuzzle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mNumberOfDiscs = 3;

	// Initiate array with zeros
	for (int32 i = 0; i < mNumberOfDiscs; i++) {
		mDiscIndexArray.Push(0);
	}

	// Initiate array, no propper initiation of arrays in unreal
	int32 tableinit[] = { 3, 4, 2 };
	mDiscIndexRefrenceArray.Append(tableinit, ARRAY_COUNT(tableinit));

	mRotationSpeed = 0.5;

	mDiscTargetAngle.Init(mNumberOfDiscs);
	mDiscCurrentAngle.Init(mNumberOfDiscs);
	mDiscMoveTracker.Init(mNumberOfDiscs);
}

// Called when the game starts or when spawned
void AMusicPuzzle::BeginPlay()
{
	Super::BeginPlay();

	for (int32 i = 0; i < mNumberOfDiscs; i++) {
		mDiscTargetAngle[i] = FVector(mDiscArray[i]->GetComponentRotation().Pitch, mDiscArray[i]->GetComponentRotation().Yaw, mDiscArray[i]->GetComponentRotation().Roll);
	}

	for (int32 i = 0; i < mNumberOfDiscs; i++) {
		mDiscCurrentAngle[i] = FVector(mDiscArray[i]->GetComponentRotation().Pitch, mDiscArray[i]->GetComponentRotation().Yaw, mDiscArray[i]->GetComponentRotation().Roll);
	}

	for (int32 i = 0; i < mNumberOfDiscs; i++) {
		mDiscMoveTracker[i] = 0;
	}
}

// Called every frame
void AMusicPuzzle::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	for (int32 i = 0; i < 3; i++) {
		if (mDiscTargetAngle[i] != mDiscCurrentAngle[i]) {
			mDiscMoveTracker[i] += mRotationSpeed * DeltaTime;
			FVector angle = FMath::Lerp(mDiscCurrentAngle[i], mDiscTargetAngle[i], mMovementCurve->GetFloatValue(mDiscMoveTracker[i]));

			FRotator rot = FRotator::ZeroRotator;
			rot.Add(angle.X, angle.Y, angle.Z);
			mDiscArray[i]->SetRelativeRotation(rot);

			if (mDiscMoveTracker[i] >= 1.0) {
				mDiscCurrentAngle[i] = mDiscTargetAngle[i];
				mDiscMoveTracker[i] = 0;
			}
		}
	}
}

void AMusicPuzzle::RotateDisc(int32 discNum) {
	// Index chosen disc by one
	if (discNum < mDiscIndexArray.Num() && mDiscTargetAngle[discNum] == mDiscCurrentAngle[discNum]) {
		mDiscIndexArray[discNum] = ++mDiscIndexArray[discNum] % 5;
		mDiscTargetAngle[discNum] += FVector(0, 72, 0);
	}
}

void AMusicPuzzle::Activate() {
	// Compare with correct combination
	if (mDiscIndexArray == mDiscIndexRefrenceArray) {
		PlayMusic();

		// Döne
		AAboveGameMode* mode = (AAboveGameMode*)GetWorld()->GetAuthGameMode();
		if (mode != nullptr)
			mode->SetCompleteStatus(this, true);
	}

	else {
		PlayShortMusic(mDiscIndexArray);
	}
}