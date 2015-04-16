// Fill out your copyright notice in the Description page of Project Settings.

#include "Above.h"
#include "RotatingPuzzle.h"


// Sets default values
ARotatingPuzzle::ARotatingPuzzle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	mFadeDown = false;
	mShouldFade = false;
}

// Called when the game starts or when spawned
void ARotatingPuzzle::BeginPlay()
{
	Super::BeginPlay();
	mRotate = false;
	mOldTarget = 0;
	
	//Get the disk mesh
	TArray<UStaticMeshComponent*> Components;
	this->GetComponents<UStaticMeshComponent>(Components);
	for (int32 i = 0; i < Components.Num(); i++){
		UStaticMeshComponent* mesh = Components[i];
		if (mesh->GetName() == mRotationParentName){
			mDishMesh = Components[i];
		}
		
		// Get indicator mesh
		if (mesh->GetName() == mIndicatorParentName) {
			mIndicatorMesh = Components[i];
			mIndicatorMeshMaterial = mIndicatorMesh->CreateAndSetMaterialInstanceDynamic(0);
		}
	}
	mBase = (2 * 3.14) * mDishMesh->StaticMesh->GetBounds().SphereRadius;
	//60 degrees between each number
	for (int32 i = 0; i < 6; i++){
		if (i == 0)
			mPoints.Push(0);
		else
			mPoints.Push(i * 60);
	}

	mIndicatorMeshMaterial->SetTextureParameterValue("Texture2", mTextureInactive);
	mIndicatorMeshMaterial->SetScalarParameterValue("BlendValue", 1.0f);
	mBlendFactor = 1;
}

// Called every frame
void ARotatingPuzzle::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if (mRotate){
		//(two*pi*r*(CurrentDegree / 360))
		if ((mBase * (mCurrent / 360)) < mCalcTarget){
			
			mDishMesh->AddLocalRotation(FRotator::FRotator(0, 1, 0), false, nullptr);
			mCurrent += 1.0;
			SoundEventRotating();
		}

		if ((mBase * (mCurrent / 360)) >= mCalcTarget){
			//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("Stopped"));
			//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, FString::Printf(TEXT("mCurrent %f"), mCurrent));
			mRotate = false;
			mOldTarget = mTarget;
			Reset();
			SoundEventRotateEnd();
		}
	}


	if (mShouldFade) {
		// Fade "up" to unlit texture
		if (!mFadeDown && mBlendFactor < 1.0f) {
			mBlendFactor += mBlendSpeed;
			mIndicatorMeshMaterial->SetScalarParameterValue("BlendValue", mBlendFactor);
		}
		// Change texture when unlit is showing
		else if (!mFadeDown && mBlendFactor >= 1.0f) {
			mIndicatorMeshMaterial->SetTextureParameterValue("Texture1", mDesiredTexture);
			mFadeDown = true;
		}
		// Fade "down" to lit texture
		else if (mFadeDown && mBlendFactor > 0.0f) {
			mBlendFactor -= mBlendSpeed;
			mIndicatorMeshMaterial->SetScalarParameterValue("BlendValue", mBlendFactor);
		}
		// Stop fading when lit
		else if (mFadeDown && mBlendFactor <= 0.0f) {
			mShouldFade = false;
			mFadeDown = false;
		}
	}
}

void ARotatingPuzzle::Activate(float target){
	if (mRotate)
		return;

	mRotate = true;
	mTarget = target;
	//GEngine->AddOnScreenDebugMessage(-1, 8.0f, FColor::Red, FString::Printf(TEXT("Target from array %f"), (target)));
	//GEngine->AddOnScreenDebugMessage(-1, 8.0f, FColor::Red, FString::Printf(TEXT("old target %f"), ( mOldTarget)));
	
	float calc = 0;
	float num = 0;
	float sum = 0;
	//Find the old target in the array of positions
	for (int32 i = 0; i < mPoints.Num(); i++){
		if (mPoints[i] == mOldTarget){
			calc = mPoints[i];
			num = i;
		}
	}

	bool loop = true;
	int32 j = num;
	//Find points between oldtarget and new target and add the degrees between
	//Used to calculate the arc length
	while (loop){
		if ( j == mPoints.Num() - 1){
			if (mPoints[j] == mTarget){
				loop = false;
			}
			else{
				//Last point in array 
				//Did not find target so start over
				sum += 60;
				j = 0;
			}
		}
		else {
			if (mPoints[j] == mTarget){
				//Found target , stop loop
				loop = false;
			}
			else{
				sum += 60;
				j++;
			}
		}
	}
	//GEngine->AddOnScreenDebugMessage(-1, 8.0f, FColor::Magenta, FString::Printf(TEXT("Degree to move %f"), sum));
	//Calc the target with the formula
	mCalcTarget = mBase * ((sum / 360));


	// Set texture if texture exists
	if (mRandom <= mIndicatorTextures.Num()) {
		mDesiredTexture = mIndicatorTextures[mRandom];
		mShouldFade = true;

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Random: %i"), mRandom));
	}

	SoundEventButtonClick();
	SoundEventRotateBegin();
}

void ARotatingPuzzle::Reset(){
	mCurrent = 0;
}

float ARotatingPuzzle::NotSameNumber(){

	mRandom = FMath::RandHelper(5);
	float point = mPoints[mRandom];

	if (point == mOldTarget){
		return NotSameNumber();
	}
	else
		return point;
}

TArray<UTexture2D*> ARotatingPuzzle::GetMaterialsReference() {
	return mIndicatorTextures;
}

UMaterialInstanceDynamic* ARotatingPuzzle::GetMaterialReference() {
	return mIndicatorMeshMaterial;
}