// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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
	void InteractWithTrigger(int32 triggerNum);

	/** Empty list of activated triggers */
	UFUNCTION(BlueprintCallable, Category = Interaction)
	void EndHoldButton();

	// Array to store order of pressed buttons
	TArray<int32> mButtonOrder;

	// Used to test if buttons are pressed in order
	bool mIsInOrder;

	/** Unlock door */
	UFUNCTION(BlueprintNativeEvent, Category = Interaction)
		void Unlock();

	/** Light specified button */
	UFUNCTION(BlueprintNativeEvent, Category = Interaction)
		void LightButton(int32 buttonNum);
};
