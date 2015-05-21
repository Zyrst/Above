// Fill out your copyright notice in the Description page of Project Settings.

#include "Above.h"
#include "GyroscopeFinishButton.h"
#include "AboveGameMode.h"


// Sets default values
AGyroscopeFinishButton::AGyroscopeFinishButton(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGyroscopeFinishButton::BeginPlay(){
	Super::BeginPlay();
}

// Called every frame
void AGyroscopeFinishButton::Tick( float DeltaTime ){
	Super::Tick( DeltaTime );
}

void AGyroscopeFinishButton::Activate() {
	// Puzzle is done
	AAboveGameMode* mode = (AAboveGameMode*)GetWorld()->GetAuthGameMode();
	if (mode != nullptr)
		mode->SetCompleteStatus(this, true);
}