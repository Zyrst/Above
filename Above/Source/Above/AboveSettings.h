// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/WorldSettings.h"

#include "AboveSettings.generated.h"

/**
 * 
 */
UCLASS()
class ABOVE_API AAboveSettings : public AWorldSettings
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Constants)
		FName mHighlightColorParameterName = "HighlightColor";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Constants)
		FLinearColor mHighlightColor;
	
	/** Array for holding references to each puzzle */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = World)
		TArray<AActor*> mPuzzles;

	/** Reference to door that opens when all puzzles are done */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = World)
		AActor* mLastDoor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = World)
		AActor* mTree;
	
};
