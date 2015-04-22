// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "SoundPuzzle.generated.h"

class APuzzzleSlab;
class ALightIndicator;

UCLASS()
class ABOVE_API ASoundPuzzle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASoundPuzzle(const FObjectInitializer& ObjectInitializer);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	void DoOnceLoad();

	UFUNCTION(BlueprintCallable, Category = Activation)
		void Activate(int32 index, UChildActorComponent* slab);
	UFUNCTION()
		void Reset();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Maze)
		TArray<AActor*> MazeArray;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Maze)
		TArray<int32> mCorrectPath;

	/**Sound events*/
	UFUNCTION(BlueprintImplementableEvent, Category = "fmod")
		void SoundEventLeft();
	UFUNCTION(BlueprintImplementableEvent, Category = "fmod")
		void SoundEventRight();
	UFUNCTION(BlueprintImplementableEvent, Category = "fmod")
		void SoundEventForward();
	UFUNCTION(BlueprintImplementableEvent, Category = "fmod")
		void SoundEventBack();

private:
	int32 mSteps;
	int32 mCorPathSteps;
	TArray<UChildActorComponent*> mWalkWay;
	TArray<AActor*> mCorPathSlabs;
	FString mWalkingWay;
	FString mRightWay;
	ALightIndicator* mLightInd;
	

	bool PuzzleCompleted = false;
	bool mDoneOnce = false;
};