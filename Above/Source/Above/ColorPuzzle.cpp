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

	mMatrixBoard.Init(mMatrixSizeX * mMatrixSizeY);

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
	
	Int32Vector2 bob = ConvertSlideNumberToIndex(11);

	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Magenta, FString::Printf(TEXT("Trigger: %d | %d"), bob.x, bob.y));
}

// Called every frame
void AColorPuzzle::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );


}

Int32Vector3* AColorPuzzle::GetMatrixValue(int32 x, int32 y) {
	int32 index = x + (mMatrixSizeX * y);

	if (index < mMatrixBoard.Num())
		return &mMatrixBoard[index];

	else
		return nullptr;
}

void AColorPuzzle::Int32Flip(int32* x, int32* y) {
	moveBuffer = *x;
	*x = *y;
	*x = moveBuffer;
}

void AColorPuzzle::multiplyColor(Int32Vector3* vector) {
	vector->z = vector->x * vector->y;
	// Todo update visuals or some shit
}

void AColorPuzzle::Activate(int32 slideNum) {
	//Int32Vector2 
}

Int32Vector2 AColorPuzzle::ConvertSlideNumberToIndex(int32 number) {
	Int32Vector2 firstInSlide;

	if (number <= 5) {
		firstInSlide.x = 3;
		firstInSlide.y = 8 - number;
	}

	else {
		firstInSlide.x = number - 3;
		firstInSlide.y = 3;
	}

	return firstInSlide;
}