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

	UFUNCTION(BlueprintNativeEvent, Category = Sound)
		void PlayMusic();

	UFUNCTION(BlueprintNativeEvent, Category = Sound)
		void PlayShortMusic();

	/** Indexes selected disc by one */
	UFUNCTION(BlueprintCallable, Category = Interaction)
	void RotateDisc(int32 discNum);

	/** Called to test if correct combination */
	UFUNCTION(BlueprintCallable, Category = Interaction)
	void Activate();

	// User combination
	TArray<int32> DiscIndexArray;

	// Correct combination
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Puzzle)
	TArray<int32> DiscIndexRefrenceArray;
	
};
