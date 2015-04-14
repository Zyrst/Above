// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "SoundPuzzle.generated.h"

class APuzzzleSlab;

UCLASS()
class ABOVE_API ASoundPuzzle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASoundPuzzle();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION()
		void Activate();
	UFUNCTION()
		void Reset();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Maze)
		TArray<APuzzzleSlab*> MazeArray;
	

private:
	int32 mSteps;
	
};
