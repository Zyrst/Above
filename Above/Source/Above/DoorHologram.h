// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "DoorHologram.generated.h"

UCLASS()
class ABOVE_API ADoorHologram : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoorHologram();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	/** Pointer to button */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pointer)
		TArray<AActor*> mButtonArray;
	/** Should it be open at start*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Start)
		bool mStartOpen;
};
