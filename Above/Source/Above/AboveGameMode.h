// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "AboveGameMode.generated.h"

/**
 * 
 */
UCLASS()
class ABOVE_API AAboveGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AAboveGameMode(const class FObjectInitializer& ObjectInitializer);

	float getStandardFoV();
	float getZoomFoV();
	
	/** Sets the default FoV for the player*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Utility)
		float StandardF_O_V;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Utility)
		float ZoomF_O_V;

	/** Sets complete status on puzzle */
	UFUNCTION(BlueprintCallable, Category = Puzzle)
		void SetCompleteStatus(UObject* puzzle, bool status);

	/** Gets complete status on puzzle */
	UFUNCTION(BlueprintCallable, Category = Puzzle)
		bool GetCompleteStatus(UObject* puzzle);
	
	/** Sets begin status on puzzle */
	UFUNCTION(BlueprintCallable, Category = Puzzle)
		void SetStartedStatus(UObject* puzzle, bool status);

	/** Gets begin status on puzzle */
	UFUNCTION(BlueprintCallable, Category = Puzzle)
		bool GetStartedStatus(UObject* puzzle);


private:
	TMap<UObject*, bool> CompletedPuzzleArray;
	TMap<UObject*, bool> StartedPuzzleArray;
};
