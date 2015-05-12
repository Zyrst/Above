// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "EndDoor.generated.h"

UCLASS()
class ABOVE_API AEndDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEndDoor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;


	/** Called when every puzzle is finished */
	UFUNCTION(BlueprintCallable, Category = Puzzle)
		void PuzzlesDone();

	UFUNCTION(BlueprintImplementableEvent, Category = Puzzle)
		void OnPuzzleDone();
	
};
