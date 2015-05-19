// Fill out your copyright notice in the Description page of Project Settings.

#include "Above.h"
#include "Clouds.h"


// Sets default values
AClouds::AClouds(const FObjectInitializer& ObjectInitializer) :
Super(ObjectInitializer) {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mRootComponent	= ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("Root component"));
	SetRootComponent(mRootComponent);
}

void AClouds::OnConstruction(const FTransform& Transform) {
	Super::OnConstruction(Transform);
}

// Called when the game starts or when spawned
void AClouds::BeginPlay() {
	Super::BeginPlay();
	
}

// Called every frame
void AClouds::Tick( float DeltaTime ) {
	Super::Tick( DeltaTime );

	mInnerRotation	+= InnerSpeed * DeltaTime;
	mMiddleRotation += MiddleSpeed * DeltaTime;
	mOuterRotation	+= OuterSpeed * DeltaTime;

	FRotator ir = FRotator::ZeroRotator;
	ir.Add(0, mInnerRotation, 0);
	InnerClouds->SetRelativeRotation(ir);

	FRotator mr = FRotator::ZeroRotator;
	mr.Add(0, mMiddleRotation, 0);
	MiddleClouds->SetWorldRotation(mr);

	FRotator or = FRotator::ZeroRotator;
	or.Add(0, mOuterRotation, 0);
	OuterClouds->SetRelativeRotation(or);
}

