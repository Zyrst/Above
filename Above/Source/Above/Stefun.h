// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Stefun.generated.h"

UCLASS()
class ABOVE_API AStefun : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AStefun();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	//Makes char go forward and backward
	UFUNCTION()
	void MoveForward(float val);
	//Makes char move right and lefts
	UFUNCTION()
	void MoveRight(float val);
	
};
