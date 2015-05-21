// Fill out your copyright notice in the Description page of Project Settings.

#include "Above.h"
#include "Door.h"


// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mMaterialArray.Init(6);

}

// Called when the game starts or when spawned
void ADoor::BeginPlay() {
	Super::BeginPlay();

	mMaterialArray[0] = mDoorMesh->CreateAndSetMaterialInstanceDynamic(6);
	mMaterialArray[1] = mDoorMesh->CreateAndSetMaterialInstanceDynamic(5);
	mMaterialArray[2] = mDoorMesh->CreateAndSetMaterialInstanceDynamic(2);
	mMaterialArray[3] = mDoorMesh->CreateAndSetMaterialInstanceDynamic(3);
	mMaterialArray[4] = mDoorMesh->CreateAndSetMaterialInstanceDynamic(0);
	mMaterialArray[5] = mDoorMesh->CreateAndSetMaterialInstanceDynamic(4);
}

// Called every frame
void ADoor::Tick( float DeltaTime ) {
	Super::Tick(DeltaTime);

}