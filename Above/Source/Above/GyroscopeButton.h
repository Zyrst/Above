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

	/** Whether to control rotation for each gyroscope part, or to activate rotation on gyroscope */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Defaults)
		bool RotationActivation = false;

	/** Activate when pressing or stepping? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RotationActivation, meta = (EditCondition = "RotationActivation"))
		bool ActivateWhenSteppedOn = false;

	/** How many rotation modes on button */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Defaults, meta = (EditCondition = "!RotationActivation"))
		int32 NumberOfModes = 12;


	/** Called when pressing button */
	UFUNCTION(BlueprintCallable, Category = Puzzle)
		void Activate();

	/** Event called when button is activated */
	UFUNCTION(BlueprintImplementableEvent, Category = Puzzle)
		void OnActivate();



	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Trigger)
		UBoxComponent* mOverlapBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Trigger)
		UChildActorComponent* mInteractionTrigger;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Trigger)
		UStaticMeshComponent* mStepMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Trigger)
		UStaticMeshComponent* mPressMesh;


private:
	int32 mCurrentMode = 0;

	USceneComponent* mRootComponent;
};
