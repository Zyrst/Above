// Fill out your copyright notice in the Description page of Project Settings.

#include "Above.h"
#include "AboveSettings.h"


void AAboveSettings::AddPuzzle(AActor* puzzle) {
	mPuzzles.Add(puzzle);
}

void AAboveSettings::SetLastDoor(AActor* door) {
	mLastDoor = door;
}

void AAboveSettings::SetTree(AActor* tree) {
	mTree = tree;
	if (mTree != nullptr)
		UE_LOG(LogTemp, Error, TEXT("Fuk"));
}

void AAboveSettings::SetStoryBoard(AActor* storyBoard){
	mStoryBoard = storyBoard;
	
}

