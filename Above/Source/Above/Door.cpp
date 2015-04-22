// Fill out your copyright notice in the Description page of Project Settings.

#include "Above.h"
#include "Door.h"


// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RotationDegree = 90;
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	TArray<UStaticMeshComponent*> Components;
	this->GetComponents<UStaticMeshComponent>(Components);
	for (int32 i = 0; i < Components.Num(); i++){
		UStaticMeshComponent* mesh = Components[i];
		if (mesh->GetName() == "Door"){
			mDoorMesh = mesh->StaticMesh;
			mDoor = Components[i];
			GEngine->AddOnScreenDebugMessage(-1, 2.0, FColor::Green, TEXT("Able to find mesh"));
		}
		
	}
	//Two * Pi * R
	mBase = ((2 * 3.14) * mDoorMesh->GetBounds().SphereRadius);
	
}

// Called every frame
void ADoor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	if (mShouldRotate){
		//(two*pi*r*(CurrentDegree / 360))
		if ((mBase * (mCurrent / 360)) <= mTarget){
			//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, FString::Printf(TEXT("Degree %f"), ((mBase * (mCurrent / 360)))));
			mDoor->AddLocalRotation(FRotator::FRotator(0, 1, 0), false, nullptr);
			mCurrent += 1.0;
		}
		
		if (mBase * (mCurrent / 360) >= mTarget){
			mShouldRotate = false;
			Reset();
		}
	}
}

void ADoor::Activate(){
	mShouldRotate = true;
	float target = (RotationDegree / 360);
	mTarget = mBase * target;
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black, FString::Printf(TEXT("Size %f"), mTarget));
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, FString::Printf(TEXT("BlueprintDegree %f"), RotationDegree));

	SoundEventDoorOpen();
}

void ADoor::Reset(){
	mCurrent = 0;
	mTarget = 0;
}