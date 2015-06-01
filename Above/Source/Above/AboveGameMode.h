// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "Tree.h"
#include "AboveGameMode.generated.h"

class AAboveSettings;
class AStoryBoard;

/**
 * 
 */
UCLASS()
class ABOVE_API AAboveGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AAboveGameMode(const class FObjectInitializer& ObjectInitializer);
	
	virtual void OnConstruction(const FTransform& Transform) override;

	/** Sets complete status on puzzle */
	UFUNCTION(BlueprintCallable, Category = Puzzle)
		void SetCompleteStatus(AActor* puzzle, bool done);

	/** Gets complete status on puzzle */
	UFUNCTION(BlueprintCallable, Category = Puzzle)
		bool GetCompleteStatus(AActor* puzzle);
	
	/** Sets begin status on puzzle */
	UFUNCTION(BlueprintCallable, Category = Puzzle)
		void SetStartedStatus(AActor* puzzle, bool started);

	/** Gets begin status on puzzle */
	UFUNCTION(BlueprintCallable, Category = Puzzle)
		bool GetStartedStatus(AActor* puzzle);

	/**Player End Game Trigger*/
	UFUNCTION(BlueprintCallable, Category = EndGame)
		void EndTrigger(UDestructibleComponent* destComp, UPrimitiveComponent* standPlat);
	UFUNCTION(BlueprintImplementableEvent, Category = EndGame)
		void EndCredit();
	UFUNCTION()
		void ActivateTreeEmmisive(AActor* puzzle);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Tree)
		AActor* Tree_BP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Story)
		AActor* StoryBoard_BP;

	/** Debug cheats */
	UFUNCTION(Exec, BlueprintCallable, Category = "Debug")
		void FinishSound();
	UFUNCTION(Exec, BlueprintCallable, Category = "Debug")
		void FinishSpatial();
	UFUNCTION(Exec, BlueprintCallable, Category = "Debug")
		void FinishColor();

private:
	TMap<AActor*, bool> CompletedPuzzleArray;
	TMap<AActor*, bool> StartedPuzzleArray;
	bool mTrigger;

	ATree* mTree;
	AStoryBoard* mStory;
	AAboveSettings* mSettings;

	int32 mPuzzleFinishedNum = 0;
};
