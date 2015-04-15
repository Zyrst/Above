// Fill out your copyright notice in the Description page of Project Settings.

#include "Above.h"
#include "LightIndicator.h"
#include "PuzzleSlabIndicatorLight.h"

// Sets default values
ALightIndicator::ALightIndicator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ALightIndicator::BeginPlay()
{
	Super::BeginPlay();
	for (TActorIterator<AActor> itr(GetWorld()); itr; ++itr){
		APuzzleSlabIndicatorLight* tmp = Cast<APuzzleSlabIndicatorLight>(*itr);
		if (tmp != nullptr){
			mLights.Push(tmp);
		}
	}
}

// Called every frame
void ALightIndicator::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ALightIndicator::Reduce(){
	mLights[mLampsOff++]->LightOff();
}

void ALightIndicator::Reset(){
	for (int32 i = 0; i < mLights.Num(); i++){
		mLights[i]->Reset();
	}
	mLampsOff = 0;
}