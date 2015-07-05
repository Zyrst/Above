// Fill out your copyright notice in the Description page of Project Settings.

#include "Above.h"
#include "AboveGameMode.h"
#include "Stefun.h"
#include "AboveSettings.h"
#include "EndDoor.h"
#include "Tree.h"
#include "StoryBoard.h"

AAboveGameMode::AAboveGameMode(const class FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer){
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnObject(TEXT("Blueprint'/Game/Blueprints/Characters/Stefun_Blueprint.Stefun_Blueprint_C'"));
	if (PlayerPawnObject.Class != NULL){
		DefaultPawnClass = PlayerPawnObject.Class;
	}
	if ((GEngine != NULL) && (GEngine->GameViewport != NULL)){
		GEngine->GameViewport->SetSuppressTransitionMessage(true);
	}

	static ConstructorHelpers::FClassFinder<AHUD> HUD(TEXT("Blueprint'/Game/Blueprints/HUDs/DefaultHUD.DefaultHUD_C'"));
	if (HUD.Class != NULL)
		HUDClass = HUD.Class;
	mTrigger = false;
}

void AAboveGameMode::OnConstruction(const FTransform& transform){
	mSettings = (AAboveSettings*)GetWorld()->GetWorldSettings();
	if (mSettings != nullptr){
		mTree = (ATree*)mSettings->mTree;
		mStory = (AStoryBoard*)mSettings->mStoryBoard;
	}
}

void AAboveGameMode::SetCompleteStatus(AActor* puzzle, bool done) {
	CompletedPuzzleArray[puzzle] = done;
	
	if (!CompletedPuzzleArray.Find(puzzle)) {
		CompletedPuzzleArray.Add(puzzle);
		mPuzzleFinishedNum++;
		return;
	}
	ActivateTreeEmmisive(puzzle);

	
	if (mPuzzleFinishedNum >= 3) {
		AEndDoor* endDoor = (AEndDoor*)mSettings->mLastDoor;

		// Tell end door that puzzles are done
		if (endDoor != nullptr)
			endDoor->PuzzlesDone();
	}


	// Try getting reference array
	/*if (mSettings != nullptr) {
		// Check if same number of finieshed puzzles equals max number of puzzles
		if (CompletedPuzzleArray.Num() >= mSettings->mPuzzles.Num()) {
			bool everythingDone = true;

			// Check if references match
			for (int32 i = 0; i < mSettings->mPuzzles.Num(); i++) {
				if (!CompletedPuzzleArray.Find(mSettings->mPuzzles[i]))
					everythingDone = false;
			}

			// Puzzles are done
			if (everythingDone) {
				AEndDoor* endDoor = (AEndDoor*)mSettings->mLastDoor;

				// Tell end door that puzzles are done
				if (endDoor != nullptr)
					endDoor->PuzzlesDone();
			}
		}
	}*/

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("AboveGameMode.cpp: %s completed"), *puzzle->GetName()));
}

bool AAboveGameMode::GetCompleteStatus(AActor* puzzle) {
	if (CompletedPuzzleArray.Find(puzzle))
		return CompletedPuzzleArray[puzzle];
	return false;
}


void AAboveGameMode::SetStartedStatus(AActor* puzzle, bool started) {
	if (!StartedPuzzleArray.Find(puzzle))
		StartedPuzzleArray.Add(puzzle);
	StartedPuzzleArray[puzzle] = started;

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("AboveGameMode.cpp: %s started"), *puzzle->GetName()));
}

bool AAboveGameMode::GetStartedStatus(AActor* puzzle) {
	if (StartedPuzzleArray.Find(puzzle))
		return StartedPuzzleArray[puzzle];
	return false;
}

void AAboveGameMode::EndTrigger(UDestructibleComponent* destComp, UPrimitiveComponent* standPlat){
	//Make sure we have pressed button first
	if (!mTrigger){
		destComp->ApplyRadiusDamage(10, destComp->GetRelativeTransform().GetLocation(), 5, 0, true);
		//Make debries of old battery fall through platform
		standPlat->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		//Be able to stand there again
		standPlat->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		mTrigger = true;
	}
	
}

void AAboveGameMode::ActivateTreeEmmisive(AActor* puzzle){
	
	FString name= puzzle->GetName();

	if (name.Contains("Sound")){
		((ATree*)mSettings->mTree)->UpdateTree(0);
		((AStoryBoard*)mSettings->mStoryBoard)->UpdateBoard();
	}
	else if (name.Contains("Gyro")){
		((ATree*)mSettings->mTree)->UpdateTree(1);
		((AStoryBoard*)mSettings->mStoryBoard)->UpdateBoard();
	}
	else if (name.Contains("Color")){
		((ATree*)mSettings->mTree)->UpdateTree(2);
		((AStoryBoard*)mSettings->mStoryBoard)->UpdateBoard();
	}

	
}

void AAboveGameMode::FinishSound() {
	if (mSettings == nullptr)
		return;

	for (int32 i = 0; i < mSettings->mPuzzles.Num(); i++) {
		FString name = mSettings->mPuzzles[i]->GetName();
		if (mSettings->mPuzzles[i]->GetName().Contains("Sound")) {
			SetCompleteStatus(mSettings->mPuzzles[i], true);
		}
	}
}

void AAboveGameMode::FinishSpatial() {
	if (mSettings == nullptr)
		return;

	for (int32 i = 0; i < mSettings->mPuzzles.Num(); i++) {
		if (mSettings->mPuzzles[i]->GetName().Contains("Gyro")) {
			SetCompleteStatus(mSettings->mPuzzles[i], true);
		}
	}
}

void AAboveGameMode::FinishColor() {
	if (mSettings == nullptr)
		return;

	for (int32 i = 0; i < mSettings->mPuzzles.Num(); i++) {
		if (mSettings->mPuzzles[i]->GetName().Contains("Color")) {
			SetCompleteStatus(mSettings->mPuzzles[i], true);
		}
	}
}
