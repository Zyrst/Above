// Fill out your copyright notice in the Description page of Project Settings.

#include "Above.h"
#include "Lamp.h"
#include "Stefun.h"
#include "AboveGameMode.h"


// Sets default values
ALamp::ALamp(const FObjectInitializer& ObjectInitializer) :
	mAction(false),
	mActionKill(false),
	mKillingDuration(5),
	mKillingBrightnessIncreaseFactor(4),
	mSavingBrightnessDecreaseFactor(0.5),
	mKillingAttenuationIncreaseFactor(4),
	mSavingAttenuationDecreaseFactor(0.5),
	mTransitionSpeed(0.8f),
	mFlickerAmount(200),
	mFlickerIntensity(1),
	mBlinkFactor(1),
	mSoundIntensity(2),
	mPressedBefore(false){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ALamp::BeginPlay(){
	Super::BeginPlay();

	// Populate lights array
	TArray<UPointLightComponent*> mLightTemp;
	this->GetComponents(mLightTemp);
	
	// Add only moveable lights
	for (int32 i = 0; i < mLightTemp.Num(); i++) {
		if (mLightTemp[i]->Mobility == EComponentMobility::Movable)
			mLights.Add(mLightTemp[i]);
	}

	// Add default intensities
	for (int32 i = 0; i < mLights.Num(); i++) {
		if (mLights[i] != NULL) {
			mLightDefaultIntensity.Add(mLights[i]->Intensity);
			mLightDefaultAttenuation.Add(mLights[i]->AttenuationRadius);
			mLightDefaultPosition.Add(mLights[i]->GetComponentLocation());
		}
		else {
			mLightDefaultIntensity.Add(0);
			mLightDefaultAttenuation.Add(0);
			mLightDefaultPosition.Add(FVector(0, 0, 0));
		}
	}

	TArray<UActorComponent*> components;
	this->GetComponents(components);
	for (int32 i = 0; i < components.Max(); i++) {
		if (components[i]->GetName() == TEXT("Fireflies")) {
			mFireflyParticles = components[i];
			break;
		}
	}

	TArray<USphereComponent*> colliders;
	this->GetComponents(colliders);
	if (colliders.Num() > 0) {
		mSphereCollider = colliders[0];
		mSphereCollider->OnComponentBeginOverlap.AddDynamic(this, &ALamp::OnOverlapBegin);
		mSphereCollider->OnComponentEndOverlap.AddDynamic(this, &ALamp::OnOverlapEnd);
	}

	SoundEventBeginPlay();
}

// Called every frame
void ALamp::Tick( float DeltaTime ){
	Super::Tick( DeltaTime );

	if (mTrackPlayer)
		SoundEventDistance();
	
	// Clamp flicker amount
	int32 flicktmp = (mFlickerAmount == 0) ? 1 : mFlickerAmount;
	for (int32 i = 0; i < mLights.Num(); i++) {
	
		// Randomize new values
		float newIntensity	= (rand() % flicktmp) + (mLightDefaultIntensity[i] - mFlickerAmount);
		float newAtt		= (rand() % flicktmp) + (mLightDefaultAttenuation[i] - mFlickerAmount);
		float lerpFactor	= mFlickerIntensity * mBlinkFactor;
		
		// Check if buttons has been pressed
		if (mAction) {
			// Check if "kill" action
			if (mActionKill) {
				newIntensity	= ((rand() % flicktmp) + (mLightDefaultIntensity[i] - mFlickerAmount)) * mKillingBrightnessIncreaseFactor;
				newAtt			= ((rand() % flicktmp) + (mLightDefaultAttenuation[i] - mFlickerAmount)) * mKillingAttenuationIncreaseFactor;
			}
			else {
				newIntensity	= ((rand() % flicktmp) + (mLightDefaultIntensity[i] - mFlickerAmount)) * mSavingBrightnessDecreaseFactor;
				newAtt			= ((rand() % flicktmp) + (mLightDefaultAttenuation[i] - mFlickerAmount)) * mSavingAttenuationDecreaseFactor;
			}

			// Set lerp "speed"
			lerpFactor = mTransitionSpeed;
		}

		
		FVector newPos = mLightDefaultPosition[i] + FMath::VRand() * (flicktmp / 100.0f);

		// Clamp lower bound
		if (newIntensity <= 0)
			newIntensity = 0;
		if (newAtt <= 0)
			newAtt = 0;

		// Lerp towards new values
		mLights[i]->Intensity			= FMath::Lerp(mLights[i]->Intensity, newIntensity, lerpFactor);
		mLights[i]->AttenuationRadius	= FMath::Lerp(mLights[i]->AttenuationRadius, newAtt, lerpFactor);

		// Lerp towards new position
		mLights[i]->SetWorldLocation(FMath::Lerp<FVector, float>(mLights[i]->GetComponentLocation(), newPos, mFlickerIntensity));

		// Update brightness and color
		mLights[i]->UpdateColorAndBrightness();
	}

	if (mKillTimer >= 0) {
		mKillTimer -= DeltaTime;
	}
	// Only reset if save
	else if (mAction && !mActionKill) {
		mAction		= false;
		mActionKill = false;
		if (mFireflyParticles != NULL)
			mFireflyParticles->Deactivate();

		mSoundIntensity = 2;
		SoundEventIntensityChange();
	}
}


// Kill fireflies
void ALamp::ActivateFirst() {
	// Do not allow press when action. R.I.P English
	if (mAction)
		return;

	mSoundIntensity = 3;
	mAction			= true;
	mActionKill		= true;
	mKillTimer		= mKillingDuration;

	// Call sound events
	SoundEventFireflyRelease();
	SoundEventButtonPress();
	SoundEventIntensityChange();

	// Puzzle is done
	AAboveGameMode* mode = (AAboveGameMode*)GetWorld()->GetAuthGameMode();
	if (mode != nullptr)
		mode->SetCompleteStatus(this, true);
}

// Release fireflies
void ALamp::ActivateSecond() {
	// Do not allow press when action
	if (mAction)
		return;

	mPressedBefore	= true;
	mSoundIntensity = 1;
	mAction			= true;
	mActionKill		= false;
	mKillTimer		= mKillingDuration;
	if (mFireflyParticles != NULL)
		mFireflyParticles->Activate();

	// Call sound events
	SoundEventFireflyElectrocute();
	SoundEventButtonPress();
	SoundEventIntensityChange();

	// Puzzle is done
	AAboveGameMode* mode = (AAboveGameMode*)GetWorld()->GetAuthGameMode();
	if (mode != nullptr)
		mode->SetCompleteStatus(this, true);
}


void ALamp::OnOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	TArray<AActor*> actors;
	GetOverlappingActors(actors, AStefun::StaticClass());

	if (actors.Num() > 0) {
		mPlayerReference = actors[0];
		mTrackPlayer = true;
	}
}

void ALamp::OnOverlapEnd(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	TArray<AActor*> actors;
	GetOverlappingActors(actors, AStefun::StaticClass());

	if (actors.Num() > 0) {
		mTrackPlayer = false;
	}
}


float ALamp::GetDistanceFromPlayer() {
	FVector p1 = this->GetTransform().GetLocation();
	FVector p2 = mPlayerReference->GetTransform().GetLocation();

	return FMath::Sqrt(FVector::Dist(p1, p2));
}

float ALamp::GetSoundIntensityLevel() {
	return mSoundIntensity;
}


float ALamp::GetPlayedStatus() {
	return mPressedBefore ? 1.0f : 0.0f;
}
