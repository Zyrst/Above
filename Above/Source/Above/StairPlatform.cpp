// Fill out your copyright notice in the Description page of Project Settings.

#include "Above.h"
#include "StairPlatform.h"
#include "Stefun.h"


// Sets default values
AStairPlatform::AStairPlatform() {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AStairPlatform::OnConstruction(const FTransform& transform) {
	Super::OnConstruction(transform);

	if (NextCollisionBox != nullptr)
		NextCollisionBox->SetRelativeLocation(NextCollisionBoxPosition);
	
	if (PreviousCollisionBox != nullptr)
		PreviousCollisionBox->SetRelativeLocation(PreviousCollisionBoxPosition);
}

// Called when the game starts or when spawned
void AStairPlatform::BeginPlay() {
	Super::BeginPlay();
	
	if (NextCollisionBox != nullptr)
		NextCollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AStairPlatform::BeginOverlapNext);
	
	if (PreviousCollisionBox != nullptr)
		PreviousCollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AStairPlatform::BeginOverlapPrevious);

	if (MiddleCollisionBox != nullptr)
		MiddleCollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AStairPlatform::BeginOverlapMiddle);
}

// Called every frame
void AStairPlatform::Tick( float DeltaTime ) {
	Super::Tick( DeltaTime );

	if (!mMove || !MovementSpeedCurve)
		return;

	mMovementTracker += MoveSpeed * DeltaTime;

	FVector tmpLoc = FVector::ZeroVector;
	switch (mMoveDirection) {
		case MoveDirection::Target:
			tmpLoc = FMath::Lerp(mLerpFrom, ActivePosition, MovementSpeedCurve->GetFloatValue(mMovementTracker));
			SetActorLocation(tmpLoc);
			break;
		case MoveDirection::Idle:
			tmpLoc = FMath::Lerp(mLerpFrom, IdlePosition, MovementSpeedCurve->GetFloatValue(mMovementTracker));
			SetActorLocation(tmpLoc);			
			break;
	}

	if (mMovementTracker >= 1.0f) {
		mMove = false;
		mMovementTracker = 0;

		switch (mMoveDirection) {
		case MoveDirection::Target:
			OnTargetReached();
			break;
		case MoveDirection::Idle:
			OnIdleReached();
			break;
		}
	}
}

void AStairPlatform::MoveToTarget() {
	if (mMove || FVector::Dist(GetActorLocation(), ActivePosition) <= 1)
		return;

	mLerpFrom = GetActorLocation();
	mMoveDirection = MoveDirection::Target;
	mMove = true;
	OnHeadingForTarget();
}

void AStairPlatform::MoveToIdle() {
	if (mMove || FVector::Dist(GetActorLocation(), IdlePosition) <= 1)
		return;

	mLerpFrom = GetActorLocation();
	mMoveDirection = MoveDirection::Idle;
	mMove = true;
	OnHeadingForIdle();
}


void AStairPlatform::BeginOverlapNext(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	AStefun* s = (AStefun*)OtherActor;
	if (NextPlatform == nullptr || s == nullptr)
		return;

	AStairPlatform* tmp = (AStairPlatform*)NextPlatform;
	if (tmp != nullptr)
		tmp->MoveToTarget();
}

void AStairPlatform::BeginOverlapPrevious(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	AStefun* s = (AStefun*)OtherActor;
	if (PreviousPlatform == nullptr || s == nullptr	)
		return;

	AStairPlatform* tmp = (AStairPlatform*)PreviousPlatform;
	if (tmp != nullptr)
		tmp->MoveToTarget();
}

void AStairPlatform::BeginOverlapMiddle(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	AStefun* s = (AStefun*)OtherActor;
	if (s == nullptr)
		return;
	
	if (PreviousPlatform != nullptr) {
		AStairPlatform* tmp = (AStairPlatform*)PreviousPlatform;
		if (tmp != nullptr)
			tmp->MoveToIdle();
	}

	if (NextPlatform != nullptr) {
		AStairPlatform* tmp = (AStairPlatform*)NextPlatform;
		if (tmp != nullptr)
			tmp->MoveToIdle();
	}
}
