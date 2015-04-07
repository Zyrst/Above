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

	/** Called on hit by line trace*/
	UFUNCTION(BlueprintNativeEvent, Category = Interaction)
		void Interact();

	UFUNCTION(BlueprintCallable, Category = Interaction)
		void StartHover();

	UFUNCTION(BlueprintCallable, Category = Interaction)
		void EndHover();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Interaction)
		UTextRenderComponent* mHoverText;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Interaction)
		FString mHoverTextDefaultValue;

	UBoxComponent* mRootComponent;
};
