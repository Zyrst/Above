// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "SoundPuzzle.generated.h"

class APuzzzleSlab;

UCLASS()
class ABOVE_API ASoundPuzzle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASoundPuzzle(const FObjectInitializer& ObjectInitializer);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION(BlueprintCallable, Category = Activation)
		void Activate(int32 index);
	UFUNCTION()
		void Reset();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Maze)
		TArray<AActor*> MazeArray;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Slab)
		UChildActorComponent* mChild;

private:
	int32 mSteps;
	
};
