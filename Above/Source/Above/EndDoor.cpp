// Fill out your copyright notice in the Description page of Project Settings.

#include "Above.h"
#include "EndDoor.h"
#include "AboveSettings.h"


// Sets default values
AEndDoor::AEndDoor() {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEndDoor::BeginPlay() {
	Super::BeginPlay();

	AAboveSettings* settings = (AAboveSettings*)GetWorld()->GetWorldSettings();
	settings->SetLastDoor(this);
}

// Called every frame
void AEndDoor::Tick( float DeltaTime ) {
	Super::Tick( DeltaTime );
}

void AEndDoor::PuzzlesDone() {
	OnPuzzleDone();
}