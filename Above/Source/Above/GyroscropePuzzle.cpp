// Fill out your copyright notice in the Description page of Project Settings.

#include "Above.h"
#include "GyroscropePuzzle.h"
#include "AboveSettings.h"


// Sets default values
AGyroscropePuzzle::AGyroscropePuzzle(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer),
	mOuterCurrentAngle(0, 0, 0),
	mOuterTargetAngle(0, 0, 0),
	mMiddleCurrentAngle(0, 0, 0),
	mMiddleTargetAngle(0, 0, 0), 
	mInnerCurrentAngle(0, 0, 0),
	mInnerTargetAngle(0, 0, 0) {

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mRoot = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("Scene root"));
	SetRootComponent(mRoot);

	mOuterSphere = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("OuterCircle"));
	mMiddleSphere = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("MiddleCircle"));
	mInnerSphere = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("InnerCircle"));

	mOuterSphere->AttachParent = mRoot;
	mMiddleSphere->AttachParent = mOuterSphere;
	mInnerSphere->AttachParent = mMiddleSphere;
}

void AGyroscropePuzzle::OnConstruction(const FTransform& Transform) {
	mInnerSphere->SetSphereRadius(mInnerCircleRadius);
	mMiddleSphere->SetSphereRadius(mMiddleCircleRadius);
	mOuterSphere->SetSphereRadius(mOuterCircleRadius);

	// Set parent (cannot do this in constructor since that crashes on play)
	mOuterSphere->AttachParent = mRoot;
	mMiddleSphere->AttachParent = mOuterSphere;
	mInnerSphere->AttachParent = mMiddleSphere;

	// Set angle
	mInnerCurrentAngle = FVector(InnerAngle, 0, 0);
	mMiddleCurrentAngle = FVector(0, 0, MiddleAngle);
	mOuterCurrentAngle = FVector(0, OuterAngle, 0);

	FRotator rot = FRotator::ZeroRotator;
	rot.Add(mInnerCurrentAngle.X, mInnerCurrentAngle.Y, mInnerCurrentAngle.Z);
	mInnerSphere->SetRelativeRotation(rot);

	rot = FRotator::ZeroRotator;
	rot.Add(mMiddleCurrentAngle.X, mMiddleCurrentAngle.Y, mMiddleCurrentAngle.Z);
	mMiddleSphere->SetRelativeRotation(rot);
	
	rot = FRotator::ZeroRotator;
	rot.Add(mOuterCurrentAngle.X, mOuterCurrentAngle.Y, mOuterCurrentAngle.Z);
	mOuterSphere->SetRelativeRotation(rot);
}

// Called when the game starts or when spawned
void AGyroscropePuzzle::BeginPlay() {
	Super::BeginPlay();

	mOuterSphere->AttachParent = mRoot;
	mMiddleSphere->AttachParent = mOuterSphere;
	mInnerSphere->AttachParent = mMiddleSphere;

	mInnerCurrentAngle = mInnerTargetAngle = FVector(InnerAngle, 0, 0);
	mMiddleCurrentAngle = mMiddleTargetAngle = FVector(0, 0, MiddleAngle);
	mOuterCurrentAngle = mOuterTargetAngle = FVector(0, OuterAngle, 0);

	AAboveSettings* settings = (AAboveSettings*)GetWorld()->GetWorldSettings();
	settings->AddPuzzle(this);
}

// Called every frame
void AGyroscropePuzzle::Tick( float DeltaTime ) {
	Super::Tick( DeltaTime );

	if (CinematicMode)
		CinematicUpdate(DeltaTime);
	else
		RegularUpdate(DeltaTime);
}

