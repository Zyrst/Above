// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "PuzzzleSlab.generated.h"

UCLASS()
class ABOVE_API APuzzzleSlab : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APuzzzleSlab(const FObjectInitializer& ObjectInitializer);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	/** Root component with no other function */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Interaction)
		UBoxComponent* mRootComponent;

	/** Overlapping-trigger */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Trigger)
		UBoxComponent* mOverlapBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh)
		USkeletalMeshComponent* mSlab;

	UFUNCTION()
		void BeginOverlapOnBox(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION(BlueprintNativeEvent, Category = Overlap)
		void SteppedOnSlab();

	UFUNCTION(BlueprintCallable, Category = Effect)
		void LightUpSlab();

	UFUNCTION(BlueprintCallable, Category = Effect)
		void ResetSlab();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bool)
		bool mCorrectSlab;
};
