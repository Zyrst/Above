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

	/** Sound event called when player is near enough to manipulate lamp sound by distance */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Sound")
		void SoundEventDistance();

	/** Sound event called when starting */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Sound")
		void SoundEventBeginPlay();

	/** Sound event called when intensity change */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Sound")
		void SoundEventIntensityChange();

	/** Called when something enter sphere collider */
	UFUNCTION()
		void OnOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	/** Called when something exits sphere collider*/
	UFUNCTION()
		void OnOverlapEnd(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	/** Returns distance between lamp and player */
	UFUNCTION(BlueprintCallable, Category = "fmod")
		float GetDistanceFromPlayer();

	/** Returns sound intensity level. For use with fmod*/
	UFUNCTION(BlueprintCallable, Category = "fmod")
		float GetSoundIntensityLevel();

	/** Returns sound intensity level. For use with fmod*/
	UFUNCTION(BlueprintCallable, Category = "fmod")
		float GetPlayedStatus();

private:
	bool mAction, mActionKill, mTrackPlayer;
	float mKillTimer;

	UActorComponent* mFireflyParticles;
	USphereComponent* mSphereCollider;
	AActor* mPlayerReference;

	float mSoundIntensity;

	bool mPressedBefore;
};
