// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "GyroscopeButton.generated.h"

UCLASS()
class ABOVE_API AGyroscopeButton : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AGyroscopeButton(const FObjectInitializer& ObjectInitializer);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	virtual void OnConstruction(const FTransform& Transform) override;

	/** Is it this button which initiates rotation? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RotationActivation)
		bool InitiatesRotation = false;

	/** Activate when pressing or stepping? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RotationActivation)
		bool ActivateWhenSteppedOn = false;

	/** How many rotation modes on button */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Defaults)
		int32 NumberOfModes = 12;

	/** Which button is it? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Defaults)
		int32 ButtonIndex = 1;


	/** Called when pressing button */
	UFUNCTION(BlueprintCallable, Category = Puzzle)
		void Activate();

	/** Event called when button is activated */
	UFUNCTION(BlueprintImplementableEvent, Category = Puzzle)
		void OnActivate();

	/** Event called when button is activated for rotation */
	UFUNCTION(BlueprintImplementableEvent, Category = Puzzle)
		void OnInitiateRotationActivate();


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Trigger)
		UBoxComponent* mOverlapBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Trigger)
		UChildActorComponent* mInteractionTrigger;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Trigger)
		UStaticMeshComponent* mStepMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Trigger)
		UStaticMeshComponent* mPressMesh;

	UFUNCTION()
		void BeginOverlapOnBox(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable, Category = Misc)
		int32 GetCurrentMode();


	UFUNCTION(BlueprintImplementableEvent, Category = "fmod")
		void SoundEventModeChange(int32 buttonNumber, int32 mode, bool activatesRotation);

private:
	int32 mCurrentMode = 0;

	USceneComponent* mRootComponent;
	FVector mInteractionTriggerPosition;
	FVector mOverlapBoxPosition;
};