void AGyroscropePuzzle::RegularUpdate(float DeltaTime) {
	if (!mMovementCurve || !mShouldRotateAnything || mDone)
		return;

	UpdateRotation(DeltaTime);

	if (!mShouldRotateInner && !mShouldRotateMiddle && !mShouldRotateOuter) {
		//SoundEventEndRotate();
		mShouldRotateAnything = false;

		if (mInnerCurrentAngle.X >= 360) {
			mInnerCurrentAngle.X -= 360;
			mInnerTargetAngle.X -= 360;
			FRotator rot = FRotator::ZeroRotator;
			rot.Add(mInnerTargetAngle.X, 0, 0);
			mInnerSphere->SetRelativeRotation(rot);
		}
		
		if (mMiddleCurrentAngle.Z >= 360) {
			mMiddleCurrentAngle.Z -= 360;
			mMiddleTargetAngle.Z -= 360;
			FRotator rot = FRotator::ZeroRotator;
			rot.Add(0, 0, mMiddleTargetAngle.Z);
			mMiddleSphere->SetRelativeRotation(rot);
		}

		if (mOuterCurrentAngle.Y >= 360) {
			mOuterCurrentAngle.Y -= 360;
			mOuterTargetAngle.Y -= 360;
			FRotator rot = FRotator::ZeroRotator;
			rot.Add(0, mOuterTargetAngle.Y, 0);
			mOuterSphere->SetRelativeRotation(rot);
		}

		bool solved = true;
		float d1 = FVector::Dist(mInnerCurrentAngle, FVector(InnerSolveAngle, 0, 0));
		float d2 = FVector::Dist(mMiddleCurrentAngle, FVector(0, 0, MiddleSolveAngle));
		float d3 = FVector::Dist(mOuterCurrentAngle, FVector(0, OuterSolveAngle, 0));

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Levels: %f, %f, %f"), d1, d2, d3));

		solved &= (d1 < 0.1f);
		solved &= (d2 < 0.1f);
		solved &= (d3 < 0.1f);

		if (solved)
			OnSolve();

		if (mLastRotation) {
			mDone = true;
		}
	}
}

void AGyroscropePuzzle::CinematicUpdate(float DeltaTime) {

	mInnerMovementBuffer += InnerSpeed * DeltaTime;
	mMiddleMovementBuffer += MiddleSpeed * DeltaTime;
	mOuterMovementBuffer += OuterSpeed * DeltaTime;

	FRotator rot = FRotator::ZeroRotator;
	rot.Add(0, mOuterMovementBuffer, 0);
	mOuterSphere->SetRelativeRotation(rot);

	rot = FRotator::ZeroRotator;
	rot.Add(0, 0, mMiddleMovementBuffer);
	mMiddleSphere->SetRelativeRotation(rot);

	rot = FRotator::ZeroRotator;
	rot.Add(mInnerMovementBuffer, 0, 0);
	mInnerSphere->SetRelativeRotation(rot);
}

void AGyroscropePuzzle::UpdateRotation(float DeltaTime) {
	if (mShouldRotateOuter && mOuterCurrentAngle != mOuterTargetAngle) {
		mOuterMoveTracker += mRotationSpeed * DeltaTime;
		FVector angle = FMath::Lerp(mOuterCurrentAngle, mOuterTargetAngle, mMovementCurve->GetFloatValue(mOuterMoveTracker));

		FRotator rot = FRotator::ZeroRotator;
		rot.Add(angle.X, angle.Y, angle.Z);
		mOuterSphere->SetRelativeRotation(rot);

		if (mOuterMoveTracker >= 1.0) {
			mOuterCurrentAngle = mOuterTargetAngle;
			mShouldRotateOuter = false;
			mOuterMoveTracker = 0;

			SoundEventEndOuterRotate();
		}
	}

	if (mShouldRotateMiddle && mMiddleCurrentAngle != mMiddleTargetAngle) {
		mMiddleMoveTracker += mRotationSpeed * DeltaTime;
		FVector angle = FMath::Lerp(mMiddleCurrentAngle, mMiddleTargetAngle, mMovementCurve->GetFloatValue(mMiddleMoveTracker));

		FRotator rot = FRotator::ZeroRotator;
		rot.Add(angle.X, angle.Y, angle.Z);
		mMiddleSphere->SetRelativeRotation(rot);

		if (mMiddleMoveTracker >= 1.0) {
			mMiddleCurrentAngle = mMiddleTargetAngle;
			mShouldRotateMiddle = false;
			mMiddleMoveTracker = 0;

			SoundEventEndMiddleRotate();
		}
	}

	if (mShouldRotateInner && mInnerCurrentAngle != mInnerTargetAngle) {
		mInnerMoveTracker += mRotationSpeed * DeltaTime;
		FVector angle = FMath::Lerp(mInnerCurrentAngle, mInnerTargetAngle, mMovementCurve->GetFloatValue(mInnerMoveTracker));

		FRotator rot = FRotator::ZeroRotator;
		rot.Add(angle.X, angle.Y, angle.Z);
		mInnerSphere->SetRelativeRotation(rot);

		if (mInnerMoveTracker >= 1.0) {
			mInnerCurrentAngle = mInnerTargetAngle;
			mShouldRotateInner = false;
			mInnerMoveTracker = 0;

			SoundEventEndInnerRotate();
		}
	}

}


