// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "JellyFish.generated.h"

UCLASS()
class ABOVE_API AJellyFish : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AJellyFish();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	/** Movement speed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
		FVector mMovementSpeed;

	/** Movement location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
		FVector mTargetLocation;

	/** Ray trace distance */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
		float mTraceDistance;

	/** Random distance margin */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
		float mRandomDistance;

	/** Chain to center point */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
		FVector mCenterPoint;

	/** Max distance from center */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
		float mMaxCenterDistance;

private:
	void Move(float deltaTime);
	void RayTrace();
	void ChangeTarget();
	void Rotate(float deltaTime);
	void OutOfBounds();

	FVector mDelta;
	FVector mCurrentRotation;
	FVector mTargetRotation;

	float mRotateCounter;
};
