// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "MusicPuzzle.generated.h"

UCLASS()
class ABOVE_API AMusicPuzzle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMusicPuzzle();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	/** On correct combination */
	UFUNCTION(BlueprintImplementableEvent, Category = Sound)
		void PlayMusic();

	/** On incorrect combination*/
	UFUNCTION(BlueprintImplementableEvent, Category = Sound)
		void PlayShortMusic(UPARAM(ref)TArray<int32>& currentCombination);

	/** Indexes selected disc by one */
	UFUNCTION(BlueprintCallable, Category = Interaction)
	void RotateDisc(int32 discNum);

	/** Called to test if correct combination */
	UFUNCTION(BlueprintCallable, Category = Interaction)
	void Activate();

	// Player input combination
	TArray<int32> DiscIndexArray;

	// Correct combination
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Puzzle)
	TArray<int32> DiscIndexRefrenceArray;

	/** Movement curve */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults")
		UCurveFloat* mMovementCurve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
		TArray<UStaticMeshComponent*> mDiscArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Defaults)
		float mDiscRadius = 100;

	int32 mNumberOfDiscs;

	float mRotationSpeed;

	TArray<FVector> mDiscTargetAngle;
	TArray<FVector> mDiscCurrentAngle;
	TArray<float> mDiscMoveTracker;
	
};
