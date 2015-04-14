// Fill out your copyright notice in the Description page of Project Settings.

#include "Above.h"
#include "PuzzzleSlab.h"


// Sets default values
APuzzzleSlab::APuzzzleSlab(const FObjectInitializer& ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mRootComponent = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("RootCompenent"));
	RootComponent = mRootComponent;

	mOverlapBox = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("CollisionBox"));
	mOverlapBox->AttachParent = mRootComponent;
	
	mSlab = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("Slab"));
	mSlab->AttachParent = mRootComponent;

	//mOverlapBox->OnComponentBeginOverlap
}

// Called when the game starts or when spawned
void APuzzzleSlab::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APuzzzleSlab::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

void APuzzzleSlab::BeginOverlapOnBox(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Overlap")));
}