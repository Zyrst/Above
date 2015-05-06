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
	mRandomRotationInterval = FVector2D(3, 5);
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
		//Table material 
		if (mesh->GetName() == "ModelBase"){
			mDishMeshMaterial = Components[i]->CreateAndSetMaterialInstanceDynamic(0);
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
	mDishMeshMaterial->SetTextureParameterValue("Emmisive", mLightUp[0]);

	if (mButtonEmissive.Num() > 0)
		mIndicatorMeshMaterial->SetTextureParameterValue("Emissive", mButtonEmissive[0]);
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
			int32 rotationSpeed = (mCalcTarget - mBase * (mCurrent / 360)) * 0.2;
			if (rotationSpeed < 1) {
				rotationSpeed = 1;
			}
			mDishMesh->AddLocalRotation(FRotator::FRotator(0, rotationSpeed, 0), false, nullptr);
			mCurrent += rotationSpeed;
			SoundEventRotating();
			
		}
		if ((mBase * (mCurrent / 360)) >= mCalcTarget){
			//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("Stopped"));
			//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, FString::Printf(TEXT("mCurrent %f"), mCurrent));
			mRotate = false;
			mOldTarget = mTarget;
			ActivateEmmisive();
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
			mIndicatorMeshMaterial->SetTextureParameterValue("Emissive", mDesiredButtonEmissive);
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

void ARotatingPuzzle::Activate(){
	if (mRotate)
		return;

	mRotate = true;	
	//Get random number
	mRandom = FMath::RandHelper(5);
	//Don't want zero so + 1 so it always moves atleast one spot
	mRandom += 1;
	UE_LOG(LogTemp, Log, TEXT("Random: %d"), mRandom);
	float sum = 0;
	sum = 60 * (mRandom);
	//mPevPos is empty so don't want nullptr which breaks the game
	if (mPrevPos.Num() == 0){
		mPrevPos.Push(sum);
		if (sum == 60 || sum == 180 || sum == 300){
			UE_LOG(LogTemp, Log, TEXT("One new Right"))
			mRightPos.Add(sum);
		}
	}
	//PrevPost contains elemtents that can be used to determine positions
	else if(mPrevPos.Num() != 0 || mRightPos.Num() != 3){
		float tmp = mPrevPos.Last() + sum;
		if (tmp > 360){
			tmp -= 360.0f;
		}
		if (tmp == 360){
			tmp = 0;
		}
		mPrevPos.Add(tmp);
		//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, FString::Printf(TEXT("Value: %f"), tmp));
		UE_LOG(LogTemp, Log, TEXT("Temp value %f"), tmp);
		UE_LOG(LogTemp, Log, TEXT("Sum %f"), sum);
		
		if (tmp == 60 || tmp == 180 || tmp == 300){
			UE_LOG(LogTemp, Log, TEXT("One new Right"));
			if (!mRightPos.Contains(tmp)){
				mRightPos.Add(tmp);
				//Light up the right slot
			}
			
			else if (mRightPos.Contains(tmp)){
				//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Duplicate same value"));
				UE_LOG(LogTemp, Log, TEXT("Duplicate value"));
				mRightPos.Empty();
				//Reset 
			}
			if (mRightPos.Num() == 3){
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("All right"));
				UE_LOG(LogTemp, Log, TEXT("All right"));
			}
		}
		UE_LOG(LogTemp, Log, TEXT("Size of Right Pos: %d"), mRightPos.Num());
	}
	

	//Calc the target with the formula using arc length formula
	mCalcTarget = mBase * ((sum / 360));
	mCalcTarget += mBase * ((360 * FMath::RandRange(3, 5) / 360));

	// Set texture if texture exists
	if (mRandom <= mIndicatorTextures.Num()) {
		if (mButtonEmissive.Num() <= mIndicatorTextures.Num())
			mDesiredButtonEmissive = mButtonEmissive[mRandom - 1];

		mDesiredTexture = mIndicatorTextures[mRandom - 1];
		mShouldFade = true;

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Random: %i"), mRandom));
	}
	SoundEventButtonClick();
	SoundEventRotateBegin();

	///Old Code

	/*float calc = 0;
	int32 num = 0;
	bool loop = true;

	//Find the old target in the array of positions
	for (int32 i = 0; i < mPoints.Num(); i++){
		if (mPoints[i] == mOldTarget){
			calc = mPoints[i];
			num = i;
		}
	}*/

	//Find points between oldtarget and new target and add the degrees between
	/*while (loop){
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
	}*/
}

void ARotatingPuzzle::Reset(){
	mCurrent = 0;
}


void ARotatingPuzzle::ActivateEmmisive(){
	
	float tmp;
	switch (mRightPos.Num()){
	case 0:
		mDishMeshMaterial->SetTextureParameterValue("Emmisive", mLightUp[0]);
		mDishMeshMaterial->SetTextureParameterValue("Emmisive2", mLightUp[0]);
		break;
	case 1:
		tmp = mRightPos.Last();
		if (tmp == 60){
			mDishMeshMaterial->SetTextureParameterValue("Emmisive", mLightUp[1]);
		}
		else if (tmp == 180){
			mDishMeshMaterial->SetTextureParameterValue("Emmisive", mLightUp[2]);
		}
		else if (tmp == 300){
			mDishMeshMaterial->SetTextureParameterValue("Emmisive", mLightUp[3]);
		}
		break;
	case 2:
		tmp = mRightPos.Last();

		if (tmp == 60){
			mDishMeshMaterial->SetTextureParameterValue("Emmisive2", mLightUp[1]);
		}
		else if (tmp == 180){
			mDishMeshMaterial->SetTextureParameterValue("Emmisive2", mLightUp[2]);
		}
		else if (tmp == 300){
			mDishMeshMaterial->SetTextureParameterValue("Emmisive2", mLightUp[3]);
		}
		break;
	case 3:
		mDishMeshMaterial->SetTextureParameterValue("Emmisive", mLightUp[4]);
		mDishMeshMaterial->SetTextureParameterValue("Emmisive2", mLightUp[0]);
		break;
	default:
		mDishMeshMaterial->SetTextureParameterValue("Emmisive", mLightUp[0]);
		mDishMeshMaterial->SetTextureParameterValue("Emmisive2", mLightUp[0]);
		break;
	}
}

/** Old code*/
float ARotatingPuzzle::NotSameNumber(){
	
	mRandom = FMath::RandHelper(6);
	float point = mPoints[mRandom];

	if (point == mOldTarget){
		return NotSameNumber();
	}
	else
		return point;
}
///End of old code

TArray<UTexture2D*> ARotatingPuzzle::GetMaterialsReference() {
	return mIndicatorTextures;
}

UMaterialInstanceDynamic* ARotatingPuzzle::GetMaterialReference() {
	return mIndicatorMeshMaterial;
}