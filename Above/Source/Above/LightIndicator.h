// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "LightIndicator.generated.h"

class APuzzleSlabIndicatorLight;

UCLASS()
class ABOVE_API ALightIndicator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALightIndicator();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION(BlueprintCallable, Category = Reduce)
		void Reduce();

	UFUNCTION(BlueprintCallable, Category = Reset)
		void Reset();
private:
	int32 mLampsOff = 0;
	
	TArray<APuzzleSlabIndicatorLight*> mLights;
};
