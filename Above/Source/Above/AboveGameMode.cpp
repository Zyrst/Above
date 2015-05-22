// Fill out your copyright notice in the Description page of Project Settings.

#include "Above.h"
#include "AboveGameMode.h"
#include "Stefun.h"
#include "AboveSettings.h"
#include "EndDoor.h"
#include "Tree.h"

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
		if (mTree != nullptr)
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT(" Able to cast class"));
	}
}

void AAboveGameMode::SetCompleteStatus(AActor* puzzle, bool done) {
	
	if (!CompletedPuzzleArray.Find(puzzle))
		CompletedPuzzleArray.Add(puzzle);
	CompletedPuzzleArray[puzzle] = done;
	ActivateTreeEmmisive(puzzle);

	// Try getting reference array
	if (mSettings != nullptr) {
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
	}

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
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("AboveGameMode.cpp: Triggered the end"));

		destComp->ApplyRadiusDamage(500, destComp->GetRelativeTransform().GetLocation(), 100, 0, true);
		//Make debries of old battery fall through platform
		standPlat->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		//Be able to stand there again
		standPlat->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		mTrigger = true;
	}
	
}

void AAboveGameMode::ActivateTreeEmmisive(AActor* puzzle){
	if (mTree == nullptr)
		return;
	
	FString name= puzzle->GetName();

	if (name.Contains("Sound")){
		mTree->UpdateTree(0);
	}
	else if (name.Contains("Gyro")){
		mTree->UpdateTree(1);
	}
	else if (name.Contains("Color")){
		mTree->UpdateTree(2);
	}
}