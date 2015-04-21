// Fill out your copyright notice in the Description page of Project Settings.

#include "Above.h"
#include "Walkway.h"


// Sets default values
AWalkway::AWalkway()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWalkway::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWalkway::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AWalkway::Activate_Implementation() {

}

void AWalkway::ActivatePartly_Implementation() {

}