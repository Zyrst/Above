// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "AboveButton.generated.h"

UCLASS()
class ABOVE_API AAboveButton : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAboveButton(const FObjectInitializer& ObjectInitializer);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	/* Call this from code when activating button. 
	 * This function does some internal things and then sends an event to BP
	 */
	UFUNCTION(BlueprintCallable, Category = "ButtonActions")
		void Activate();

	// This event is called when player interacts with button
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "ButtonActions")
		void ButtonActivate();
};
