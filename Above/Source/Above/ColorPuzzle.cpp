// Fill out your copyright notice in the Description page of Project Settings.

#include "Above.h"
#include "ColorPuzzle.h"


// Sets default values
AColorPuzzle::AColorPuzzle(const FObjectInitializer& ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Initiate constants
	mMatrixSizeX = 12;
	mMatrixSizeY = 12;
	mMatrixEdgeSizeX = 3;
	mMatrixEdgeSizeY = 3;

	mRoot = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("Root"));
	mRoot->SetMobility(EComponentMobility::Static);
	RootComponent = mRoot;

	mSlide0 = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("Slide 0"));
	mSlide0->AttachParent = mRoot;
	mSlide1 = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("Slide 1"));
	mSlide1->AttachParent = mRoot;
	mSlide2 = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("Slide 2"));
	mSlide2->AttachParent = mRoot;
	mSlide3 = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("Slide 3"));
	mSlide3->AttachParent = mRoot;
	mSlide4 = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("Slide 4"));
	mSlide4->AttachParent = mRoot;
	mSlide5 = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("Slide 5"));
	mSlide5->AttachParent = mRoot;
	mSlide6 = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("Slide 6"));
	mSlide6->AttachParent = mRoot;
	mSlide7 = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("Slide 7"));
	mSlide7->AttachParent = mRoot;
	mSlide8 = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("Slide 8"));
	mSlide8->AttachParent = mRoot;
	mSlide9 = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("Slide 9"));
	mSlide9->AttachParent = mRoot;
	mSlide10 = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("Slide 10"));
	mSlide10->AttachParent = mRoot;
	mSlide11 = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("Slide 11"));
	mSlide11->AttachParent = mRoot;
	
	mSlideRootArray.Add(mSlide0);
	mSlideRootArray.Add(mSlide1);
	mSlideRootArray.Add(mSlide2);
	mSlideRootArray.Add(mSlide3);
	mSlideRootArray.Add(mSlide4);
	mSlideRootArray.Add(mSlide5);
	mSlideRootArray.Add(mSlide6);
	mSlideRootArray.Add(mSlide7);
	mSlideRootArray.Add(mSlide8);
	mSlideRootArray.Add(mSlide9);
	mSlideRootArray.Add(mSlide10);
	mSlideRootArray.Add(mSlide11);

	// Initiate matrix
	mMatrixBoard.Init(mMatrixSizeX * mMatrixSizeY);

	// Board size
	mBoardSize = Int32Vector2(mMatrixSizeX - (mMatrixEdgeSizeX * 2), mMatrixSizeY - (mMatrixEdgeSizeY * 2));

	// Number center slots
	mBoardSlots = mBoardSize.x * mBoardSize.y;

	mReferenceBoard.Init(mBoardSlots);

	// Add index reference
	for (int32 i = 0; i < mMatrixSizeX; i++)
		for (int32 j = 0; j < mMatrixSizeY; j++)
			mIndexMap.Add(ConvertDoubleIndexToSingle(Int32Vector2(i, j), mMatrixSizeX), Int32Vector2(i, j));

	mNumberOfSlides = mBoardSize.x + mBoardSize.y;

	mSlideOffset.Init(mNumberOfSlides);

	// Initiate slide offset
	for (int32 i = 0; i <mNumberOfSlides; i++) {
		mSlideOffset[i] = 0;
	}

	// Fill matrix
	for (int i = 0; i < mMatrixBoard.Num(); i++) {
		if (mIndexMap.Find(i)->x >= 3 && mIndexMap.Find(i)->x <= 8 && mIndexMap.Find(i)->y >= 3 && mIndexMap.Find(i)->y <= 8) {
			mMatrixBoard[i] = Int32Vector3(30, 40, 0);
		}

		else {
			mMatrixBoard[i] = Int32Vector3(20, 30, 0);
		}

		multiplyColor(&mMatrixBoard[i]);
	}

	// Fill reference board
	for (int32 i = 0; i < mReferenceBoard.Num(); i++) {
		mReferenceBoard[i] = 1200;
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

	// Initiate slide movement array
	mSlidePositionArray.Init(mNumberOfSlides);
	for (int32 i = 0; i < mSlidePositionArray.Num(); i++) {
		mSlidePositionArray[i] = TriFVector(FVector(0, 0, 0), FVector(0, 0, 0), FVector(0, 0, 0));
	}
}

