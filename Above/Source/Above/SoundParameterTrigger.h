// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "SoundParameterTrigger.generated.h"

UCLASS()
class ABOVE_API ASoundParameterTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASoundParameterTrigger(const FObjectInitializer& ObjectInitializer);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	/** Name of parameter to set value on */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters")
		FName mParameterName;
	
	/** Value of parameter */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters")
		float mParameterValue;
};
