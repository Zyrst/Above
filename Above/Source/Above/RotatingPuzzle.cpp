// Fill out your copyright notice in the Description page of Project Settings.

#include "Above.h"
#include "RotatingPuzzle.h"


// Sets default values
ARotatingPuzzle::ARotatingPuzzle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARotatingPuzzle::BeginPlay()
{
	Super::BeginPlay();
	mRotate = false;
	mOldTarget = 0;

	TArray<UStaticMeshComponent*> Components;
	this->GetComponents<UStaticMeshComponent>(Components);
	for (int32 i = 0; i < Components.Num(); i++){
		UStaticMeshComponent* mesh = Components[i];
		if (mesh->GetName() == "Disk"){
			mDishMesh = Components[i];

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
	
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Vector &f"), mStartPos));
	//Activate(90);
}

// Called every frame
void ARotatingPuzzle::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if (mRotate){
		//Do stuff
		//(two*pi*r*(CurrentDegree / 360))
		if ((mBase * (mCurrent / 360)) < mCalcTarget){
			
			mDishMesh->AddLocalRotation(FRotator::FRotator(0, 1, 0), false, nullptr);
			//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::Printf(TEXT("Yaw float value %f"), mDishMesh->GetComponentRotation().Yaw));
			//this->AddActorLocalRotation(FRotator(0, 1, 0), false, nullptr);
			mCurrent += 1.0;
		}

		if ((mBase * (mCurrent / 360)) >= mCalcTarget){
			//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::Printf(TEXT("Current rotate value %f"), mCurrent));
			//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT("mCalcTarget %f"), mTarget));
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("Stopped"));
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, FString::Printf(TEXT("mCurrent %f"), mCurrent));
			mRotate = false;
			mOldTarget = mTarget;
			Reset();
		}
	}
}

void ARotatingPuzzle::Activate(float target){
	
	mRotate = true;
	mTarget = target;
	GEngine->AddOnScreenDebugMessage(-1, 8.0f, FColor::Red, FString::Printf(TEXT("Target from array %f"), (target)));
	GEngine->AddOnScreenDebugMessage(-1, 8.0f, FColor::Red, FString::Printf(TEXT("old target %f"), ( mOldTarget)));
	
	float calc = 0;
	float num = 0;
	float sum = 0;
	for (int32 i = 0; i < mPoints.Num(); i++){
		if (mPoints[i] == mOldTarget){
			calc = mPoints[i];
			num = i;
		}
	}

	bool loop = true;
	int32 j = num;
	while (loop){
		if ( j == mPoints.Num() - 1){
			if (mPoints[j] == mTarget){
				//sum += 60;
				loop = false;
			}
			else{
				sum += 60;
				j = 0;
			}

		}
		else {
			if (mPoints[j] == mTarget){
				//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, FString::Printf(TEXT("Array value %f"), mPoints[j]));
				//sum += 60;
				loop = false;
			}
			else{
				sum += 60;
				j++;
			}


		}
	}
	GEngine->AddOnScreenDebugMessage(-1, 8.0f, FColor::Magenta, FString::Printf(TEXT("Degree to move %f"), sum));
	mCalcTarget = mBase * ((sum / 360));
}

void ARotatingPuzzle::Reset(){
	mCurrent = 0;
}

float ARotatingPuzzle::NotSameNumber(){
	int32 random = FMath::RandHelper(5);

	float point = mPoints[random];

	if (point == mOldTarget){
		NotSameNumber();
	}
	else
		return point;

}