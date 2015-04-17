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
	for (int32 i = 0; i < 4; i++){
		mSounds.Add(false);
	}

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

	if (mDoneOnce == false){
		DoOnceLoad();
		mDoneOnce = true;
	}
	if (mSteps == 16){
		

		if (mWalkingWay.Equals(mRightWay)){
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("Went the right way"));
		}
		else if (!mWalkingWay.Equals(mRightWay)){
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("Went the wrong way"));
		}
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, mWalkingWay);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, mRightWay);
		mSteps = 0;
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, mWalkingWay);
	}
}

void ASoundPuzzle::DoOnceLoad(){
	for (int32 i = 0; i < mCorrectPath.Num(); i++){
		mCorPathSlabs.Add(MazeArray[mCorrectPath[i]]);
	}

	for (int32 i = 0; i < mCorrectPath.Num(); i++){
		mRightWay += FString::FromInt(mCorrectPath[i]);
	}
}

void ASoundPuzzle::Activate(int32 index, UChildActorComponent* slab){
	//Spela upp ljud
	//Cast to Puzzleslab so we can use functions
	APuzzzleSlab* tmpSlab = Cast<APuzzzleSlab>(slab->ChildActor);

	//Reset sound array at every activate
	for (int32 i = 0; i < 4; i++){
		mSounds[i] = false;
	}
	//Make sure we don't have a null pointer
	if (tmpSlab != nullptr){
		if (mSteps < 16 ){
			//Make sure we start from the begining of the puzzle
			if (mSteps == 0 && tmpSlab->mStartSlab){
				Reset();
				mSteps++;
				//Add to walkpath and light it up
				mWalkWay.Add(slab);
				tmpSlab->LightUpSlab();
				mLightInd->Reduce();
				mCorPathSteps++;
				mWalkingWay += FString::FromInt(index);
			}
			else if(mSteps != 0){
				if (!mWalkWay.Contains(slab)){
					mSteps++;
					mWalkWay.Add(slab);
					tmpSlab->LightUpSlab();
					mLightInd->Reduce();
					mWalkingWay += FString::FromInt(index);
				}
				if (mCorPathSlabs[mCorPathSteps]->GetName() == tmpSlab->GetName()){
					//(GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, tmpSlab->GetName());
					mCorPathSteps++;
				}
				
			}

			auto name = slab->GetAttachmentRoot()->GetName();
			auto rootLocation = slab->GetAttachmentRoot()->RelativeLocation;
			//slab->GetAttachmentRoot()->RelativeLocation;
			FVector tmpPos = slab->GetRelativeTransform().GetLocation();
			//tmpSlab->GetTransform().GetLocation();
			UE_LOG(LogTemp, Warning, TEXT("Location Root: %s"), *rootLocation.ToString());
			UE_LOG(LogTemp, Warning, TEXT("Location Slab: %s"), *tmpPos.ToString());
			FVector tmpNextPos;
			tmpNextPos = tmpNextPos.ZeroVector;
			UE_LOG(LogTemp, Warning, TEXT("mCorPathSteps: %d"), mCorPathSteps);
			if (mCorPathSteps < 16){
				auto tmp = mCorPathSlabs[(mCorPathSteps)]->GetTransform().GetRelativeTransform(slab->GetAttachmentRoot()->GetComponentTransform());
				tmpNextPos = tmp.GetLocation();
				UE_LOG(LogTemp, Warning, TEXT("Location Next Slab: %s"), *tmpNextPos.ToString());
			}

			float tmpX = 0;
			float tmpY = 0;
			if (!tmpNextPos.IsZero()){
				tmpX = tmpPos.X - tmpNextPos.X;
				tmpY = tmpPos.Y - tmpNextPos.Y;
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("tmpX value %f"), tmpX));
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("tmpY value %f"), tmpY));
				UE_LOG(LogTemp, Warning, TEXT("tmpX: %f"), tmpX);
				UE_LOG(LogTemp, Warning, TEXT("tmpY: %f"), tmpY);
			}

			if (tmpX > 50){
				mSounds[0] = true;
			}
			else if (tmpX < -50){
				mSounds[1] = true;
			}

			if (tmpY > 50){
				mSounds[2] = true;
			}
			else if (tmpY < -50){
				mSounds[3] = true;
			}

			for (int32 i = 0; i < 4; i++){
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, FString::Printf(TEXT("Bool: %s"), mSounds[i] ? TEXT("true") : TEXT("false")));
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
		mCorPathSteps = 0;

		for (int32 i = 0; i < 4; i++){
			mSounds[i] = false;
		}
	}
	
	mWalkingWay = NULL;
}
 