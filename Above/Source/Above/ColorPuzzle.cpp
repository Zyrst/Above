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

	mMovementSpeed = 1.f;

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

	// Color initiation
	FLinearColor tmpColorRed = FLinearColor(255, 0, 0);
	FLinearColor tmpColorYellow = FLinearColor(255, 255, 0);
	FLinearColor tmpColorBlue = FLinearColor(0, 0, 255);
	FLinearColor tmpColorOrange = FLinearColor(255, 128, 0);
	FLinearColor tmpColorPurple = FLinearColor(255, 0, 255);
	FLinearColor tmpColorGreen = FLinearColor(0, 255, 0);

	mColorValueReference.Add(20, tmpColorRed);
	mColorValueReference.Add(400, tmpColorRed);
	mColorValueReference.Add(30, tmpColorYellow);
	mColorValueReference.Add(900, tmpColorYellow);
	mColorValueReference.Add(40, tmpColorBlue);
	mColorValueReference.Add(1600, tmpColorBlue);
	mColorValueReference.Add(600, tmpColorOrange);
	mColorValueReference.Add(800, tmpColorPurple);
	mColorValueReference.Add(1200, tmpColorGreen);

	// Initiate matrix
	mMatrixBoard.Init(mMatrixSizeX * mMatrixSizeY);

	// Board size
	mBoardSize = Int32Vector2(mMatrixSizeX - (mMatrixEdgeSizeX * 2), mMatrixSizeY - (mMatrixEdgeSizeY * 2));

	// Number center slots
	mBoardSlots = mBoardSize.x * mBoardSize.y;

	// Add index reference
	for (int32 x = 0; x < mMatrixSizeX; x++)
		for (int32 y = 0; y < mMatrixSizeY; y++)
			mIndexMap.Add(ConvertDoubleIndexToSingle(Int32Vector2(x, y), mMatrixSizeX), Int32Vector2(x, y));

	mNumberOfSlides = mBoardSize.x + mBoardSize.y;

	mSlideOffset.Init(mNumberOfSlides);

	// Initiate slide offset
	for (int32 i = 0; i <mNumberOfSlides; i++) {
		mSlideOffset[i] = 0;
	}

	// Fill matrix
	for (int i = 0; i < mMatrixBoard.Num(); i++) {
		mMatrixBoard[i] = Int32Vector3(20, 20, 0);

		/*
		if (mIndexMap.Find(i)->x >= 3 && mIndexMap.Find(i)->x <= 8 && mIndexMap.Find(i)->y >= 3 && mIndexMap.Find(i)->y <= 8) {
			mMatrixBoard[i] = Int32Vector3(20, 20, 0);
		}

		else {
			mMatrixBoard[i] = Int32Vector3(30, 30, 0);
		}
		*/
	}

	mMatrixBoard[ConvertDoubleIndexToSingle(Int32Vector2(3, 3), mMatrixSizeX)] = Int32Vector3(40, 40, 0);

	// Fill reference board
	mReferenceBoard.Init(mBoardSlots);
	for (int32 i = 0; i < mReferenceBoard.Num(); i++) {
		mReferenceBoard[i] = 1200;
	}

	// Initiate materials
	mMaterialMatrix.Init(mBoardSlots);

	moveBuffer = 0;

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

	mMaterialMatrix[ConvertDoubleIndexToSingle(Int32Vector2(1, 2), mBoardSize.x)] = mTableMesh->CreateAndSetMaterialInstanceDynamic(1);
	mMaterialMatrix[ConvertDoubleIndexToSingle(Int32Vector2(3, 2), mBoardSize.x)] = mTableMesh->CreateAndSetMaterialInstanceDynamic(2);
	mMaterialMatrix[ConvertDoubleIndexToSingle(Int32Vector2(1, 3), mBoardSize.x)] = mTableMesh->CreateAndSetMaterialInstanceDynamic(3);
	mMaterialMatrix[ConvertDoubleIndexToSingle(Int32Vector2(3, 3), mBoardSize.x)] = mTableMesh->CreateAndSetMaterialInstanceDynamic(4);
	mMaterialMatrix[ConvertDoubleIndexToSingle(Int32Vector2(0, 3), mBoardSize.x)] = mTableMesh->CreateAndSetMaterialInstanceDynamic(5);
	mMaterialMatrix[ConvertDoubleIndexToSingle(Int32Vector2(0, 2), mBoardSize.x)] = mTableMesh->CreateAndSetMaterialInstanceDynamic(6);
	mMaterialMatrix[ConvertDoubleIndexToSingle(Int32Vector2(2, 3), mBoardSize.x)] = mTableMesh->CreateAndSetMaterialInstanceDynamic(7);
	mMaterialMatrix[ConvertDoubleIndexToSingle(Int32Vector2(2, 2), mBoardSize.x)] = mTableMesh->CreateAndSetMaterialInstanceDynamic(8);
	mMaterialMatrix[ConvertDoubleIndexToSingle(Int32Vector2(5, 2), mBoardSize.x)] = mTableMesh->CreateAndSetMaterialInstanceDynamic(9);
	mMaterialMatrix[ConvertDoubleIndexToSingle(Int32Vector2(5, 3), mBoardSize.x)] = mTableMesh->CreateAndSetMaterialInstanceDynamic(10);
	mMaterialMatrix[ConvertDoubleIndexToSingle(Int32Vector2(4, 3), mBoardSize.x)] = mTableMesh->CreateAndSetMaterialInstanceDynamic(11);
	mMaterialMatrix[ConvertDoubleIndexToSingle(Int32Vector2(4, 2), mBoardSize.x)] = mTableMesh->CreateAndSetMaterialInstanceDynamic(12);
	mMaterialMatrix[ConvertDoubleIndexToSingle(Int32Vector2(0, 5), mBoardSize.x)] = mTableMesh->CreateAndSetMaterialInstanceDynamic(13);
	mMaterialMatrix[ConvertDoubleIndexToSingle(Int32Vector2(0, 4), mBoardSize.x)] = mTableMesh->CreateAndSetMaterialInstanceDynamic(14);
	mMaterialMatrix[ConvertDoubleIndexToSingle(Int32Vector2(1, 5), mBoardSize.x)] = mTableMesh->CreateAndSetMaterialInstanceDynamic(15);
	mMaterialMatrix[ConvertDoubleIndexToSingle(Int32Vector2(1, 4), mBoardSize.x)] = mTableMesh->CreateAndSetMaterialInstanceDynamic(16);
	mMaterialMatrix[ConvertDoubleIndexToSingle(Int32Vector2(2, 5), mBoardSize.x)] = mTableMesh->CreateAndSetMaterialInstanceDynamic(17);
	mMaterialMatrix[ConvertDoubleIndexToSingle(Int32Vector2(2, 4), mBoardSize.x)] = mTableMesh->CreateAndSetMaterialInstanceDynamic(18);
	mMaterialMatrix[ConvertDoubleIndexToSingle(Int32Vector2(5, 4), mBoardSize.x)] = mTableMesh->CreateAndSetMaterialInstanceDynamic(19);
	mMaterialMatrix[ConvertDoubleIndexToSingle(Int32Vector2(5, 5), mBoardSize.x)] = mTableMesh->CreateAndSetMaterialInstanceDynamic(20);
	mMaterialMatrix[ConvertDoubleIndexToSingle(Int32Vector2(3, 4), mBoardSize.x)] = mTableMesh->CreateAndSetMaterialInstanceDynamic(21);
	mMaterialMatrix[ConvertDoubleIndexToSingle(Int32Vector2(4, 5), mBoardSize.x)] = mTableMesh->CreateAndSetMaterialInstanceDynamic(22);
	mMaterialMatrix[ConvertDoubleIndexToSingle(Int32Vector2(4, 4), mBoardSize.x)] = mTableMesh->CreateAndSetMaterialInstanceDynamic(23);
	mMaterialMatrix[ConvertDoubleIndexToSingle(Int32Vector2(3, 5), mBoardSize.x)] = mTableMesh->CreateAndSetMaterialInstanceDynamic(24);
	mMaterialMatrix[ConvertDoubleIndexToSingle(Int32Vector2(0, 1), mBoardSize.x)] = mTableMesh->CreateAndSetMaterialInstanceDynamic(25);
	mMaterialMatrix[ConvertDoubleIndexToSingle(Int32Vector2(0, 0), mBoardSize.x)] = mTableMesh->CreateAndSetMaterialInstanceDynamic(26);
	mMaterialMatrix[ConvertDoubleIndexToSingle(Int32Vector2(2, 1), mBoardSize.x)] = mTableMesh->CreateAndSetMaterialInstanceDynamic(27);
	mMaterialMatrix[ConvertDoubleIndexToSingle(Int32Vector2(1, 1), mBoardSize.x)] = mTableMesh->CreateAndSetMaterialInstanceDynamic(28);
	mMaterialMatrix[ConvertDoubleIndexToSingle(Int32Vector2(3, 0), mBoardSize.x)] = mTableMesh->CreateAndSetMaterialInstanceDynamic(29);
	mMaterialMatrix[ConvertDoubleIndexToSingle(Int32Vector2(3, 1), mBoardSize.x)] = mTableMesh->CreateAndSetMaterialInstanceDynamic(30);
	mMaterialMatrix[ConvertDoubleIndexToSingle(Int32Vector2(2, 0), mBoardSize.x)] = mTableMesh->CreateAndSetMaterialInstanceDynamic(31);
	mMaterialMatrix[ConvertDoubleIndexToSingle(Int32Vector2(5, 0), mBoardSize.x)] = mTableMesh->CreateAndSetMaterialInstanceDynamic(32);
	mMaterialMatrix[ConvertDoubleIndexToSingle(Int32Vector2(5, 1), mBoardSize.x)] = mTableMesh->CreateAndSetMaterialInstanceDynamic(33);
	mMaterialMatrix[ConvertDoubleIndexToSingle(Int32Vector2(4, 1), mBoardSize.x)] = mTableMesh->CreateAndSetMaterialInstanceDynamic(34);
	mMaterialMatrix[ConvertDoubleIndexToSingle(Int32Vector2(4, 0), mBoardSize.x)] = mTableMesh->CreateAndSetMaterialInstanceDynamic(35);
	mMaterialMatrix[ConvertDoubleIndexToSingle(Int32Vector2(1, 0), mBoardSize.x)] = mTableMesh->CreateAndSetMaterialInstanceDynamic(36);

	multiplyColor();
}

