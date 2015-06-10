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
	virtual void Tick(float DeltaSeconds) override;

	/** Table mesh */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
		UStaticMeshComponent* mTableMesh;

	/** Movement curve */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
		UCurveFloat* mMovementCurve;

	/** Color curve */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
		UCurveFloat* mColorCurve;

	/** Color curve */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
		float mBlendSpeed = 0.5f;

	/** When slide starts to move */
	UFUNCTION(BlueprintImplementableEvent, Category = Animation)
		void StartMoveSlide();

	/** When puzzle is done  */
	UFUNCTION(BlueprintImplementableEvent, Category = Event)
		void PuzzleDone();

	/** Set matrix values from blueprints */
	UFUNCTION(BlueprintCallable, Category = Matrix)
		void SetMatrixValue(int32 indexX, int32 indexY, int32 x, int32 y);

	// Get correct value in slot
	int32* GetReferenceBoardValue(Int32Vector2 index);

	/** Set correct value from blueprints */
	UFUNCTION(BlueprintCallable, Category = Matrix)
		void SetReferenceBoardValue(int32 indexX, int32 indexY, int32 value);

	/** Chec if solved */
	UFUNCTION(BlueprintCallable, Category = Interaction)
		void CheckCombination();

	/** Move slide */
	UFUNCTION(BlueprintCallable, Category = Interaction)
		void ActivateSlide(int32 slideNum, bool movePositiveDirection);

private:
	// Variables
	Int32Vector2 mMatrixSize;
	Int32Vector2 mMatrixEdgeSize;
	Int32Vector2 mMaxSlideOffset;

	Int32Vector2 mBoardSize;
	int32 mBoardSlots;
	int32 mNumberOfSlides;

	float mMovementSpeed;

	// Root
	USceneComponent* mRoot;

	//Roots for moving slides
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

	// Slide root array
	TArray<USphereComponent*> mSlideRootArray;

	// Matrix containing current values
	TArray<Int32Vector3> mMatrixBoard;

	// Get 2d index from 1d
	TMap<int32, Int32Vector2> mIndexMap;

	// Current offset on slides
	TArray<int32> mSlideOffset;

	// Stores color values
	TMap<int32, FLinearColor> mColorValueReference;

	// Contains correct sulution
	TArray<int32> mReferenceBoard;

	// Current slide possitions
	TArray<TriFVector> mSlidePositionArray;

	// Instanced materials array
	TArray<UMaterialInstanceDynamic*> mMaterialMatrix;

	// Get 1d index from 2d
	int32 ConvertDoubleIndexToSingle(Int32Vector2 index, int32 matrixSizeX);

	// Returns pointer to value from xy coordinates
	Int32Vector3* GetMatrixValue(Int32Vector2 index);

	// Return second index in slide
	Int32Vector2 ConvertSlideNumberToIndex(int32 number);

	// Update colors
	void multiplyColor();

	// Shift values in matrix
	void ShiftSlide(int32 slideNum, bool movePositiveDirection);

	// Prints specified part of matrix
	void PrintMatrix(Int32Vector2 lowerBound, Int32Vector2 upperBound);

	// Compare correct solution to current
	bool ReferenceBoardMatrixIsSame();

	// Lerp variables
	bool mLerp = true;
	float mLerpTime = 0;
};