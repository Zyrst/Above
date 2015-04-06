// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AboveButton.h"
#include <vector>
#include "GameFramework/Actor.h"
#include "Lamp.generated.h"

UCLASS()
class ABOVE_API ALamp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALamp(const FObjectInitializer& ObjectInitializer);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Pointer to light component. Pls don't sort
	TArray<UPointLightComponent*> mLights;

	// Default values for light. Pls don't sort
	std::vector<float> mLightDefaultIntensity;
	std::vector<float> mLightDefaultAttenuation;
	std::vector<FVector> mLightDefaultPosition;

	// The amount of flickering
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 flickerAmount;
	
	// Lerping light position based on this value
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float flickerIntensity;

	// Modify this to change how much the lamp "blinks"
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float blinkFactor;

	// First activate action
	UFUNCTION(BlueprintCallable, Category = "LampActions")
		void ActivateFirst();
	// Second activate action
	UFUNCTION(BlueprintCallable, Category = "LampActions")
		void ActivateSecond();
};
