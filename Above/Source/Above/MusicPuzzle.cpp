// Fill out your copyright notice in the Description page of Project Settings.

#include "Above.h"
#include "MusicPuzzle.h"


// Sets default values
AMusicPuzzle::AMusicPuzzle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Initiate array with zeros
	for (int32 i = 0; i < 3; i++) {
		DiscIndexArray.Push(0);
	}

	// Initiate array, no propper initiation of arrays in unreal
	int32 tableinit[] = { 3, 4, 2 };
	DiscIndexRefrenceArray.Append(tableinit, ARRAY_COUNT(tableinit));
}

// Called when the game starts or when spawned
void AMusicPuzzle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMusicPuzzle::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AMusicPuzzle::RotateDisc(int32 discNum) {
	// Index chosen disc by one
	if (discNum < DiscIndexArray.Num()) {
		DiscIndexArray[discNum] = ++DiscIndexArray[discNum] % 5;
	}
}

void AMusicPuzzle::Activate() {
	// Compare with correct combination
	if (DiscIndexArray == DiscIndexRefrenceArray) {
		PlayMusic();
	}

	else {
		PlayShortMusic();
	}
}