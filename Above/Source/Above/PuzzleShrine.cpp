// Fill out your copyright notice in the Description page of Project Settings.

#include "Above.h"
#include "PuzzleShrine.h"


// Sets default values
APuzzleShrine::APuzzleShrine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	mTuneToPlay = 0;
}

// Called when the game starts or when spawned
void APuzzleShrine::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APuzzleShrine::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void APuzzleShrine::Activate() {
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Activate"));

	PlayMusic();
}