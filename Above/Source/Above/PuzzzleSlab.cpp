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
	
	mSlabMesh = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("Slab"));
	mSlabMesh->AttachParent = mRootComponent;

	mOverlapBox->OnComponentBeginOverlap.AddDynamic(this, &APuzzzleSlab::BeginOverlapOnBox);

	mIsCorrectSlab = false;
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

void APuzzzleSlab::BeginOverlapOnBox(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	SteppedOnSlab();
}

void APuzzzleSlab::SteppedOnSlab_Implementation() {

}

void APuzzzleSlab::LightUpSlab() {
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, TEXT("Slab is lit, trust me brah"));
}

void APuzzzleSlab::ResetSlab() {
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, TEXT("Slab reset"));
}