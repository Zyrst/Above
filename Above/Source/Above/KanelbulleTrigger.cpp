// Fill out your copyright notice in the Description page of Project Settings.

#include "Above.h"
#include "KanelbulleTrigger.h"


// Sets default values
AKanelbulleTrigger::AKanelbulleTrigger(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AKanelbulleTrigger::BeginPlay(){
	Super::BeginPlay();
	
}

// Called every frame
void AKanelbulleTrigger::Tick( float DeltaTime ){
	Super::Tick( DeltaTime );


	if (!mShouldAnimate || mTextures.Num() <= 0 || mEmissiveTextures.Num() <= 0)
		return;

	// Increase tracker
	mAnimateTracker += mAnimationSpeed * DeltaTime;

	// Calculate material indices
	int32 tIdx = mAnimationCurve->GetFloatValue(mAnimateTracker) * (mTextures.Num() - 1);
	int32 eIdx = mAnimationCurve->GetFloatValue(mAnimateTracker) * (mEmissiveTextures.Num() - 1);

	// Set textures
	if (tIdx < mTextures.Num())
		mMaterial->SetTextureParameterValue("Texture", mTextures[tIdx]);
	if (eIdx < mEmissiveTextures.Num())
		mMaterial->SetTextureParameterValue("Emissive", mEmissiveTextures[eIdx]);


	if (mAnimateTracker >= 1.0f)
		mShouldAnimate = false;
}

void AKanelbulleTrigger::Activate() {
	// Animate
	mShouldAnimate = true;
}
