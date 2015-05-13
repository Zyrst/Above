// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "GyroscropePuzzle.generated.h"

UCLASS()
class ABOVE_API AGyroscropePuzzle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGyroscropePuzzle(const FObjectInitializer& ObjectInitializer);

	virtual void OnConstruction(const FTransform& Transform) override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	/** Radius of innermost circle */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Defaults)
		float mInnerCircleRadius = 100;

	/** Radius of middle circle */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Defaults)
		float mMiddleCircleRadius = 200;

	/** Radius of outer circle */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Defaults)
		float mOuterCircleRadius = 300;

	/** Public function for rotating outer circle (probably called by blueprint inheriting this class) */
	UFUNCTION(BlueprintCallable, Category = Puzzle)
		void AddOuterRotation();

	/** Public function for rotating middle circle (probably called by blueprint inheriting this class) */
	UFUNCTION(BlueprintCallable, Category = Puzzle)
		void AddMiddleRotation();

	/** Public function for rotating inner circle (probably called by blueprint inheriting this class) */
	UFUNCTION(BlueprintCallable, Category = Puzzle)
		void AddInnerRotation();

	/** Call this to initiate rotation (probably called by blueprint inheriting this class) */
	UFUNCTION(BlueprintCallable, Category = Puzzle)
		void ApplyRotation();

	/** Resets rotation */
	UFUNCTION(BlueprintCallable, Category = Puzzle)
		void ResetRotation();


	/** Trigger that adds inner circle rotation */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Triggers)
		AActor* mInnerCircleButton;
	
	/** Trigger that adds middle circle rotation */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Triggers)
		AActor* mMiddleCircleButton;
	
	/** Trigger that adds outer circle rotation */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Triggers)
		AActor* mOuterCircleButton;
	
	/** Trigger that initiates rotation */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Triggers)
		AActor* mActivateRotationTrigger;

	/** How fast pieces should rotate */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Defaults)
		float mRotationSpeed = 0.01;

	/** How much pieces should rotate each time */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Defaults)
		float mMoveAmount = 30;

	/** Movement curve */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults")
		UCurveFloat* mMovementCurve;

	UFUNCTION(BlueprintImplementableEvent, Category = "fmod")
		void SoundEventBeginRotate();

	UFUNCTION(BlueprintImplementableEvent, Category = "fmod")
		void SoundEventEndRotate();



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults")
		float InnerAngle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults")
		float MiddleAngle;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults")
		float OuterAngle;

private:
	FVector mInnerTargetAngle;
	FVector mMiddleTargetAngle;
	FVector mOuterTargetAngle;

	FVector mInnerCurrentAngle;
	FVector mMiddleCurrentAngle;
	FVector mOuterCurrentAngle;

	bool mShouldRotateOuter = false;
	bool mShouldRotateMiddle = false;
	bool mShouldRotateInner = false;
	bool mShouldRotateAnything = false;

	USceneComponent* mRoot;
	

	void AddRotationOuterHelper(FVector amount);
	void AddRotationMiddleHelper(FVector amount);
	void AddRotationInnerHelper(FVector amount);

	// For tracking movement along interpolation
	float mOuterMoveTracker = 0;
	float mMiddleMoveTracker = 0;
	float mInnerMoveTracker = 0;

	USphereComponent* mInnerSphere;
	USphereComponent* mMiddleSphere;
	USphereComponent* mOuterSphere;
};
