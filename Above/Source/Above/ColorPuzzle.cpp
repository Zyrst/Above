// Fill out your copyright notice in the Description page of Project Settings.

#include "Above.h"
#include "ColorPuzzle.h"


// Sets default values
AColorPuzzle::AColorPuzzle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mMatrixSizeX = 12;
	mMatrixSizeY = 12;
	mMatrixEdgeSizeX = 3;
	mMatrixEdgeSizeY = 3;

	mMatrixBoard.Init(mMatrixSizeX * mMatrixSizeY);

	// Add index reference
	for (int32 i = 0; i < mMatrixSizeX; i++)
		for (int32 j = 0; j < mMatrixSizeY; j++)
			mIndexMap.Add(ConvertDoubleIndexToSingle(Int32Vector2(i, j)), Int32Vector2(i, j));

	// Fill matrix
	for (int i = 0; i < mMatrixBoard.Num(); i++) {
		if (mIndexMap.Find(i)->x >= 3 && mIndexMap.Find(i)->x <= 8 && mIndexMap.Find(i)->y >= 3 && mIndexMap.Find(i)->y <= 8) {
			mMatrixBoard[i] = Int32Vector3(2, 2, 0);
		}

		else {
			mMatrixBoard[i] = Int32Vector3(1, 1, 0);
		}

		multiplyColor(&mMatrixBoard[i]);
	}

	moveBuffer = 0;

	// Color initiation
	FColor tmpColorRed = FColor(255, 0, 0);
	FColor tmpColorYellow = FColor(255, 255, 0);
	FColor tmpColorBlue = FColor(0, 0, 255);
	FColor tmpColorOrange = FColor(255, 128, 0);
	FColor tmpColorPurple = FColor(255, 0, 255);
	FColor tmpColorGreen = FColor(0, 255, 0);

	mColorValueReference.Add(20, &tmpColorRed);
	mColorValueReference.Add(400, &tmpColorRed);

	mColorValueReference.Add(30, &tmpColorYellow);
	mColorValueReference.Add(900, &tmpColorYellow);

	mColorValueReference.Add(40, &tmpColorBlue);
	mColorValueReference.Add(1600, &tmpColorBlue);

	mColorValueReference.Add(600, &tmpColorOrange);

	mColorValueReference.Add(800, &tmpColorPurple);

	mColorValueReference.Add(1200, &tmpColorGreen);
}

// Called when the game starts or when spawned
void AColorPuzzle::BeginPlay()
{
	Super::BeginPlay();

	Activate(0, false);
	Activate(0, false);
	Activate(0, false);
	Activate(0, false);

	PrintMatrix(Int32Vector2(0, 8), Int32Vector2(11, 8));

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("%d, %d, %d"), GetMatrixValue(ConvertSlideNumberToIndex(0))->x, GetMatrixValue(ConvertSlideNumberToIndex(0))->y, GetMatrixValue(ConvertSlideNumberToIndex(0))->z));
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("%d, %d, %d"), GetMatrixValue(0)->x, GetMatrixValue(0)->y, GetMatrixValue(0)->z));
}

// Called every frame
void AColorPuzzle::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	
}

Int32Vector3* AColorPuzzle::GetMatrixValue(Int32Vector2 index) {
	int32 realIndex = ConvertDoubleIndexToSingle(index);

	if (realIndex > 0 && realIndex < mMatrixBoard.Num()) {
		return &mMatrixBoard[realIndex];
	}

	else {
		return nullptr;
	}
}

void AColorPuzzle::Int32Flip(int32* x, int32* y) {
	moveBuffer = *x;
	*x = *y;
	*x = moveBuffer;
}

void AColorPuzzle::multiplyColor(Int32Vector3* vector) {
	vector->z = vector->x * vector->y;
	// Todo update visuals
}

void AColorPuzzle::Activate(int32 slideNum, bool movePositiveDirection) {
	if (slideNum >= 0 && slideNum <= 11) {
		ShiftSlide(slideNum, movePositiveDirection);
	}
}

Int32Vector2 AColorPuzzle::ConvertSlideNumberToIndex(int32 number) {
	Int32Vector2 firstInSlide;

	if (number <= 5) {
		firstInSlide.x = 0;
		firstInSlide.y = mMatrixSizeY - 1 - mMatrixEdgeSizeY - number;
	}

	else {
		firstInSlide.x = number - mMatrixEdgeSizeX;
		firstInSlide.y = 0;
	}

	return firstInSlide;
}

int32 AColorPuzzle::ConvertDoubleIndexToSingle(Int32Vector2 index) {
	return index.x + (mMatrixSizeX * index.y);
}

void AColorPuzzle::ShiftSlide(int32 slideNum, bool movePositiveDirection) {
	// Second index in slide
	Int32Vector2 index = ConvertSlideNumberToIndex(slideNum);

	// Index adjustment
	Int32Vector2 indexAddition;

	// Upper and lower bounds including maximum allowed number
	int32 lowerIndexLimit;
	int32 upperIndexLimit;

	// Shift along x
	if (slideNum <= 5) {
		if (movePositiveDirection) {
			index.x = mMatrixSizeX - 1;
			indexAddition = Int32Vector2(-1, 0);
			lowerIndexLimit = 1;
			upperIndexLimit = 11;
		}

		else {
			index.x = 0;
			indexAddition = Int32Vector2(1, 0);
			lowerIndexLimit = 0;
			upperIndexLimit = 10;
		}

		while (index.x >= lowerIndexLimit && index.x <= upperIndexLimit) {
			GetMatrixValue(index)->x = GetMatrixValue(index + indexAddition)->x;
			multiplyColor(GetMatrixValue(index + indexAddition));
			index += indexAddition;
		}
	}

	// Shift along y
	else {
		if (movePositiveDirection) {
			index.y = mMatrixSizeY - 1;
			indexAddition = Int32Vector2(0, -1);
			lowerIndexLimit = 1;
			upperIndexLimit = 11;
		}

		else {
			index.y = 0;
			indexAddition = Int32Vector2(0, 1);
			lowerIndexLimit = 0;
			upperIndexLimit = 10;
		}

		while (index.y >= lowerIndexLimit && index.y <= upperIndexLimit) {
			GetMatrixValue(index)->y = GetMatrixValue(index + indexAddition)->y;
			multiplyColor(GetMatrixValue(index));
			index += indexAddition;
		}
	}
}

void AColorPuzzle::PrintMatrix(Int32Vector2 lowerBound, Int32Vector2 upperBound) {
	for (int32 x = lowerBound.x; x <= upperBound.x; x++) {
		for (int32 y = lowerBound.y; y <= upperBound.y; y++) {
			GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Magenta, FString::Printf(TEXT("%d, %d: %d, %d, %d"), x, y, mMatrixBoard[ConvertDoubleIndexToSingle(Int32Vector2(x, y))].x, mMatrixBoard[ConvertDoubleIndexToSingle(Int32Vector2(x, y))].y, mMatrixBoard[ConvertDoubleIndexToSingle(Int32Vector2(x, y))].z));
		}
	}
}