// Called every frame
void AColorPuzzle::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	//GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Magenta, FString::Printf(TEXT("%f"), DeltaTime));

	for (int32 i = 0; i < mSlidePositionArray.Num(); i++) {
		if (mSlidePositionArray[i].x != mSlidePositionArray[i].z) {
			FVector delta;

			//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Magenta, FString::Printf(TEXT("Arse")));

			mSlidePositionArray[i].y.X += mMovementSpeed * DeltaTime;
			mSlidePositionArray[i].y.Y += mMovementSpeed * DeltaTime;
			mSlidePositionArray[i].y.Z += mMovementSpeed * DeltaTime;

			delta.X = FMath::Lerp(mSlidePositionArray[i].x.X, mSlidePositionArray[i].z.X, mMovementCurve->GetFloatValue(mSlidePositionArray[i].y.X));
			delta.Y = FMath::Lerp(mSlidePositionArray[i].x.Y, mSlidePositionArray[i].z.Y, mMovementCurve->GetFloatValue(mSlidePositionArray[i].y.Y));
			delta.Z = FMath::Lerp(mSlidePositionArray[i].x.Z, mSlidePositionArray[i].z.Z, mMovementCurve->GetFloatValue(mSlidePositionArray[i].y.Z));

			mSlideRootArray[i]->SetRelativeTransform(FTransform(mSlideRootArray[i]->GetRelativeTransform().Rotator(), delta, mSlideRootArray[i]->GetRelativeTransform().GetScale3D()));

			if (mSlidePositionArray[i].y.X >= 1.f) {
				mSlidePositionArray[i].x.X = mSlidePositionArray[i].z.X;
				mSlidePositionArray[i].y.X = 0;
			}

			if (mSlidePositionArray[i].y.Y >= 1.f) {
				mSlidePositionArray[i].x.Y = mSlidePositionArray[i].z.Y;
				mSlidePositionArray[i].y.Y = 0;
			}

			if (mSlidePositionArray[i].y.Z >= 1.f) {
				mSlidePositionArray[i].x.Z = mSlidePositionArray[i].z.Z;
				mSlidePositionArray[i].y.Z = 0;
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

UMaterialInterface* AColorPuzzle::GetMaterialPointer(Int32Vector2 index) {
	int32 realIndex = ConvertDoubleIndexToSingle(index, mBoardSize.x);

	if (realIndex >= 0 && realIndex < mMaterialMatrix.Num()) {
		return mMaterialMatrix[realIndex];
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

void AColorPuzzle::multiplyColor() {
	for (int32 x = 0; x < mMatrixSizeX; x++) {
		for (int32 y = 0; y < mMatrixSizeY; y++) {
			Int32Vector3* vector = GetMatrixValue(Int32Vector2(x, y));
			vector->z = vector->x * vector->y;
		}
	}

	for (int32 x = 0; x < mBoardSize.x; x++) {
		for (int32 y = 0; y < mBoardSize.y; y++) {
			mMaterialMatrix[ConvertDoubleIndexToSingle(Int32Vector2(x, y), mBoardSize.x)]->SetVectorParameterValue("Color",
				*mColorValueReference.Find(GetMatrixValue(Int32Vector2(x + mMatrixEdgeSizeX, y + mMatrixEdgeSizeY))->z));
		}
	}

	GEngine->ClearOnScreenDebugMessages();
	PrintMatrix(Int32Vector2(3, 0), Int32Vector2(3, 11));
}

void AColorPuzzle::CheckCombination() {
	if (ReferenceBoardMatrixIsSame()) {
		GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Magenta, FString::Printf(TEXT("Khaaaaaaaaaaaaaaaaaaaaaan!")));
	}
}

void AColorPuzzle::ActivateSlide(int32 slideNum, bool movePositiveDirection) {
	//GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Red, FString::Printf(TEXT("%d"), movePositiveDirection));

	if (slideNum >= 0 && slideNum <= 11) {
		if (mSlidePositionArray[slideNum].x == mSlidePositionArray[slideNum].z) {
			ShiftSlide(slideNum, movePositiveDirection);
		}
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
	int32 lowerIndexLimit = 0;
	int32 upperIndexLimit = 0;

	// Shift along x
	if (slideNum <= 5) {
		if (movePositiveDirection) {
			if (mSlideOffset[slideNum] < mMatrixEdgeSizeX) {
				mSlidePositionArray[slideNum].z -= FVector(2, 0, 0);
				mSlideOffset[slideNum]++;
				index.x = mMatrixSizeX - 1;
				indexAddition = Int32Vector2(-1, 0);
				lowerIndexLimit = 1;
				upperIndexLimit = 11;
			}
		}

		else {
			if (mSlideOffset[slideNum] > -mMatrixEdgeSizeX) {
				mSlidePositionArray[slideNum].z += FVector(2, 0, 0);
				mSlideOffset[slideNum]--;
				index.x = 0;
				indexAddition = Int32Vector2(1, 0);
				lowerIndexLimit = 0;
				upperIndexLimit = 10;
			}
		}

		while (index.x >= lowerIndexLimit && index.x <= upperIndexLimit) {
			GetMatrixValue(index)->x = GetMatrixValue(index + indexAddition)->x;
			index += indexAddition;
		}
	}

	// Shift along y
	else {
		if (movePositiveDirection) {
			if (mSlideOffset[slideNum] < mMatrixEdgeSizeY) {
				mSlidePositionArray[slideNum].z += FVector(0, 2, 0);
				mSlideOffset[slideNum]++;
				index.y = mMatrixSizeY - 1;
				indexAddition = Int32Vector2(0, -1);
				lowerIndexLimit = 1;
				upperIndexLimit = 11;
			}
		}

		else {
			if (mSlideOffset[slideNum] > -mMatrixEdgeSizeY) {
				mSlidePositionArray[slideNum].z -= FVector(0, 2, 0);
				mSlideOffset[slideNum]--;
				index.y = 0;
				indexAddition = Int32Vector2(0, 1);
				lowerIndexLimit = 0;
				upperIndexLimit = 10;
			}
		}

		while (index.y >= lowerIndexLimit && index.y <= upperIndexLimit) {
			GetMatrixValue(index)->y = GetMatrixValue(index + indexAddition)->y;
			index += indexAddition;
		}
	}

	multiplyColor();
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