void AGyroscropePuzzle::AddOuterRotation() {
	if (mShouldRotateOuter)
		return;
	
	mOuterMovementBuffer += mMoveAmount;
	while (mOuterMovementBuffer >= 360)
		mOuterMovementBuffer -= 360;
}
void AGyroscropePuzzle::AddMiddleRotation() {
	if (mShouldRotateMiddle)
		return;

	mMiddleMovementBuffer += mMoveAmount;
	while (mMiddleMovementBuffer >= 360)
		mMiddleMovementBuffer -= 360;
}
void AGyroscropePuzzle::AddInnerRotation() {
	if (mShouldRotateInner)
		return;

	mInnerMovementBuffer += mMoveAmount;
	while (mInnerMovementBuffer >= 360)
		mInnerMovementBuffer -= 360;
}


void AGyroscropePuzzle::ApplyRotation() {
	bool callEvent = false;

	if (!mShouldRotateOuter && mOuterCurrentAngle.Y != mOuterTargetAngle.Y + mOuterMovementBuffer) {
		mShouldRotateOuter = true;
		callEvent = true;

		mOuterTargetAngle.Y += mOuterMovementBuffer;
		mOuterMovementBuffer = 0;

		SoundEventBeginOuterRotate();
	}
	if (!mShouldRotateMiddle && mMiddleCurrentAngle.Z != mMiddleTargetAngle.Z + mMiddleMovementBuffer) {
		mShouldRotateMiddle = true;
		callEvent = true;

		mMiddleTargetAngle.Z += mMiddleMovementBuffer;
		mMiddleMovementBuffer = 0;

		SoundEventBeginMiddleRotate();
	}
	if (!mShouldRotateInner && mInnerCurrentAngle.X != mInnerTargetAngle.X + mInnerMovementBuffer) {
		mShouldRotateInner = true;
		callEvent = true;

		mInnerTargetAngle.X += mInnerMovementBuffer;
		mInnerMovementBuffer = 0;

		SoundEventBeginInnerRotate();
	}

	if (callEvent) {
		//SoundEventBeginRotate();
		mShouldRotateAnything = true;
	}
}	

void AGyroscropePuzzle::Finished() {
	// Rotate 180 degrees
	mOuterTargetAngle.Y = 180;
	mShouldRotateOuter = true;
	mShouldRotateAnything = true;
	SoundEventPuzzleFinished();

	mRotationSpeed = mFinishedRotationSpeed;
	mLastRotation = true;
}

/*
void AGyroscropePuzzle::ResetRotation() {
	if (!mShouldRotateOuter && mOuterCurrentAngle != mOuterTargetAngle)
		mShouldRotateOuter = true;
	if (!mShouldRotateMiddle && mMiddleCurrentAngle != mMiddleTargetAngle)
		mShouldRotateMiddle = true;
	if (!mShouldRotateInner && mInnerCurrentAngle != mInnerTargetAngle)
		mShouldRotateInner = true;
	
	mOuterTargetAngle = mOuterTargetAngle = FVector(0, OuterAngle, 0);
	mMiddleTargetAngle = FVector(0, 0, MiddleAngle);
	mInnerTargetAngle = FVector(InnerAngle, 0, 0);
}
*/