// Called when the game starts or when spawned
void AColorPuzzle::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AColorPuzzle::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	for (int32 i = 0; i < mSlidePositionArray.Num(); i++) {
		if (mSlidePositionArray[i].x != mSlidePositionArray[i].z) {
			FVector delta = FMath::Lerp(mSlidePositionArray[i].x, mSlidePositionArray[i].z, mMovementCurve->GetFloatValue(5));



			if (mSlidePositionArray[i].y == mSlidePositionArray[i].z) {
				mSlidePositionArray[i].x = mSlidePositionArray[i].z;
			}
		}
	}
}

Int32Vector3* AColorPuzzle::GetMatrixValue(Int32Vector2 index) {
	int32 realIndex = ConvertDoubleIndexToSingle(index, mMatrixSizeX);

	if (realIndex >= 0 && realIndex < mMatrixBoard.Num()) {
		return &mMatrixBoard[realIndex];
	}

	else {
		return nullptr;
	}
}

int32* AColorPuzzle::GetReferenceBoardValue(Int32Vector2 index) {
	int32 realIndex = ConvertDoubleIndexToSingle(index, mBoardSize.x);

	if (realIndex >= 0 && realIndex < mReferenceBoard.Num()) {
		return &mReferenceBoard[realIndex];
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

void AColorPuzzle::CheckCombination() {
	if (ReferenceBoardMatrixIsSame()) {
		GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Magenta, FString::Printf(TEXT("Khaaaaaaaaaaaaaaaaaaaaaan!")));
	}
}

void AColorPuzzle::ActivateSlide(int32 slideNum, bool movePositiveDirection) {
	GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Magenta, FString::Printf(TEXT("Poooooooop!")));

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

int32 AColorPuzzle::ConvertDoubleIndexToSingle(Int32Vector2 index, int32 matrixSizeX) {
	return index.x + (matrixSizeX * index.y);
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
		if (mSlideOffset[slideNum] < 3 && mSlideOffset[slideNum] > -3) {
			if (movePositiveDirection) {
				mSlideOffset[slideNum]++;

				index.x = mMatrixSizeX - 1;
				indexAddition = Int32Vector2(-1, 0);
				lowerIndexLimit = 1;
				upperIndexLimit = 11;
			}

			else {
				mSlideOffset[slideNum]--;
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
	}

	// Shift along y
	else {
		if (mSlideOffset[slideNum] < 3 && mSlideOffset[slideNum] > -3) {
			if (movePositiveDirection) {
				mSlideOffset[slideNum]++;
				index.y = mMatrixSizeY - 1;
				indexAddition = Int32Vector2(0, -1);
				lowerIndexLimit = 1;
				upperIndexLimit = 11;
			}

			else {
				mSlideOffset[slideNum]--;
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
}

void AColorPuzzle::PrintMatrix(Int32Vector2 lowerBound, Int32Vector2 upperBound) {
	for (int32 x = lowerBound.x; x <= upperBound.x; x++) {
		for (int32 y = lowerBound.y; y <= upperBound.y; y++) {
			GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Magenta, FString::Printf(TEXT("%d, %d: %d, %d, %d"), x, y, mMatrixBoard[ConvertDoubleIndexToSingle(Int32Vector2(x, y), mMatrixSizeX)].x, mMatrixBoard[ConvertDoubleIndexToSingle(Int32Vector2(x, y), mMatrixSizeX)].y, mMatrixBoard[ConvertDoubleIndexToSingle(Int32Vector2(x, y), mMatrixSizeX)].z));
		}
	}
}

bool AColorPuzzle::ReferenceBoardMatrixIsSame() {
	bool isSame = true;

	for (int32 x = 0; x < mBoardSize.x; x++) {
		for (int32 y = 0; y < mBoardSize.y; y++) {
			Int32Vector3* matrix = GetMatrixValue(Int32Vector2(x + mMatrixEdgeSizeX, y + mMatrixEdgeSizeY));
			int32* referenceBoard = GetReferenceBoardValue(Int32Vector2(x, y));

			if (matrix != nullptr && referenceBoard != nullptr) {
				if (matrix->z != *referenceBoard) {
					isSame = false;
				}
			}
		}
	}

	return isSame;
}