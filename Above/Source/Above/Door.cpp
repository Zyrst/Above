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
			GEngine->AddOnScreenDebugMessage(-1, 2.0, FColor::Green, TEXT("Able to find mesh"));
		}
		
	}
	Activate();
	
}

// Called every frame
void ADoor::Tick( float DeltaTime )
{
	
	Super::Tick( DeltaTime );
	if (shouldRotate){
		if ((mBase * (mCurrent / 360)) <= mTarget){
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, FString::Printf(TEXT("Degree %f"), ((mBase * (mCurrent / 360)))));
			this->AddActorLocalRotation(FRotator::FRotator(0, 1, 0), false, nullptr);
			mCurrent += 1.0;
		}
		if (mBase * (mCurrent / 360) >= mTarget){
			shouldRotate = false;
		}
	}
}

void ADoor::Activate(){
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("Rotate door now"));
	//this->AddActorLocalRotation(FRotator::FRotator(0, 1, 0), false, nullptr);
	shouldRotate = true;
	rotation = this->GetActorRotation();
	mBase = ((2 * 3.14) * mDoorMesh->GetBounds().SphereRadius);
	float mellow = (RotationDegree / 360);
	mTarget = mBase * mellow;
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black, FString::Printf(TEXT("Size %f"), mTarget));
	degree = 0.01 * RotationDegree;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, FString::Printf(TEXT("BlueprintDegree %f"), RotationDegree));
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, FString::Printf(TEXT("RotDegree %f"), degree));
}

void ADoor::Reset(){
	mRot = 0;

}