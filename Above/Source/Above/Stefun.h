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
	AStefun(const FObjectInitializer& ObjectInitializer);

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
	
	//Makes the char jump
	UFUNCTION()
		void OnStartJump();
	UFUNCTION()
	void OnStopJump();

	UFUNCTION()
		void SetZoom();

	UFUNCTION()
		void UnSetZoom();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CharacterCamera)
		UCameraComponent* mFaceCam;

	//Sprint
	UFUNCTION()
		void EnableSprint();
	UFUNCTION()
		void DisableSprint();
	
	UFUNCTION()
		void ToggleCrouch();
	
	/** The normal walking speed of the character*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character)
		int32 mWalkSpeed;

	/** Sprint speed of the character */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character)
	int32 mSprintSpeed;

	/** Walk speed while crouching*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character)
		int32 mCrouchSpeed;
};
