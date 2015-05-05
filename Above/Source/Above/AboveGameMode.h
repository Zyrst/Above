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


private:
	TMap<AActor*, bool> CompletedPuzzleArray;
	TMap<AActor*, bool> StartedPuzzleArray;
	bool mTrigger;
};
