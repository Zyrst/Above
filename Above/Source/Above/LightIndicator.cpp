// Fill out your copyright notice in the Description page of Project Settings.

#include "Above.h"
#include "LightIndicator.h"
#include "PuzzleSlabIndicatorLight.h"

// Sets default values
ALightIndicator::ALightIndicator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	LampsOn = 0;
}

// Called when the game starts or when spawned
void ALightIndicator::BeginPlay()
{
	Super::BeginPlay();
	/*for (TActorIterator<AActor> itr(GetWorld()); itr; ++itr){
		APuzzleSlabIndicatorLight* tmp = Cast<APuzzleSlabIndicatorLight>(*itr);
		if (tmp != nullptr){
			mLights.Push(tmp);
		}
	}*/
	mOnceLoad = false;
	TArray<UStaticMeshComponent*> Components;
	this->GetComponents<UStaticMeshComponent>(Components);
	for (int32 i = 0; i < Components.Num(); i++){
		UStaticMeshComponent* mesh = Components[i];
		if (mesh->GetName() == "Indicator"){
			mLightIndMesh = Components[i];
			//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, mLightIndMesh->GetName());
		}
	}

	mLightMaterial = mLightIndMesh->CreateAndSetMaterialInstanceDynamic(0);
	mLightMaterial->SetTextureParameterValue("Texture1", mShellTexture[0]);
	mLightMaterial->SetTextureParameterValue("Emmisive", mEmmisiveTexture[0]);
	
	
}

// Called every frame
void ALightIndicator::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ALightIndicator::Reduce(){
	//mLights[mLampsOff++]->LightOff();
	LampsOn++;
	//Test to see if preloading texture worked
	/*if (!mOnceLoad){
		for (int32 i = 0; i < mShellTexture.Num(); i++){
			//mShellTexture[i]->NeverStream = true;
			mLightMaterial->SetTextureParameterValue("Texture1", mShellTexture[i]);
			mLightMaterial->SetTextureParameterValue("Emmisive", mEmmisiveTexture[i]);
		}
		mOnceLoad = true;
	}*/
	mLightMaterial->SetTextureParameterValue("Texture1", mShellTexture[LampsOn]);
	mLightMaterial->SetTextureParameterValue("Emmisive", mEmmisiveTexture[LampsOn]);

	SoundEventLightLit();
}

void ALightIndicator::Reset(){
	/*for (int32 i = 0; i < mLights.Num(); i++){
		mLights[i]->Reset();
	}*/
	LampsOn = 0;
	mLightMaterial->SetTextureParameterValue("Texture1", mShellTexture[LampsOn]);
	mLightMaterial->SetTextureParameterValue("Emmisive", mEmmisiveTexture[LampsOn]);
}