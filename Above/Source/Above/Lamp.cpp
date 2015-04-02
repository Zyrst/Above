// Fill out your copyright notice in the Description page of Project Settings.

#include "Above.h"
#include "Lamp.h"


// Sets default values
ALamp::ALamp(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ALamp::BeginPlay(){
	Super::BeginPlay();

	// Populate lights array
	this->GetComponents(mLights);
	
	// Add default intensities
	for (int i = 0; i < mLights.Num(); i++) {
		if (mLights[i] != NULL) {
			mLightDefaultIntensity.push_back(mLights[i]->Intensity);
			mLightDefaultAttenuation.push_back(mLights[i]->AttenuationRadius);
			mLightDefaultPosition.push_back(mLights[i]->GetComponentLocation());
		}
		else {
			mLightDefaultIntensity.push_back(0);
			mLightDefaultAttenuation.push_back(0);
			mLightDefaultPosition.push_back(FVector(0, 0, 0));
		}
	}
}

// Called every frame
void ALamp::Tick( float DeltaTime ){
	Super::Tick( DeltaTime );

	
	// Clamp flicker amount
	int32 flicktmp = (flickerAmount == 0) ? 1 : flickerAmount;
	for (int i = 0; i < mLights.Num(); i++) {
	
		// Randomize new values
		float newInt	= (rand() % flicktmp) + (mLightDefaultIntensity[i] - flickerAmount);
		float newAtt	= (rand() % flicktmp) + (mLightDefaultAttenuation[i] - flickerAmount);
		FVector newPos	= mLightDefaultPosition[i] + FMath::VRand() * (flicktmp / 100.0f);

		// Clamp lower bound
		if (newInt <= 0)
			newInt = 0;
		if (newAtt <= 0)
			newAtt = 0;

		// Lerp towards new values
		mLights[i]->Intensity			= FMath::Lerp(mLights[i]->Intensity, newInt, flickerIntensity * blinkFactor);
		mLights[i]->AttenuationRadius	= FMath::Lerp(mLights[i]->AttenuationRadius, newAtt, flickerIntensity * blinkFactor);

		// Lerp towards new position
		mLights[i]->SetWorldLocation(FMath::Lerp<FVector, float>(mLights[i]->GetComponentLocation(), newPos, flickerIntensity));

		// Update brightness and color
		mLights[i]->UpdateColorAndBrightness();
	}

}


