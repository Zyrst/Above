// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "Int32Vector3.h"

#include "Int32Vector2.h"
#include "Int32Vector3.h"
#include "GameFramework/Actor.h"
#include "TriFVector.h"
#include "ColorPuzzle.generated.h"

UCLASS()
class ABOVE_API AColorPuzzle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AColorPuzzle(const FObjectInitializer& ObjectInitializer);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	int32 mMatrixSizeX;
	int32 mMatrixSizeY;
	int32 mMatrixEdgeSizeX;
	int32 mMatrixEdgeSizeY;

	Int32Vector2 mBoardSize;
	int32 mBoardSlots;
	int32 mNumberOfSlides;

	int32 moveBuffer;

	float mMovementSpeed;

	USceneComponent* mRoot;

	USphereComponent* mSlide0;
	USphereComponent* mSlide1;
	USphereComponent* mSlide2;
	USphereComponent* mSlide3;
	USphereComponent* mSlide4;
	USphereComponent* mSlide5;
	USphereComponent* mSlide6;
	USphereComponent* mSlide7;
	USphereComponent* mSlide8;
	USphereComponent* mSlide9;
	USphereComponent* mSlide10;
	USphereComponent* mSlide11;

	/** Movement curve */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
		UCurveFloat* mMovementCurve;

	TArray<USphereComponent*> mSlideRootArray;

	TArray<Int32Vector3> mMatrixBoard;
	TMap<int32, Int32Vector2> mIndexMap;
	TArray<int32> mSlideOffset;
	TMap<int32, FColor*> mColorValueReference;
	TArray<int32> mReferenceBoard;
	TArray<TriFVector> mSlidePositionArray;
	TArray<UMaterialInstanceDynamic*> mDynamicMaterialArray;

	int32 ConvertDoubleIndexToSingle(Int32Vector2 index, int32 matrixSizeX);

	/** Returns pointer to value from xy coordinates */
	Int32Vector3* GetMatrixValue(Int32Vector2 index);

	int32* GetReferenceBoardValue(Int32Vector2 index);

	UMaterialInstanceDynamic* GetMaterialPointer(Int32Vector2 index);

	/** Return second index in slide */
	Int32Vector2 ConvertSlideNumberToIndex(int32 number);

	void Int32Flip(int32* x, int32* y);

	void multiplyColor(Int32Vector3* vector);

	UFUNCTION(BlueprintCallable, Category = Interaction)
		void CheckCombination();

	UFUNCTION(BlueprintCallable, Category = Interaction)
		void ActivateSlide(int32 slideNum, bool movePositiveDirection);

	void ShiftSlide(int32 slideNum, bool movePositiveDirection);

	/** Prints specified part of matrix */
	void PrintMatrix(Int32Vector2 lowerBound, Int32Vector2 upperBound);

	bool ReferenceBoardMatrixIsSame();
};