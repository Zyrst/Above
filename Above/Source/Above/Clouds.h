// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Clouds.generated.h"

UCLASS()
class ABOVE_API AClouds : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AClouds(const FObjectInitializer& ObjectInitializer);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	virtual void OnConstruction(const FTransform& Transform) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = poop)
		float InnerSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = poop)
		float MiddleSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = poop)
		float OuterSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = poop)
		UStaticMeshComponent* OuterClouds;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = poop)
		UStaticMeshComponent* MiddleClouds;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = poop)
		UStaticMeshComponent* InnerClouds;

private:
	USceneComponent* mRootComponent;

	float mInnerRotation;
	float mMiddleRotation;
	float mOuterRotation;
};
