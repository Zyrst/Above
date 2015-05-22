// Fill out your copyright notice in the Description page of Project Settings.

#include "Above.h"
#include "SoundParameterTrigger.h"
#include "Stefun.h"
#include "AboveGameMode.h"

// Sets default values
ASoundParameterTrigger::ASoundParameterTrigger(const FObjectInitializer& ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	mRootComponent = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("Root"));
	SetRootComponent(mRootComponent);
	mRootComponent->SetVisibility(false);

	// Create possible colliders
	mBoxCollider					= ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("BoxCollider"));
	mSphereCollider					= ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("SpehereCollider"));
	mCapsuleCollider				= ObjectInitializer.CreateDefaultSubobject<UCapsuleComponent>(this, TEXT("CapsuleCollider"));
}

void ASoundParameterTrigger::OnConstruction(const FTransform& Transform) {
	Super::OnConstruction(Transform);

	// Set up visibility on actor change
	mBoxCollider->SetVisibility(false);
	mBoxCollider->bGenerateOverlapEvents = false;
	mSphereCollider->SetVisibility(false);
	mSphereCollider->bGenerateOverlapEvents = false;
	mCapsuleCollider->SetVisibility(false);
	mCapsuleCollider->bGenerateOverlapEvents = false;

	// Set visibility depending on which collider chosen
	switch (mColliderType) {
	case ColliderType::Box:
		mBoxCollider->SetVisibility(true);
		mBoxCollider->bGenerateOverlapEvents = true;
		break;
	case ColliderType::Spehere:
		mSphereCollider->SetVisibility(true);
		mSphereCollider->bGenerateOverlapEvents = true;
		break;
	case ColliderType::Capsule:
		mCapsuleCollider->SetVisibility(true);
		mCapsuleCollider->bGenerateOverlapEvents = true;
		break;
	}

	// Set parent (cannot do this in constructor since that crashes on play)
	mBoxCollider->AttachParent = mRootComponent;
	mSphereCollider->AttachParent = mRootComponent;
	mCapsuleCollider->AttachParent = mRootComponent;
}

// Called when the game starts or when spawned
void ASoundParameterTrigger::BeginPlay(){
	Super::BeginPlay();

	// Setup collision
	switch (mColliderType) {
	case ColliderType::Box:
		mBoxCollider->OnComponentBeginOverlap.AddDynamic(this, &ASoundParameterTrigger::OnOverlapBegin);
		mBoxCollider->OnComponentEndOverlap.AddDynamic(this, &ASoundParameterTrigger::OnOverlapEnd);
		break;
	case ColliderType::Spehere:
		mSphereCollider->OnComponentBeginOverlap.AddDynamic(this, &ASoundParameterTrigger::OnOverlapBegin);
		mSphereCollider->OnComponentEndOverlap.AddDynamic(this, &ASoundParameterTrigger::OnOverlapEnd);
		break;
	case ColliderType::Capsule:
		mCapsuleCollider->OnComponentBeginOverlap.AddDynamic(this, &ASoundParameterTrigger::OnOverlapBegin);
		mCapsuleCollider->OnComponentEndOverlap.AddDynamic(this, &ASoundParameterTrigger::OnOverlapEnd);
		break;
	}

	// Wonky. Set position manually instead of inheriting...
	mBoxCollider->SetWorldTransform(mRootComponent->GetRelativeTransform());
	mSphereCollider->SetWorldTransform(mRootComponent->GetRelativeTransform());
	mCapsuleCollider->SetWorldTransform(mRootComponent->GetRelativeTransform());

	mBoxCollider->AttachParent = mRootComponent;
	mSphereCollider->AttachParent = mRootComponent;
	mCapsuleCollider->AttachParent = mRootComponent;
}

// Called every frame
void ASoundParameterTrigger::Tick( float DeltaTime ){
	Super::Tick( DeltaTime );
}


void ASoundParameterTrigger::OnOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	AStefun* sCast = Cast<AStefun>(OtherActor);
	if (sCast == nullptr)
		return;

	OnOverlapBeginEvent(sCast);

	if (!mPuzzleDoneTrigger && !EndTrigger) {
		sCast->ChangeParameter(mEnterParameterName, mEnterParameterValue);
		return;
	}

	// Check puzzle status
	AAboveGameMode* mode = (AAboveGameMode*)GetWorld()->GetAuthGameMode();
	if (mode != nullptr) {
		float curPuzzleStatus = -1;

		if (!mode->GetStartedStatus(mPuzzleReference) && !mode->GetCompleteStatus(mPuzzleReference))
			curPuzzleStatus = mNotStarted;
		else if (mode->GetStartedStatus(mPuzzleReference) && !mode->GetCompleteStatus(mPuzzleReference))
			curPuzzleStatus = mStarted;
		else if (mode->GetCompleteStatus(mPuzzleReference))
			curPuzzleStatus = mFinished;

		sCast->ChangeParameter(mStatusParameterName, curPuzzleStatus);
	}

}

void ASoundParameterTrigger::OnOverlapEnd(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	AStefun* sCast = Cast<AStefun>(OtherActor);
	if (sCast == nullptr)
		return;

	OnOverlapEndEvent(sCast);

	if (!mPuzzleDoneTrigger && !EndTrigger) {
		sCast->ChangeParameter(mExitParameterName, mExitParameterValue);
		return;
	}
}