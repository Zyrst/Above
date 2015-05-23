// Fill out your copyright notice in the Description page of Project Settings.

#include "Above.h"
#include "ColorPuzzle.h"
#include "AboveGameMode.h"


// Sets default values
AColorPuzzle::AColorPuzzle(const FObjectInitializer& ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Initiate constants
	mMatrixSize = Int32Vector2(18, 18);
	mMatrixEdgeSize = Int32Vector2(6, 6);
	mMaxSlideOffset = Int32Vector2(2, 2);

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
	FLinearColor tmpColorRed = FLinearColor(1, 0, 0);
	FLinearColor tmpColorYellow = FLinearColor(1, 1, 0);
	FLinearColor tmpColorBlue = FLinearColor(0, 0, 1);
	FLinearColor tmpColorOrange = FLinearColor(1, 0.1, 0);
	FLinearColor tmpColorPurple = FLinearColor(1, 0, 1);
	FLinearColor tmpColorGreen = FLinearColor(0, 1, 0);

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
	mMatrixBoard.Init(mMatrixSize.x * mMatrixSize.y);

	// Board size
	mBoardSize = Int32Vector2(mMatrixSize.x - (mMatrixEdgeSize.x * 2), mMatrixSize.y - (mMatrixEdgeSize.y * 2));

	// Number center slots
	mBoardSlots = mBoardSize.x * mBoardSize.y;

	// Add index reference
	for (int32 x = 0; x < mMatrixSize.x; x++)
		for (int32 y = 0; y < mMatrixSize.y; y++)
			mIndexMap.Add(ConvertDoubleIndexToSingle(Int32Vector2(x, y), mMatrixSize.x), Int32Vector2(x, y));

	mNumberOfSlides = mBoardSize.x + mBoardSize.y;

	mSlideOffset.Init(mNumberOfSlides);

	// Initiate slide offset
	for (int32 i = 0; i <mNumberOfSlides; i++) {
		mSlideOffset[i] = 0;
	}

	// Fill matrix
	//RÖD
	*GetMatrixValue(Int32Vector2(6, 14)) = Int32Vector3(20, 20, 0);
	*GetMatrixValue(Int32Vector2(7, 14)) = Int32Vector3(40, 40, 0);
	*GetMatrixValue(Int32Vector2(8, 14)) = Int32Vector3(20, 20, 0);
	*GetMatrixValue(Int32Vector2(9, 14)) = Int32Vector3(20, 20, 0);
	*GetMatrixValue(Int32Vector2(10, 14)) = Int32Vector3(30, 30, 0);
	*GetMatrixValue(Int32Vector2(11, 14)) = Int32Vector3(40, 40, 0);

	*GetMatrixValue(Int32Vector2(6, 13)) = Int32Vector3(30, 30, 0);
	*GetMatrixValue(Int32Vector2(7, 13)) = Int32Vector3(20, 20, 0);
	*GetMatrixValue(Int32Vector2(8, 13)) = Int32Vector3(20, 20, 0);
	*GetMatrixValue(Int32Vector2(9, 13)) = Int32Vector3(30, 30, 0);
	*GetMatrixValue(Int32Vector2(10, 13)) = Int32Vector3(30, 30, 0);
	*GetMatrixValue(Int32Vector2(11, 13)) = Int32Vector3(20, 20, 0);

	*GetMatrixValue(Int32Vector2(6, 12)) = Int32Vector3(40, 40, 0);
	*GetMatrixValue(Int32Vector2(7, 12)) = Int32Vector3(40, 40, 0);
	*GetMatrixValue(Int32Vector2(8, 12)) = Int32Vector3(40, 40, 0);
	*GetMatrixValue(Int32Vector2(9, 12)) = Int32Vector3(40, 40, 0);
	*GetMatrixValue(Int32Vector2(10, 12)) = Int32Vector3(20, 20, 0);
	*GetMatrixValue(Int32Vector2(11, 12)) = Int32Vector3(20, 20, 0);

	*GetMatrixValue(Int32Vector2(3, 11)) = Int32Vector3(40, 40, 0);
	*GetMatrixValue(Int32Vector2(4, 11)) = Int32Vector3(30, 30, 0);
	*GetMatrixValue(Int32Vector2(5, 11)) = Int32Vector3(30, 30, 0);
	*GetMatrixValue(Int32Vector2(6, 11)) = Int32Vector3(20, 20, 0);
	*GetMatrixValue(Int32Vector2(7, 11)) = Int32Vector3(30, 30, 0);
	*GetMatrixValue(Int32Vector2(8, 11)) = Int32Vector3(20, 30, 0);
	*GetMatrixValue(Int32Vector2(9, 11)) = Int32Vector3(40, 20, 0);
	*GetMatrixValue(Int32Vector2(10, 11)) = Int32Vector3(30, 20, 0);
	*GetMatrixValue(Int32Vector2(11, 11)) = Int32Vector3(30, 40, 0);
	*GetMatrixValue(Int32Vector2(12, 11)) = Int32Vector3(30, 30, 0);
	*GetMatrixValue(Int32Vector2(13, 11)) = Int32Vector3(40, 40, 0);
	*GetMatrixValue(Int32Vector2(14, 11)) = Int32Vector3(30, 30, 0);

	*GetMatrixValue(Int32Vector2(3, 10)) = Int32Vector3(20, 20, 0);
	*GetMatrixValue(Int32Vector2(4, 10)) = Int32Vector3(20, 20, 0);
	*GetMatrixValue(Int32Vector2(5, 10)) = Int32Vector3(40, 40, 0);
	*GetMatrixValue(Int32Vector2(6, 10)) = Int32Vector3(20, 40, 0);
	*GetMatrixValue(Int32Vector2(7, 10)) = Int32Vector3(40, 30, 0);
	*GetMatrixValue(Int32Vector2(8, 10)) = Int32Vector3(30, 20, 0);
	*GetMatrixValue(Int32Vector2(9, 10)) = Int32Vector3(20, 20, 0);
	*GetMatrixValue(Int32Vector2(10, 10)) = Int32Vector3(30, 20, 0);
	*GetMatrixValue(Int32Vector2(11, 10)) = Int32Vector3(30, 20, 0);
	*GetMatrixValue(Int32Vector2(12, 10)) = Int32Vector3(40, 40, 0);
	*GetMatrixValue(Int32Vector2(13, 10)) = Int32Vector3(20, 20, 0);
	*GetMatrixValue(Int32Vector2(14, 10)) = Int32Vector3(40, 40, 0);

	*GetMatrixValue(Int32Vector2(3, 9)) = Int32Vector3(40, 40, 0);
	*GetMatrixValue(Int32Vector2(4, 9)) = Int32Vector3(30, 30, 0);
	*GetMatrixValue(Int32Vector2(5, 9)) = Int32Vector3(20, 20, 0);
	*GetMatrixValue(Int32Vector2(6, 9)) = Int32Vector3(30, 40, 0);
	*GetMatrixValue(Int32Vector2(7, 9)) = Int32Vector3(30, 30, 0);
	*GetMatrixValue(Int32Vector2(8, 9)) = Int32Vector3(30, 20, 0);
	*GetMatrixValue(Int32Vector2(9, 9)) = Int32Vector3(20, 20, 0);
	*GetMatrixValue(Int32Vector2(10, 9)) = Int32Vector3(20, 20, 0);
	*GetMatrixValue(Int32Vector2(11, 9)) = Int32Vector3(30, 40, 0);
	*GetMatrixValue(Int32Vector2(12, 9)) = Int32Vector3(40, 40, 0);
	*GetMatrixValue(Int32Vector2(13, 9)) = Int32Vector3(20, 20, 0);
	*GetMatrixValue(Int32Vector2(14, 9)) = Int32Vector3(30, 30, 0);

	*GetMatrixValue(Int32Vector2(3, 8)) = Int32Vector3(30, 30, 0);
	*GetMatrixValue(Int32Vector2(4, 8)) = Int32Vector3(20, 20, 0);
	*GetMatrixValue(Int32Vector2(5, 8)) = Int32Vector3(30, 30, 0);
	*GetMatrixValue(Int32Vector2(6, 8)) = Int32Vector3(40, 40, 0);
	*GetMatrixValue(Int32Vector2(7, 8)) = Int32Vector3(30, 20, 0);
	*GetMatrixValue(Int32Vector2(8, 8)) = Int32Vector3(30, 20, 0);
	*GetMatrixValue(Int32Vector2(9, 8)) = Int32Vector3(30, 30, 0);
	*GetMatrixValue(Int32Vector2(10, 8)) = Int32Vector3(30, 40, 0);
	*GetMatrixValue(Int32Vector2(11, 8)) = Int32Vector3(20, 40, 0);
	*GetMatrixValue(Int32Vector2(12, 8)) = Int32Vector3(30, 30, 0);
	*GetMatrixValue(Int32Vector2(13, 8)) = Int32Vector3(20, 20, 0);
	*GetMatrixValue(Int32Vector2(14, 8)) = Int32Vector3(40, 40, 0);

	*GetMatrixValue(Int32Vector2(3, 7)) = Int32Vector3(30, 30, 0);
	*GetMatrixValue(Int32Vector2(4, 7)) = Int32Vector3(40, 40, 0);
	*GetMatrixValue(Int32Vector2(5, 7)) = Int32Vector3(20, 20, 0);
	*GetMatrixValue(Int32Vector2(6, 7)) = Int32Vector3(20, 30, 0);
	*GetMatrixValue(Int32Vector2(7, 7)) = Int32Vector3(30, 20, 0);
	*GetMatrixValue(Int32Vector2(8, 7)) = Int32Vector3(30, 20, 0);
	*GetMatrixValue(Int32Vector2(9, 7)) = Int32Vector3(40, 40, 0);
	*GetMatrixValue(Int32Vector2(10, 7)) = Int32Vector3(30, 40, 0);
	*GetMatrixValue(Int32Vector2(11, 7)) = Int32Vector3(40, 30, 0);
	*GetMatrixValue(Int32Vector2(12, 7)) = Int32Vector3(30, 30, 0);
	*GetMatrixValue(Int32Vector2(13, 7)) = Int32Vector3(30, 30, 0);
	*GetMatrixValue(Int32Vector2(14, 7)) = Int32Vector3(20, 20, 0);

	*GetMatrixValue(Int32Vector2(3, 6)) = Int32Vector3(20, 20, 0);
	*GetMatrixValue(Int32Vector2(4, 6)) = Int32Vector3(30, 30, 0);
	*GetMatrixValue(Int32Vector2(5, 6)) = Int32Vector3(40, 40, 0);
	*GetMatrixValue(Int32Vector2(6, 6)) = Int32Vector3(40, 20, 0);
	*GetMatrixValue(Int32Vector2(7, 6)) = Int32Vector3(30, 40, 0);
	*GetMatrixValue(Int32Vector2(8, 6)) = Int32Vector3(40, 20, 0);
	*GetMatrixValue(Int32Vector2(9, 6)) = Int32Vector3(30, 30, 0);
	*GetMatrixValue(Int32Vector2(10, 6)) = Int32Vector3(40, 30, 0);
	*GetMatrixValue(Int32Vector2(11, 6)) = Int32Vector3(30, 30, 0);
	*GetMatrixValue(Int32Vector2(12, 6)) = Int32Vector3(40, 40, 0);
	*GetMatrixValue(Int32Vector2(13, 6)) = Int32Vector3(20, 20, 0);
	*GetMatrixValue(Int32Vector2(14, 6)) = Int32Vector3(20, 20, 0);

	*GetMatrixValue(Int32Vector2(6, 5)) = Int32Vector3(40, 40, 0);
	*GetMatrixValue(Int32Vector2(7, 5)) = Int32Vector3(20, 20, 0);
	*GetMatrixValue(Int32Vector2(8, 5)) = Int32Vector3(30, 30, 0);
	*GetMatrixValue(Int32Vector2(9, 5)) = Int32Vector3(40, 40, 0);
	*GetMatrixValue(Int32Vector2(10, 5)) = Int32Vector3(40, 40, 0);
	*GetMatrixValue(Int32Vector2(11, 5)) = Int32Vector3(40, 40, 0);

	*GetMatrixValue(Int32Vector2(6, 4)) = Int32Vector3(20, 20, 0);
	*GetMatrixValue(Int32Vector2(7, 4)) = Int32Vector3(40, 40, 0);
	*GetMatrixValue(Int32Vector2(8, 4)) = Int32Vector3(40, 40, 0);
	*GetMatrixValue(Int32Vector2(9, 4)) = Int32Vector3(30, 30, 0);
	*GetMatrixValue(Int32Vector2(10, 4)) = Int32Vector3(30, 30, 0);
	*GetMatrixValue(Int32Vector2(11, 4)) = Int32Vector3(20, 20, 0);

	*GetMatrixValue(Int32Vector2(6, 3)) = Int32Vector3(20, 20, 0);
	*GetMatrixValue(Int32Vector2(7, 3)) = Int32Vector3(30, 30, 0);
	*GetMatrixValue(Int32Vector2(8, 3)) = Int32Vector3(40, 40, 0);
	*GetMatrixValue(Int32Vector2(9, 3)) = Int32Vector3(20, 20, 0);
	*GetMatrixValue(Int32Vector2(10, 3)) = Int32Vector3(20, 20, 0);
	*GetMatrixValue(Int32Vector2(11, 3)) = Int32Vector3(40, 40, 0);

	// Fill reference board
	mReferenceBoard.Init(mBoardSlots);
	for (int32 i = 0; i < mReferenceBoard.Num(); i++) {
		mReferenceBoard[i] = 0;
	}
	
	*GetReferenceBoardValue(Int32Vector2(0, 0)) = 900;
	*GetReferenceBoardValue(Int32Vector2(1, 0)) = 800;
	*GetReferenceBoardValue(Int32Vector2(2, 0)) = 800;
	*GetReferenceBoardValue(Int32Vector2(3, 0)) = 900;
	*GetReferenceBoardValue(Int32Vector2(4, 0)) = 1600;
	*GetReferenceBoardValue(Int32Vector2(5, 0)) = 900;

	*GetReferenceBoardValue(Int32Vector2(0, 1)) = 1200;
	*GetReferenceBoardValue(Int32Vector2(1, 1)) = 1200;
	*GetReferenceBoardValue(Int32Vector2(2, 1)) = 800;
	*GetReferenceBoardValue(Int32Vector2(3, 1)) = 1200;
	*GetReferenceBoardValue(Int32Vector2(4, 1)) = 1200;
	*GetReferenceBoardValue(Int32Vector2(5, 1)) = 1200;

	*GetReferenceBoardValue(Int32Vector2(0, 2)) = 1600;
	*GetReferenceBoardValue(Int32Vector2(1, 2)) = 600;
	*GetReferenceBoardValue(Int32Vector2(2, 2)) = 600;
	*GetReferenceBoardValue(Int32Vector2(3, 2)) = 900;
	*GetReferenceBoardValue(Int32Vector2(4, 2)) = 1200;
	*GetReferenceBoardValue(Int32Vector2(5, 2)) = 800;

	*GetReferenceBoardValue(Int32Vector2(0, 3)) = 1200;
	*GetReferenceBoardValue(Int32Vector2(1, 3)) = 600;
	*GetReferenceBoardValue(Int32Vector2(2, 3)) = 900;
	*GetReferenceBoardValue(Int32Vector2(3, 3)) = 800;
	*GetReferenceBoardValue(Int32Vector2(4, 3)) = 800;
	*GetReferenceBoardValue(Int32Vector2(5, 3)) = 600;

	*GetReferenceBoardValue(Int32Vector2(0, 4)) = 600;
	*GetReferenceBoardValue(Int32Vector2(1, 4)) = 600;
	*GetReferenceBoardValue(Int32Vector2(2, 4)) = 1200;
	*GetReferenceBoardValue(Int32Vector2(3, 4)) = 900;
	*GetReferenceBoardValue(Int32Vector2(4, 4)) = 800;
	*GetReferenceBoardValue(Int32Vector2(5, 4)) = 800;

	*GetReferenceBoardValue(Int32Vector2(0, 5)) = 1200;
	*GetReferenceBoardValue(Int32Vector2(1, 5)) = 600;
	*GetReferenceBoardValue(Int32Vector2(2, 5)) = 600;
	*GetReferenceBoardValue(Int32Vector2(3, 5)) = 400;
	*GetReferenceBoardValue(Int32Vector2(4, 5)) = 800;
	*GetReferenceBoardValue(Int32Vector2(5, 5)) = 600;

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


	if (!mLerp)
		return;

	mLerpTime += (mBlendSpeed * DeltaTime);

	// Start lerping
	for (int32 x = 0; x < mBoardSize.x; x++) {
		for (int32 y = 0; y < mBoardSize.y; y++) {
			if (mColorCurve != NULL)
				mMaterialMatrix[ConvertDoubleIndexToSingle(Int32Vector2(x, y), mBoardSize.x)]->SetScalarParameterValue("ColorBlend", mColorCurve->GetFloatValue(mLerpTime));
			else
				mMaterialMatrix[ConvertDoubleIndexToSingle(Int32Vector2(x, y), mBoardSize.x)]->SetScalarParameterValue("ColorBlend", mLerpTime);
		}
	}

	if (mLerpTime >= 1.0f) {
		mLerp = false;
		
		for (int32 x = 0; x < mBoardSize.x; x++) {
			for (int32 y = 0; y < mBoardSize.y; y++) {
				FLinearColor temp;
				mMaterialMatrix[ConvertDoubleIndexToSingle(Int32Vector2(x, y), mBoardSize.x)]->GetVectorParameterValue("Color2", temp);
				mMaterialMatrix[ConvertDoubleIndexToSingle(Int32Vector2(x, y), mBoardSize.x)]->SetVectorParameterValue("Color1", temp);
				mMaterialMatrix[ConvertDoubleIndexToSingle(Int32Vector2(x, y), mBoardSize.x)]->SetScalarParameterValue("ColorBlend", 0);
			}
		}

	}
}

