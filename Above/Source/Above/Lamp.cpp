// Fill out your copyright notice in the Description page of Project Settings.

#include "Above.h"
#include "Lamp.h"


// Sets default values
ALamp::ALamp(const FObjectInitializer& ObjectInitializer){
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


void ALamp::ActivateFirst() {
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Lamp first action")));
}

void ALamp::ActivateSecond() {
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Lamp second action")));
}

