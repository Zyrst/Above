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
	Activate();
	
}

// Called every frame
void ADoor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	if (shouldRotate){
		if ((this->GetActorRotation().Vector().Y - rotation.Vector().Y)  < degree ){
			//FMath::Atan(this->GetActorRotation().Vector().Y - rotation.Vector().Y);
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, FString::Printf(TEXT("Degree %f"),(this->GetActorRotation().Vector().Y - rotation.Vector().Y)));
			this->AddActorLocalRotation(FRotator::FRotator(0, 1, 0), false, nullptr);
			mRot++;
		}
		if ((this->GetActorRotation().Vector().Y - rotation.Vector().Y) >= degree){
			shouldRotate = false;
		}
	}
	
	
	
}

void ADoor::Activate(){
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("Rotate door now"));
	//this->AddActorLocalRotation(FRotator::FRotator(0, 1, 0), false, nullptr);
	shouldRotate = true;
	rotation = this->GetActorRotation();
	degree = 0.01 * RotationDegree;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, FString::Printf(TEXT("BlueprintDegree %d"), RotationDegree));
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, FString::Printf(TEXT("RotDegree %f"), degree));
}

void ADoor::Reset(){
	mRot = 0;
}