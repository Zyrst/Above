// Fill out your copyright notice in the Description page of Project Settings.

#include "Above.h"
#include "SoundPuzzle.h"
#include "PuzzzleSlab.h"
#include "LightIndicator.h"

// Sets default values
ASoundPuzzle::ASoundPuzzle(const FObjectInitializer& objectInit):
Super(objectInit)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}
 
// Called when the game starts or when spawned
void ASoundPuzzle::BeginPlay()
{
	Super::BeginPlay();
	mSteps = 0;

	for (TActorIterator<AActor> itr(GetWorld()); itr; ++itr){
		ALightIndicator* tmp = Cast<ALightIndicator>(*itr);
		if (tmp != nullptr){
			mLightInd = tmp;
		}
	}
}

// Called every frame
void ASoundPuzzle::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	if (mSteps == 16){
		for (int32 i = 0; i < 16; i++){
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, mWalkWay[i]->GetName());
		}
		mSteps = 0;
	}
}

void ASoundPuzzle::Activate(int32 index, UChildActorComponent* slab){
	//Spela upp ljud
	//Cast to Puzzleslab so we can use functions
	APuzzzleSlab* tmpSlab = Cast<APuzzzleSlab>(slab->ChildActor);
	if (tmpSlab != nullptr){
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Found Slab"));
		if (mSteps < 16 ){
			//Make sure we start from the begining of the puzzle
			if (mSteps == 0 && tmpSlab->mStartSlab){
				Reset();
				mSteps++;
				//Add to walkpath and light it up
				mWalkWay.Add(slab);
				tmpSlab->LightUpSlab();
				mLightInd->Reduce();
			}
			else if(mSteps != 0){
				if (!mWalkWay.Contains(slab)){
					mSteps++;
					mWalkWay.Add(slab);
					tmpSlab->LightUpSlab();
					mLightInd->Reduce();
				}
			}
		}
	}

	
}

void ASoundPuzzle::Reset(){
	//Don't want to crash when we try the puzzle for the first time
	if (mWalkWay.Num() != 0){
		for (int32 i = 0; i < 16; i++){
			APuzzzleSlab* tmpSlab = Cast<APuzzzleSlab>(mWalkWay[i]->ChildActor);
			if (tmpSlab != nullptr){
				tmpSlab->ResetSlab();

			}
		}
		//Empties the array but keep the same size so no need to allocate more room
		mWalkWay.Empty(16);
		mLightInd->Reset();
	}
}