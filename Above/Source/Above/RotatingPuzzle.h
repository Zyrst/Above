// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "RotatingPuzzle.generated.h"

UCLASS()
class ABOVE_API ARotatingPuzzle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARotatingPuzzle();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION(BlueprintCallable, Category = Activation)
		void Activate(float target);

	void Reset();

	/**Get a random number which is not the current target*/
	UFUNCTION(BlueprintCallable, Category = RandomNum)
		float NotSameNumber();
	
	/**Array of points*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Points )
		TArray<float> mPoints;
	/**Last target*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Points)
		float mOldTarget;

	/** For getting reference to "indicator" material */
	UFUNCTION(BlueprintCallable, Category = Material)
		TArray<UTexture2D*> GetMaterialsReference();

	UFUNCTION(BlueprintCallable, Category = Material)
		UMaterialInstanceDynamic* GetMaterialReference();

	/** Populate this with materials corresponding to numbers */
	UPROPERTY(EditAnywhere, Category = Material)
		TArray<UTexture2D*> mIndicatorTextures;

	/** Texture when off */
	UPROPERTY(EditAnywhere, Category = Material)
		UTexture2D* mTextureInactive;

	/** How fast to blend textures */
	UPROPERTY(EditAnywhere, Category = Material)
		float mBlendSpeed;

	/** Set name of rotating parent here */
	UPROPERTY(EditAnywhere, Category = Properties)
		FString mRotationParentName;

	/** Set name of indicator parent here */
	UPROPERTY(EditAnywhere, Category = Properties)
		FString mIndicatorParentName;

private:
	bool mRotate;
	float mCalcTarget = 0;
	
	float mTarget = 0;
	float mBase;
	float mCurrent;
	int32 mRandom;

	UStaticMeshComponent* mDishMesh;
	UStaticMeshComponent* mIndicatorMesh;
	UMaterialInstanceDynamic* mIndicatorMeshMaterial;
	FVector* mStartPos;

	UTexture2D* mDesiredTexture;
	bool mFadeDown;
	bool mShouldFade;
	float mBlendFactor;
};
