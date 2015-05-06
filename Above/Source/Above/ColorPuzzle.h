// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "Int32Vector3.h"

#include "Int32Vector2.h"
#include "Int32Vector3.h"
#include "GameFramework/Actor.h"
#include "ColorPuzzle.generated.h"

UCLASS()
class ABOVE_API AColorPuzzle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AColorPuzzle();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	/** Returns pointer to value from xy coordinates */
	Int32Vector3* GetMatrixValue(Int32Vector2 index);

	int32 mMatrixSizeX;
	int32 mMatrixSizeY;

	TArray<Int32Vector3> mMatrixBoard;

	int32 moveBuffer;

	void Int32Flip(int32* x, int32* y);

	void multiplyColor(Int32Vector3* vector);
	
	TMap<int32, FColor*> mColorValueReference;

	void Activate(int32 slideNum, bool movePositiveDirection);

	Int32Vector2 ConvertSlideNumberToIndex(int32 number);

	void ShiftSlide(int32 slideNum, Int32Vector2 index, bool movePositiveDirection);

	TMap<int32, Int32Vector2> mIndexMap;

	int32 ConvertDoubleIndexToSingle(Int32Vector2 index);
};