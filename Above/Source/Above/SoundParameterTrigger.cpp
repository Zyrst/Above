// Fill out your copyright notice in the Description page of Project Settings.

#include "Above.h"
#include "SoundParameterTrigger.h"


// Sets default values
ASoundParameterTrigger::ASoundParameterTrigger(const FObjectInitializer& ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASoundParameterTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASoundParameterTrigger::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}