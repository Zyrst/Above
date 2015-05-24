// Fill out your copyright notice in the Description page of Project Settings.

#include "Above.h"
#include "GyroscopeButton.h"

#include <limits>


// Sets default pööp
AGyroscopeButton::AGyroscopeButton(const FObjectInitializer& ObjectInitializer): 
	Super(ObjectInitializer){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mRootComponent = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("root"));
	
	//mOverlapBox = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("StepCollider"));
	//mInteractionTrigger = ObjectInitializer.CreateDefaultSubobject<UChildActorComponent>(this, TEXT("InteractionTrigger"));
	//mStepMesh = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("StepMesh"));
	
	for (int32 i = 0; i < mPressMeshes.Num(); i++) {
		mPressMeshes[i] = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("PressMesh" + i));
		mPressMeshes[i]->AttachParent = mRootComponent;
	}

	SetRootComponent(mRootComponent);
	
	//mOverlapBox->AttachParent			= mRootComponent;
	//mInteractionTrigger->AttachParent	= mRootComponent;
	//mStepMesh->AttachParent				= mRootComponent;
}

void AGyroscopeButton::OnConstruction(const FTransform& Transform) {
	Super::OnConstruction(Transform);

	if (ActivateWhenSteppedOn) {
		
		//if (mOverlapBox != NULL) {
		//	mOverlapBoxPosition = mOverlapBox->GetRelativeTransform().GetLocation();
		//	mOverlapBox->SetRelativeLocation(mOverlapBoxPosition);
		//}

		//if (mInteractionTrigger != NULL)
		//	mInteractionTrigger->SetRelativeLocation(FVector(0, 0, -500000));

		if (mStepMesh != NULL)
			mStepMesh->SetVisibility(true);

		for (int32 i = 0; i < mPressMeshes.Num(); i++)
			mPressMeshes[i]->SetVisibility(false);
	}
	else {
		//if (mOverlapBox != NULL)
		//	mOverlapBox->SetRelativeLocation(FVector(0, 0, -500000));

		//if (mInteractionTrigger != NULL) {
		//	mInteractionTriggerPosition = mInteractionTrigger->GetRelativeTransform().GetLocation();
		//	mInteractionTrigger->SetRelativeLocation(mInteractionTriggerPosition);
		//}

		if (mStepMesh != NULL)
			mStepMesh->SetVisibility(false);
	
		for (int32 i = 0; i < mPressMeshes.Num(); i++)
			mPressMeshes[i]->SetVisibility(true);
	}


	mCurrentMode = StartingMode % NumberOfModes;
	mCurrentAngle = FVector(0, (360 / NumberOfModes) * StartingMode , 0);
	
	FRotator rot = FRotator::ZeroRotator;
	rot.Add(mCurrentAngle.X, mCurrentAngle.Y, mCurrentAngle.Z);

	mRotateMesh->SetRelativeRotation(rot);
	
	//mOverlapBox->AttachParent			= mRootComponent;
	//mInteractionTrigger->AttachParent	= mRootComponent;
	//mStepMesh->AttachParent				= mRootComponent;
	//mPressMesh->AttachParent			= mRootComponent;
}

// Called when the game starts or when spawned
void AGyroscopeButton::BeginPlay() {
	Super::BeginPlay();

	if (mOverlapBox != NULL)
		mOverlapBox->OnComponentBeginOverlap.AddDynamic(this, &AGyroscopeButton::BeginOverlapOnBox);
}

// Called every frame
void AGyroscopeButton::Tick( float DeltaTime ) {
	Super::Tick( DeltaTime );


	if (!mShouldRotate)
		return;

	mRotateTracker += mRotateSpeed * DeltaTime;

	if (mRotationCurve != NULL) {

		FVector angle = FMath::Lerp(mCurrentAngle, mTargetAngle, mRotationCurve->GetFloatValue(mRotateTracker));

		FRotator rot = FRotator::ZeroRotator;
		rot.Add(angle.X, angle.Y, angle.Z);
		
		mRotateMesh->SetRelativeRotation(rot);
	}
	else {
		
	}

	if (mRotateTracker >= 1.0f) {
		mCurrentAngle = mTargetAngle;
		mShouldRotate = false;
		mRotateTracker = 0;
	}
}

void AGyroscopeButton::Activate() {
	if (mShouldRotate)
		return;

	if (!InitiatesRotation) {
		mCurrentMode++;
		mCurrentMode %= NumberOfModes;

		mShouldRotate = true;
		mTargetAngle = mCurrentAngle + FVector(0, (360 / NumberOfModes), 0);
	}

	OnActivate();
	
	SoundEventModeChange(ButtonIndex, mCurrentMode, InitiatesRotation);
}

void AGyroscopeButton::BeginOverlapOnBox(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (!ActivateWhenSteppedOn)
		return;

	Activate();
}

int32 AGyroscopeButton::GetCurrentMode() {
	return mCurrentMode;
}
