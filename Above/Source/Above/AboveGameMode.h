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

	int32 getStandardFoV();
	
	/** Sets the default FoV for the player*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Utility)
		int32 StandardFoV;

private:
	int32 mStandardFoV;
};
