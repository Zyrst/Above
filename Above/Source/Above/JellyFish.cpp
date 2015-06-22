// Fill out your copyright notice in the Description page of Project Settings.

#include "Above.h"
#include "JellyFish.h"


// Sets default values
AJellyFish::AJellyFish()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mMovementSpeed = FVector(100, 100, 100);
	mRotateCounter = 0.f;
	mTraceDistance = 100;
	mRandomDistance = 500;
	mCenterPoint = FVector(0, 0, 0);
	mMaxCenterDistance = 10000;
}

// Called when the game starts or when spawned
void AJellyFish::BeginPlay()
{
	Super::BeginPlay();

	mTargetLocation = this->GetActorLocation();
	mDelta = FVector(0, 0, 0);
	mCurrentRotation = FVector(0, 0, 0);
	mTargetRotation = FVector(0, 0, 0);
}

// Called every frame
void AJellyFish::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	Move(DeltaTime);
	RayTrace();
	Rotate(DeltaTime);
}

void AJellyFish::Move(float deltaTime)
{
	FVector delta = mTargetLocation - this->GetActorLocation();
	FVector deltaAbs = delta.GetAbs();

	FVector centerDistance = mCenterPoint - this->GetActorLocation();
	centerDistance = centerDistance.GetAbs();
	float centerDistanceFloat = FMath::Sqrt(centerDistance.X * centerDistance.X + centerDistance.Y * centerDistance.Y + centerDistance.Z * centerDistance.Z);

	if (deltaAbs.X < 10 &&
		deltaAbs.Y < 10 &&
		deltaAbs.Z < 10)
	{
		ChangeTarget();
	}
	
	if (centerDistanceFloat > mMaxCenterDistance)
		OutOfBounds();

	this->AddActorWorldOffset(mDelta * deltaTime);
}

void AJellyFish::RayTrace()
{
	FVector traceStart = this->GetActorLocation();
	FVector traceEnd = traceStart + (mTargetRotation * mTraceDistance);

	FHitResult traceHitResult;
	ECollisionChannel collisionChannel = ECC_Pawn;
	FCollisionQueryParams traceParamaters(FName(TEXT("InteractionTrace")), true, this);

	// Trace
	GetWorld()->LineTraceSingle(traceHitResult, traceStart, traceEnd, collisionChannel, traceParamaters);

	if (traceHitResult.bBlockingHit == true)
	{
		ChangeTarget();
	}
}

void AJellyFish::ChangeTarget()
{
	FVector oldTarget = mTargetLocation;
	mTargetLocation += FVector(FMath::FRandRange(-mRandomDistance, mRandomDistance), FMath::FRandRange(-mRandomDistance, mRandomDistance), FMath::FRandRange(-mRandomDistance, mRandomDistance));

	FVector traceStart = this->GetActorLocation();
	FVector traceEnd = traceStart + (mTargetRotation * mTraceDistance);

	FHitResult traceHitResult;
	ECollisionChannel collisionChannel = ECC_Pawn;
	FCollisionQueryParams traceParamaters(FName(TEXT("InteractionTrace")), true, this);

	// Trace
	GetWorld()->LineTraceSingle(traceHitResult, traceStart, traceEnd, collisionChannel, traceParamaters);

	mDelta = mTargetLocation - this->GetActorLocation();

	if (traceHitResult.bBlockingHit == true) {
		mTargetLocation = this->GetActorLocation() - mDelta;
	}

	mDelta = mTargetLocation - this->GetActorLocation();

	mDelta.Normalize();
	mTargetRotation = mDelta;
	mDelta = mDelta * mMovementSpeed;
}

void AJellyFish::Rotate(float deltaTime)
{
	if (mCurrentRotation != mTargetRotation)
	{
		this->SetActorRotation(FMath::Lerp(mCurrentRotation.Rotation(), mTargetRotation.Rotation(), mRotateCounter) + FVector(0, 0, -90).Rotation());
		mRotateCounter += (1 * deltaTime);
		if (mRotateCounter >= 1.f)
		{
			mRotateCounter = 0.f;
			mCurrentRotation = mTargetRotation;
		}
	}
}

void AJellyFish::OutOfBounds()
{
	mTargetLocation = mCenterPoint;
	mDelta = mTargetLocation - this->GetActorLocation();
	mDelta.Normalize();
	mTargetRotation = mDelta;
	mDelta = mDelta * mMovementSpeed;
}