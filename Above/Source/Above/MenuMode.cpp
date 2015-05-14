// Fill out your copyright notice in the Description page of Project Settings.

#include "Above.h"
#include "MenuMode.h"


AMenuMode::AMenuMode(const class FObjectInitializer& ObjectInitializer):
Super(ObjectInitializer){
	/*static ConstructorHelpers::FClassFinder<AHUD> HUD(TEXT("Blueprint'/Game/Blueprints/HUDs/MainMenuHUD_blueprint.MainMenuHUD_blueprint_C'"));
	if (HUD.Class != NULL)
		HUDClass = HUD.Class;*/
	
}
void AMenuMode::OnConstruction(const FTransform& transform){
	//Load saved settings , might want to do this somewhere else
	GEngine->GetGameUserSettings()->LoadSettings();
}
