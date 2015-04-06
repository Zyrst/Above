// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Door.generated.h"

UCLASS()
class ABOVE_API ADoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION(BlueprintCallable, Category = Activation)
		void Activate(); 

	void Reset();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Rotation)
		int32 RotationDegree;
private:
	int mRot = 0;
	bool shouldRotate = false;
	FRotator rotation;
	float degree;
};
