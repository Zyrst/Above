// Fill out your copyright notice in the Description page of Project Settings.

#include "Above.h"
#include "Stefun.h"


// Sets default values
AStefun::AStefun()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AStefun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStefun::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AStefun::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

