// Fill out your copyright notice in the Description page of Project Settings.

#include "Above.h"
#include "AboveGameMode.h"

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
}

float AAboveGameMode::getStandardFoV(){
	return StandardF_O_V;
}

float AAboveGameMode::getZoomFoV(){
	return ZoomF_O_V;
}


void AAboveGameMode::SetCompleteStatus(AActor* puzzle, bool done) {
	if (!CompletedPuzzleArray.Find(puzzle))
		CompletedPuzzleArray.Add(puzzle);
	CompletedPuzzleArray[puzzle] = done;
}

bool AAboveGameMode::GetCompleteStatus(AActor* puzzle) {
	if (CompletedPuzzleArray.Find(puzzle))
		return CompletedPuzzleArray[puzzle];
	return false;
}


void AAboveGameMode::SetStartedStatus(AActor* puzzle, bool started) {
	if (StartedPuzzleArray.Find(puzzle))
		StartedPuzzleArray.Add(puzzle);
	StartedPuzzleArray[puzzle] = started;
}

bool AAboveGameMode::GetStartedStatus(AActor* puzzle) {
	if (StartedPuzzleArray.Find(puzzle))
		return StartedPuzzleArray[puzzle];
	return false;
}

void AAboveGameMode::EndTrigger(){
	//Stuff to be done
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("Triggered the end"));
	
}