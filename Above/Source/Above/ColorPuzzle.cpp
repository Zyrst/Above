// Fill out your copyright notice in the Description page of Project Settings.

#include "Above.h"
#include "ColorPuzzle.h"


// Sets default values
AColorPuzzle::AColorPuzzle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


}

// Called when the game starts or when spawned
void AColorPuzzle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AColorPuzzle::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

