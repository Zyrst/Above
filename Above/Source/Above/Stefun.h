// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "InteractionTrigger.h"
#include "GameFramework/Character.h"
#include "Blueprint/UserWidget.h"
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

	/** Zooms in */
	UFUNCTION()
		void SetZoom();

	/** Zooms out */
	UFUNCTION()
		void UnSetZoom();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = CharacterCamera)
		UCameraComponent* mFaceCam;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = CharacterCamera)
		UCameraComponent* mThirdPersonCam;

	//Sprint
	UFUNCTION()
		void EnableSprint();
	UFUNCTION()
		void DisableSprint();
	
	UFUNCTION()
		void ToggleCrouch();

	UFUNCTION(BlueprintCallable, Category = Pause)
		void TogglePause();
	
	/** The normal walking speed of the character*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character)
		int32 mWalkSpeed;

	/** Sprint speed of the character */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character)
	int32 mSprintSpeed;

	/** Walk speed while crouching*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character)
		int32 mCrouchSpeed;

	/** Fondle - Calls Interact() on InteractionTrigger of looked at obeject */
	UFUNCTION(BlueprintCallable, Category = CharacterInteraction)
		void Interact();

	UFUNCTION(BlueprintCallable, Category = CharacterInteraction)
		void HoverOverObject();

	bool mInteractButtonIsPressed;

	void InteractButtonPressed();
	void InteractButtonRelesased();

	// Object hooverd over
	AInteractionTrigger* mTrigger;
	AInteractionTrigger* mHoldTrigger;

	FVector mTargetPos;

	/** Distance from edge where actor starts to look down */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Edge)
		float mEdgeThreshold;

	/** Size of gaps to ignore */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Edge)
		float mGapIgnoreSize;

	/** Maximum allowed slope angle */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Edge)
		float mEdgeMaxLedge;

	/** How far player should look over edge */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Edge)
		float mEdgeLeanAmount;

	/** How fast camera should pan down when walking towards edge */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Edge)
		float mLookDownSpeed;

	/** Called when moving */
	UFUNCTION(BlueprintImplementableEvent, Category = "fmod")
		void SoundEventMove();

	/** Called when beginning to move */
	UFUNCTION(BlueprintImplementableEvent, Category = "fmod")
		void SoundEventBeginMove();

	/** Called when movement stops */
	UFUNCTION(BlueprintImplementableEvent, Category = "fmod")
		void SoundEventEndMove();

	/** Returns move speed */
	UFUNCTION(BlueprintCallable, Category = "fmod")
		float GetMoveSpeed();

	/** Called when parameters are to be changed */
	UFUNCTION(BlueprintImplementableEvent, Category = "fmod")
		void SoundEventParameterChange();

	/** Call this to change parameters */
	UFUNCTION(BlueprintCallable, Category = "fmod")
		void ChangeParameter(FName parameterName, float parameterValue);

	/** Property holding which parameter to change */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters")
		FName mParameterChangeName;
	/** Property holding which parameter value to set */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters")
		float mParameterChangeValue;

	/** Windlevels for map */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WindLevels")
		TArray<float> mWindLevels;

	/** Call this to get current wind level */
	UFUNCTION(BlueprintCallable, Category = "WindLevels")
		float GetCurrentWindValue();

	UPROPERTY(EditAnywhere, Category = Character)
		int32 FallingTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character)
		bool DontMove;

	UFUNCTION(Exec, BlueprintCallable, Category = "Debug")
		void ToggleThirdPerson();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pause)
		bool mIsPaused;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
		TSubclassOf<class UUserWidget> PauseMenu;

	UUserWidget* mPauseWidget;
private: 
	
	bool FindGroundBelow(FVector offset);
	bool FindGroundAround(FVector offset);
	FVector mCamDefaultLocation;
	FVector mCamCurrentLocation;
	bool mLeaningOverEdge;
	
	float maxSpeed = 20;
	float currentSpeed = 0;
	bool mForward = false;
	bool mMoveForward = false;
	bool mRight = false;
	bool mStrafing = false;
	bool mMoving = false;

	int32 mFallingTime;
	APlayerController* mController;

	float mCurrentWindValue = 0;
	float mWindBaseValue = 0;
	float mSoundSpeedValue = 0;

	bool mThirdPerson = false;
};
