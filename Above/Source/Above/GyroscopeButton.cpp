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
	
	mOverlapBox = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("StepCollider"));

	mInteractionTrigger = ObjectInitializer.CreateDefaultSubobject<UChildActorComponent>(this, TEXT("InteractionTrigger"));

	mStepMesh = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("StepMesh"));
	mPressMesh = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("PressMesh"));
	
	SetRootComponent(mRootComponent);
	
	mOverlapBox->AttachParent			= mRootComponent;
	mInteractionTrigger->AttachParent	= mRootComponent;
	mStepMesh->AttachParent				= mRootComponent;
	mPressMesh->AttachParent			= mRootComponent;

	mOverlapBox->OnComponentBeginOverlap.AddDynamic(this, &AGyroscopeButton::BeginOverlapOnBox);
}

void AGyroscopeButton::OnConstruction(const FTransform& Transform) {
	Super::OnConstruction(Transform);

	if (ActivateWhenSteppedOn) {
		mOverlapBox->SetVisibility(true);
		//mOverlapBox->Activate();
		
		mOverlapBox->SetRelativeLocation(FVector(0, 0, 0));

		//mInteractionTriggerPosition = mInteractionTrigger->GetComponentLocation();
		mInteractionTrigger->SetRelativeLocation(FVector(0, 0, -500000));

		mStepMesh->SetVisibility(true);
		mPressMesh->SetVisibility(false);
	}
	else {
		mOverlapBox->SetVisibility(false);
		//mOverlapBox->Deactivate();

		//mOverlapBoxPosition = mOverlapBox->GetComponentLocation();
		mOverlapBox->SetRelativeLocation(FVector(0, 0, -500000));

		mInteractionTrigger->SetRelativeLocation(FVector(0, 0, 0));

		mStepMesh->SetVisibility(false);
		mPressMesh->SetVisibility(true);
	}
	
	//mOverlapBox->AttachParent			= mRootComponent;
	//mInteractionTrigger->AttachParent	= mRootComponent;
	//mStepMesh->AttachParent				= mRootComponent;
	//mPressMesh->AttachParent			= mRootComponent;
}

// Called when the game starts or when spawned
void AGyroscopeButton::BeginPlay() {
	Super::BeginPlay();
}

// Called every frame
void AGyroscopeButton::Tick( float DeltaTime ) {
	Super::Tick( DeltaTime );
}

void AGyroscopeButton::Activate() {
	if (RotationActivation)
		OnInitiateRotationActivate();
	else {
		mCurrentMode++;
		mCurrentMode %= NumberOfModes;
		OnActivate();
	}
}

void AGyroscopeButton::BeginOverlapOnBox(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (!ActivateWhenSteppedOn)
		return;

	Activate();
}

int32 AGyroscopeButton::GetCurrentMode() {
	return mCurrentMode;
}
