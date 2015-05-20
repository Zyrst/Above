// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "GyroscopeFinishButton.generated.h"

UCLASS()
class ABOVE_API AGyroscopeFinishButton : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGyroscopeFinishButton();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	/** Called from BP */
	UFUNCTION(BlueprintCallable, Category = puzzle)
		void Activate();
};