Int32Vector3* AColorPuzzle::GetMatrixValue(Int32Vector2 index) {
	int32 realIndex = ConvertDoubleIndexToSingle(index, mMatrixSize.x);

	if (realIndex >= 0 && realIndex < mMatrixBoard.Num()) {
		return &mMatrixBoard[realIndex];
	}

	else {
		return nullptr;
	}
}

void AColorPuzzle::SetMatrixValue(int32 indexX, int32 indexY, int32 x, int32 y) {
	GetMatrixValue(Int32Vector2(indexX, indexY))->x = x;
	GetMatrixValue(Int32Vector2(indexX, indexY))->y = y;
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

void AColorPuzzle::SetReferenceBoardValue(int32 indexX, int32 indexY, int32 value) {
	*GetReferenceBoardValue(Int32Vector2(indexX, indexY)) = value;
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
	for (int32 x = 0; x < mMatrixSize.x; x++) {
		for (int32 y = 0; y < mMatrixSize.y; y++) {
			Int32Vector3* vector = GetMatrixValue(Int32Vector2(x, y));
			vector->z = vector->x * vector->y;
		}
	}

	for (int32 x = 0; x < mBoardSize.x; x++) {
		for (int32 y = 0; y < mBoardSize.y; y++) {
			mMaterialMatrix[ConvertDoubleIndexToSingle(Int32Vector2(x, y), mBoardSize.x)]->SetVectorParameterValue("Color2",
				*mColorValueReference.Find(GetMatrixValue(Int32Vector2(x + mMatrixEdgeSize.x, y + mMatrixEdgeSize.y))->z));
		}
	}

	mLerp = true;
	mLerpTime = 0;

	//GEngine->ClearOnScreenDebugMessages();
	//PrintMatrix(Int32Vector2(6, 3), Int32Vector2(6, 14));
}

void AColorPuzzle::CheckCombination() {
	if (ReferenceBoardMatrixIsSame()) {
		PuzzleDone();

		AAboveGameMode* gameMode = (AAboveGameMode*)GetWorld()->GetAuthGameMode();
		if (gameMode != nullptr) 
			gameMode->SetCompleteStatus(this, true);
	}
}

void AColorPuzzle::ActivateSlide(int32 slideNum, bool movePositiveDirection) {
	//GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Red, FString::Printf(TEXT("%d"), movePositiveDirection));

	if (slideNum >= 0 && slideNum <= mNumberOfSlides) {
		if (mSlidePositionArray[slideNum].x == mSlidePositionArray[slideNum].z) {
			ShiftSlide(slideNum, movePositiveDirection);
		}
	}
}

Int32Vector2 AColorPuzzle::ConvertSlideNumberToIndex(int32 number) {
	Int32Vector2 firstInSlide;

	if (number <= 5) {
		firstInSlide.x = 0;
		firstInSlide.y = mMatrixSize.y - 1 - mMatrixEdgeSize.y - number;
	}

	else {
		firstInSlide.x = number;
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
			if (mSlideOffset[slideNum] < mMaxSlideOffset.x) {
				StartMoveSlide();
				mSlidePositionArray[slideNum].z -= FVector(3, 0, 0);
				mSlideOffset[slideNum]++;
				index.x = mMatrixSize.x - 1;
				indexAddition = Int32Vector2(-1, 0);
				lowerIndexLimit = 1;
				upperIndexLimit = mMatrixSize.x - 1;

			}
		}

		else {
			if (mSlideOffset[slideNum] > -mMaxSlideOffset.x) {
				StartMoveSlide();
				mSlidePositionArray[slideNum].z += FVector(3, 0, 0);
				mSlideOffset[slideNum]--;
				index.x = 0;
				indexAddition = Int32Vector2(1, 0);
				lowerIndexLimit = 0;
				upperIndexLimit = mMatrixSize.x - 2;
			}
		}

		while (index.x >= lowerIndexLimit && index.x <= upperIndexLimit && lowerIndexLimit != upperIndexLimit) {
			GetMatrixValue(index)->x = GetMatrixValue(index + indexAddition)->x;
			index += indexAddition;
		}
	}

	// Shift along y
	else {
		if (movePositiveDirection) {
			if (mSlideOffset[slideNum] < mMaxSlideOffset.y) {
				StartMoveSlide();
				mSlidePositionArray[slideNum].z += FVector(0, 3, 0);
				mSlideOffset[slideNum]++;
				index.y = mMatrixSize.y - 1;
				indexAddition = Int32Vector2(0, -1);
				lowerIndexLimit = 1;
				upperIndexLimit = mMatrixSize.y - 1;
			}
		}

		else {
			if (mSlideOffset[slideNum] > -mMaxSlideOffset.y) {
				StartMoveSlide();
				mSlidePositionArray[slideNum].z -= FVector(0, 3, 0);
				mSlideOffset[slideNum]--;
				index.y = 0;
				indexAddition = Int32Vector2(0, 1);
				lowerIndexLimit = 0;
				upperIndexLimit = mMatrixSize.y - 2;
			}
		}

		while (index.y >= lowerIndexLimit && index.y <= upperIndexLimit && lowerIndexLimit != upperIndexLimit) {
			GetMatrixValue(index)->y = GetMatrixValue(index + indexAddition)->y;
			index += indexAddition;
		}
	}

	multiplyColor();
}

void AColorPuzzle::PrintMatrix(Int32Vector2 lowerBound, Int32Vector2 upperBound) {
	for (int32 x = lowerBound.x; x <= upperBound.x; x++) {
		for (int32 y = lowerBound.y; y <= upperBound.y; y++) {
			GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Magenta, FString::Printf(TEXT("%d, %d: %d, %d, %d"), x, y, mMatrixBoard[ConvertDoubleIndexToSingle(Int32Vector2(x, y), mMatrixSize.x)].x, mMatrixBoard[ConvertDoubleIndexToSingle(Int32Vector2(x, y), mMatrixSize.x)].y, mMatrixBoard[ConvertDoubleIndexToSingle(Int32Vector2(x, y), mMatrixSize.x)].z));
		}
	}
}

bool AColorPuzzle::ReferenceBoardMatrixIsSame() {
	bool isSame = true;

	for (int32 x = 0; x < mBoardSize.x; x++) {
		for (int32 y = 0; y < mBoardSize.y; y++) {
			Int32Vector3* matrix = GetMatrixValue(Int32Vector2(x + mMatrixEdgeSize.x, y + mMatrixEdgeSize.y));
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