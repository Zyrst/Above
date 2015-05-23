// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DuoFVector.h"
#include "GameFramework/Actor.h"
#include "DoorPuzzle.generated.h"

UCLASS()
class ABOVE_API ADoorPuzzle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoorPuzzle();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	/** Mark numberd trigger as activated */
	UFUNCTION(BlueprintCallable, Category = Interaction)
		void InteractWithTrigger(int32 triggerNum, FVector newTriggerPos);

	/** Empty list of activated triggers */
	UFUNCTION(BlueprintCallable, Category = Interaction)
	void EndHoldButton();

	// Array to store order of pressed buttons
	TArray<int32> mButtonOrder;

	// Used to test if buttons are pressed in order
	bool mIsInOrder;

	/** Unlock door */
	UFUNCTION(BlueprintImplementableEvent, Category = Interaction)
		void Unlock();

	/** Light specified button */
	UFUNCTION(BlueprintImplementableEvent, Category = Interaction)
		void LightButton(int32 buttonNum);

	UFUNCTION(BlueprintImplementableEvent, Category = Interaction)
		void UnLightButton(int32 buttonNum);

	/** Is called when button is activated, passes how many lights are activated (for use with fmod) */
	UFUNCTION(BlueprintImplementableEvent, Category = fmod)
		void SoundEventButtonInteract(int32 nActivatedButtons);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = fmod)
		FVector mSoundLocation;

	// Pointer to player focus location
	FVector* mPointerTarget;
	
	FVector mLastTriggerLocation;

	TArray<DuoFVector> mLineArray;

	bool mDrawLine;

	void SetLastTriggerPos(FVector pos);

	bool mContainedLastTrigger;
};
