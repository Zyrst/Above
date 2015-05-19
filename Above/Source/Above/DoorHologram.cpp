// Fill out your copyright notice in the Description page of Project Settings.

#include "Above.h"
#include "DoorHologram.h"


// Sets default values
ADoorHologram::ADoorHologram()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADoorHologram::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADoorHologram::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

