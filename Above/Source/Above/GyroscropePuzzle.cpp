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
}

// Called when the game starts or when spawned
void AGyroscropePuzzle::BeginPlay() {
	Super::BeginPlay();

	mOuterSphere->AttachParent = mRoot;
	mMiddleSphere->AttachParent = mOuterSphere;
	mInnerSphere->AttachParent = mMiddleSphere;
}

// Called every frame
void AGyroscropePuzzle::Tick( float DeltaTime ) {
	Super::Tick( DeltaTime );

	if (!mMovementCurve || !mShouldRotateAnything)
		return;

	if (mShouldRotateOuter && mOuterCurrentAngle != mOuterTargetAngle) {
		mOuterMoveTracker += mRotationSpeed;
		FVector angle = FMath::Lerp(mOuterCurrentAngle, mOuterTargetAngle, mMovementCurve->GetFloatValue(mOuterMoveTracker));

		FRotator rot = FRotator::ZeroRotator;
		rot.Add(angle.X, angle.Y, angle.Z);
		mOuterSphere->SetRelativeRotation(rot);

		if (mOuterMoveTracker >= 1.0) {
			mOuterCurrentAngle = mOuterTargetAngle;
			mShouldRotateOuter = false;
			mOuterMoveTracker = 0;
		}
	}

	if (mShouldRotateMiddle && mMiddleCurrentAngle != mMiddleTargetAngle) {
		mMiddleMoveTracker += mRotationSpeed;
		FVector angle = FMath::Lerp(mMiddleCurrentAngle, mMiddleTargetAngle, mMovementCurve->GetFloatValue(mMiddleMoveTracker));

		FRotator rot = FRotator::ZeroRotator;
		rot.Add(angle.X, angle.Y, angle.Z);
		mMiddleSphere->SetRelativeRotation(rot);

		if (mMiddleMoveTracker >= 1.0) {
			mMiddleCurrentAngle = mMiddleTargetAngle;
			mShouldRotateMiddle = false;
			mMiddleMoveTracker = 0;
		}
	}
	
	if (mShouldRotateInner && mInnerCurrentAngle != mInnerTargetAngle) {
		mInnerMoveTracker += mRotationSpeed;
		FVector angle = FMath::Lerp(mInnerCurrentAngle, mInnerTargetAngle, mMovementCurve->GetFloatValue(mInnerMoveTracker));

		FRotator rot = FRotator::ZeroRotator;
		rot.Add(angle.X, angle.Y, angle.Z);
		mInnerSphere->SetRelativeRotation(rot);

		if (mInnerMoveTracker >= 1.0) {
			mInnerCurrentAngle = mInnerTargetAngle;
			mShouldRotateInner = false;
			mInnerMoveTracker = 0;
		}
	}

	if (!mShouldRotateInner && !mShouldRotateMiddle && !mShouldRotateOuter) {
		SoundEventEndRotate();
		mShouldRotateAnything = false;
	}
}


void AGyroscropePuzzle::AddOuterRotation() {
	AddRotationOuterHelper(FVector(0, mMoveAmount, 0));
}
void AGyroscropePuzzle::AddMiddleRotation() {
	AddRotationMiddleHelper(FVector(0, 0, mMoveAmount));
}
void AGyroscropePuzzle::AddInnerRotation() {
	AddRotationInnerHelper(FVector(mMoveAmount, 0, 0));
}


void AGyroscropePuzzle::AddRotationOuterHelper(FVector amount) {
	if (mShouldRotateOuter)
		return;
	mOuterTargetAngle += amount;
	//AddRotationMiddleHelper(amount);
}
void AGyroscropePuzzle::AddRotationMiddleHelper(FVector amount) {
	if (mShouldRotateMiddle)
		return;
	
	mMiddleTargetAngle += amount;
	//AddRotationInnerHelper(amount);
}
void AGyroscropePuzzle::AddRotationInnerHelper(FVector amount) {
	if (mShouldRotateInner)
		return;

	mInnerTargetAngle += amount;
}

void AGyroscropePuzzle::ApplyRotation() {
	bool callEvent = false;

	if (!mShouldRotateOuter && mOuterCurrentAngle != mOuterTargetAngle) {
		mShouldRotateOuter = true;
		callEvent = true;
	}
	if (!mShouldRotateMiddle && mMiddleCurrentAngle != mMiddleTargetAngle) {
		mShouldRotateMiddle = true;
		callEvent = true;
	}
	if (!mShouldRotateInner && mInnerCurrentAngle != mInnerTargetAngle) {
		mShouldRotateInner = true;
		callEvent = true;
	}

	if (callEvent) {
		SoundEventBeginRotate();
		mShouldRotateAnything = true;
	}
}	

void AGyroscropePuzzle::ResetRotation() {
	if (!mShouldRotateOuter && mOuterCurrentAngle != mOuterTargetAngle)
		mShouldRotateOuter = true;
	if (!mShouldRotateMiddle && mMiddleCurrentAngle != mMiddleTargetAngle)
		mShouldRotateMiddle = true;
	if (!mShouldRotateInner && mInnerCurrentAngle != mInnerTargetAngle)
		mShouldRotateInner = true;

	mOuterTargetAngle = FVector(0, 0, 0);
	mMiddleTargetAngle = FVector(0, 0, 0);
	mInnerTargetAngle = FVector(0, 0, 0);
}