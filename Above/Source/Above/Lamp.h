// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AboveButton.h"
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
	TArray<float> mLightDefaultIntensity;
	TArray<float> mLightDefaultAttenuation;
	TArray<FVector> mLightDefaultPosition;

	// Time it takes to kill fireflies
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float mKillingDuration;

	// The amount of brightness increase when killing fireflies
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float mKillingBrightnessIncreaseFactor;

	// The amount of decrease in light when saving fireflies
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float mSavingBrightnessDecreaseFactor;


	// The amount of attenuation increase when killing fireflies
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float mKillingAttenuationIncreaseFactor;

	// The amount of decrease in attenuation when saving fireflies
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float mSavingAttenuationDecreaseFactor;

	// Interpolation speed when buttons are pressed
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float mTransitionSpeed;


	// The amount of flickering
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 mFlickerAmount;
	
	// Lerping light position based on this value
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float mFlickerIntensity;

	// Modify this to change how much the lamp "blinks"
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float mBlinkFactor;

	// First activate action
	UFUNCTION(BlueprintCallable, Category = "LampActions")
		void ActivateFirst();
	// Second activate action
	UFUNCTION(BlueprintCallable, Category = "LampActions")
		void ActivateSecond();


	/** Sound event called when fireflies are released */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Sound")
		void SoundEventFireflyRelease();

	/** Sound event called when fireflies are killed */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Sound")
		void SoundEventFireflyElectrocute();

	/** Sound event called when either button are pressed */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Sound")
		void SoundEventButtonPress();

private:
	bool mAction, mActionKill;
	float mKillTimer;

	UActorComponent* mFireflyParticles;
};
