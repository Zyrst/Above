// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <string>
#include "GameFramework/Actor.h"
#include "InteractionTrigger.generated.h"

UCLASS()
class ABOVE_API AInteractionTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractionTrigger(const FObjectInitializer& ObjectInitializer);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	/** Called if both hit by line trace and mb1 is clicked */
	UFUNCTION(BlueprintNativeEvent, Category = Interaction)
		void Interact();

	UFUNCTION(BlueprintCallable, Category = Interaction)
		void SetPointerTarget(UPARAM(ref) FVector& vectorPointer);

	UFUNCTION(BlueprintCallable, Category = Interaction)
		FVector& GetPointerTarget();

	/** Called on hit by line trace */
	UFUNCTION(BlueprintCallable, Category = Interaction)
		void StartHover();

	/** Called when no longer hit by line trace */
	UFUNCTION(BlueprintCallable, Category = Interaction)
		void EndHover();

	/** Called when button is no longer held */
	UFUNCTION(BlueprintNativeEvent, Category = Interaction)
		void EndHold();

	/** Textcomponent */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Interaction)
		UTextRenderComponent* mHoverText;

	/** Text value set in constructor */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Interaction)
		FString mHoverTextDefaultValue;

	/** Root component with no other function */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Interaction)
		UBoxComponent* mRootComponent;

	FVector* mPointerTarget;
};
