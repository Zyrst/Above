// Fill out your copyright notice in the Description page of Project Settings.

#include "Above.h"
#include "AboveButton.h"


// Sets default values
AAboveButton::AAboveButton(const FObjectInitializer& ObjectInitializer) {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAboveButton::BeginPlay() {
	Super::BeginPlay();
}

// Called every frame
void AAboveButton::Tick( float DeltaTime ) {
	Super::Tick( DeltaTime );
}

void AAboveButton::Activate() {
	// Do relevant stuff here, like playing animation and shizz

	// Call event for use in BP
	this->ButtonActivate();
}