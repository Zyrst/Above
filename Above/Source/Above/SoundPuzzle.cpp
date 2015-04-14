// Fill out your copyright notice in the Description page of Project Settings.

#include "Above.h"
#include "SoundPuzzle.h"
#include "PuzzzleSlab.h"


// Sets default values
ASoundPuzzle::ASoundPuzzle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASoundPuzzle::BeginPlay()
{
	Super::BeginPlay();
	mSteps = 0;
}

// Called every frame
void ASoundPuzzle::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ASoundPuzzle::Activate(){
	
	if (mSteps < 16 /*&& inte aktiverade redan*/){
		if (mSteps == 0){
			//Se att det är första i puzzlet 
			mSteps++;
		}
		else{
			mSteps++;
			//Tänd upp den
			//Släck en av lamporna på väggen
			//Spela upp ljud
		}
		
	}
}

void ASoundPuzzle::Reset(){
	if (mSteps == 16 /*&& inte rätt väg*/){
		mSteps = 0;
		//Släck andra saker 
	}
}