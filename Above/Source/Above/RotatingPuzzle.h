// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "RotatingPuzzle.generated.h"

UCLASS()
class ABOVE_API ARotatingPuzzle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARotatingPuzzle();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION(BlueprintCallable, Category = Activation)
		void Activate(float target);

	void Reset();

	/**Get a random number which is not the current target*/
	UFUNCTION(BlueprintCallable, Category = RandomNum)
		float NotSameNumber();
	
	/**Array of points*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Points )
		TArray<float> mPoints;
	/**Last target*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Points)
		float mOldTarget;

private:
	bool mRotate;
	float mCalcTarget = 0;
	
	float mTarget = 0;
	float mBase;
	float mCurrent;
	UStaticMeshComponent* mDishMesh;
	FVector* mStartPos;
};
