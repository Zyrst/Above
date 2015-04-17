// Fill out your copyright notice in the Description page of Project Settings.

#include "Above.h"
#include "PuzzleSlabIndicatorLight.h"


// Sets default values
APuzzleSlabIndicatorLight::APuzzleSlabIndicatorLight(const FObjectInitializer& ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mRootComponent = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("RootCompenent"));
	RootComponent = mRootComponent;

	mLightMesh = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("LightMesh"));
	mLightMesh->AttachParent = mRootComponent;
}

// Called when the game starts or when spawned
void APuzzleSlabIndicatorLight::BeginPlay()
{
	Super::BeginPlay();
	
	mLightMaterial = mLightMesh->CreateAndSetMaterialInstanceDynamic(0);

	if (mLightTextures.Num() == 2) {
		mLightMaterial->SetTextureParameterValue("BaseTexture", mLightTextures[0]);
	}
}

// Called every frame
void APuzzleSlabIndicatorLight::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void APuzzleSlabIndicatorLight::LightOff() {
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, TEXT("Turned light off"));
	if (mLightTextures.Num() == 2) {
		mLightMaterial->SetTextureParameterValue("BaseTexture", mLightTextures[1]);
	}
}

void APuzzleSlabIndicatorLight::Reset() {
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, TEXT("Reset light"));
	if (mLightTextures.Num() == 2) {
		mLightMaterial->SetTextureParameterValue("BaseTexture", mLightTextures[0]);
	}
}