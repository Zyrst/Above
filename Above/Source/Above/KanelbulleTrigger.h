// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "KanelbulleTrigger.generated.h"

UCLASS()
class ABOVE_API AKanelbulleTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKanelbulleTrigger();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	/** Called from BP */
	UFUNCTION(BlueprintCallable, Category = puzzle)
		void Activate();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = texture)
		TArray<UTexture*> mTextures;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = texture)
		TArray<UTexture*> mEmissiveTextures;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = texture)
		float mAnimationSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = texture)
		UCurveFloat* mAnimationCurve;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = texture)
		UMaterialInstanceDynamic* mMaterial;

private:
	bool mShouldAnimate = false;
	float mAnimateTracker = 0;
	
};
