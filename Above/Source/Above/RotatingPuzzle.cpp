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

	TArray<UStaticMeshComponent*> Components;
	this->GetComponents<UStaticMeshComponent>(Components);
	for (int32 i = 0; i < Components.Num(); i++){
		UStaticMeshComponent* mesh = Components[i];
		if (mesh->GetName() == "Disk"){
			mDishMesh = Components[i];

		}
	}
	mBase = (2 * 3.14) * mDishMesh->StaticMesh->GetBounds().SphereRadius;
	for (int32 i = 0; i < 6; i++){
		if (i == 0)
			mPoints.Push(0);
		else
			mPoints.Push(i * 60);
	}
	for (int32 j = 0; j < mPoints.Num(); j++){
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, FString::Printf(TEXT("Number %f"), mPoints[j]));
	}
	Activate(90);
}

// Called every frame
void ARotatingPuzzle::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if (mRotate){
		//Do stuff
		//(two*pi*r*(CurrentDegree / 360))
		if ((mBase * (mCurrent / 360)) <= mTarget){
			//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, FString::Printf(TEXT("Degree %f"), ((mBase * (mCurrent / 360)))));
			//mDishMesh->AddLocalRotation(FRotator::FRotator(0, 1, 0), false, nullptr);
			this->AddActorLocalRotation(FRotator(0, 1, 0), false, nullptr);
			mCurrent += 1.0;
		}

		if (mBase * (mCurrent / 360) >= mTarget){
			mRotate = false;
			Reset();
		}
	}
}

void ARotatingPuzzle::Activate(float target){
	mRotate = true;
	mTarget = mBase * (target / 360);
}

void ARotatingPuzzle::Reset(){
	mCurrent = 0;
	mTarget = 0;
}