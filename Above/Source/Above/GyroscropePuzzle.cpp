// Fill out your copyright notice in the Description page of Project Settings.

#include "Above.h"
#include "GyroscropePuzzle.h"


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
}

// Called every frame
void AGyroscropePuzzle::Tick( float DeltaTime ) {
	Super::Tick( DeltaTime );

	if (!mMovementCurve || !mShouldRotateAnything)
		return;

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

	if (!mShouldRotateInner && !mShouldRotateMiddle && !mShouldRotateOuter) {
		//SoundEventEndRotate();
		mShouldRotateAnything = false;
	}
}


void AGyroscropePuzzle::AddOuterRotation() {
	if (mShouldRotateOuter)
		return;
	
	mOuterMovementBuffer += mMoveAmount;
	if (mOuterMovementBuffer >= 360)
		mOuterMovementBuffer -= 360;
}
void AGyroscropePuzzle::AddMiddleRotation() {
	if (mShouldRotateMiddle)
		return;

	mMiddleMovementBuffer += mMoveAmount;
	if (mMiddleMovementBuffer >= 360)
		mMiddleMovementBuffer -= 360;
}
void AGyroscropePuzzle::AddInnerRotation() {
	if (mShouldRotateInner)
		return;

	mInnerMovementBuffer += mMoveAmount;
	if (mInnerMovementBuffer >= 360)
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