// Fill out your copyright notice in the Description page of Project Settings.

#include "Above.h"
#include "DoorSpatial.h"


// Sets default values
ADoorSpatial::ADoorSpatial()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADoorSpatial::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADoorSpatial::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

