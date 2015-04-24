// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "PuzzleShrine.generated.h"

UCLASS()
class ABOVE_API APuzzleShrine : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APuzzleShrine();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION(BlueprintCallable, Category = Interaction)
		void Activate();
	
	UFUNCTION(BlueprintImplementableEvent, Category = Sound)
		void PlayMusic();
};
