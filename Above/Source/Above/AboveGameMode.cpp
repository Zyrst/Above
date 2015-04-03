// Fill out your copyright notice in the Description page of Project Settings.

#include "Above.h"
#include "AboveGameMode.h"

AAboveGameMode::AAboveGameMode(const class FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer){
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnObject(TEXT("Blueprint'/Game/Blueprints/Characters/Stefun_Blueprint.Stefun_Blueprint_C'"));
	if (PlayerPawnObject.Class != NULL){
		DefaultPawnClass = PlayerPawnObject.Class;
	}
	mStandardFoV = StandardFoV;
	if ((GEngine != NULL) && (GEngine->GameViewport != NULL)){
		GEngine->GameViewport->SetSuppressTransitionMessage(true);
	}
}

int32 AAboveGameMode::getStandardFoV(){
	return mStandardFoV;
}