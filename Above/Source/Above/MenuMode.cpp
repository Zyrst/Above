// Fill out your copyright notice in the Description page of Project Settings.

#include "Above.h"
#include "MenuMode.h"


AMenuMode::AMenuMode(const class FObjectInitializer& ObjectInitializer):
Super(ObjectInitializer){
	/*static ConstructorHelpers::FClassFinder<AHUD> HUD(TEXT("Blueprint'/Game/Blueprints/HUDs/MainMenuHUD_blueprint.MainMenuHUD_blueprint_C'"));
	if (HUD.Class != NULL)
		HUDClass = HUD.Class;*/
	WindowMode = 0;
	Resolution.Set(1280, 720);

}

void AMenuMode::SetWindow(){
	//GEngine->GameUserSettings->RequestResolutionChange(x, y, mode, false);
	switch (WindowMode){
	case 0:
		GEngine->GameUserSettings->SetScreenResolution(FIntPoint(Resolution.X, Resolution.Y));
		GEngine->GameUserSettings->SetFullscreenMode(EWindowMode::Fullscreen);
		break;
	case 1:
		GEngine->GameUserSettings->SetScreenResolution(FIntPoint(Resolution.X, Resolution.Y));
		GEngine->GameUserSettings->SetFullscreenMode(EWindowMode::Windowed);
		break;
	case 2:
		GEngine->GameUserSettings->SetScreenResolution(FIntPoint(Resolution.X, Resolution.Y));
		GEngine->GameUserSettings->SetFullscreenMode(EWindowMode::WindowedFullscreen);
		break;
	}
			
		
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Set Res"));
		
		GEngine->GameUserSettings->ConfirmVideoMode();
		
		GEngine->GameUserSettings->ApplyResolutionSettings(true);
		GEngine->GameUserSettings->ApplyNonResolutionSettings();
		GEngine->GameUserSettings->ApplySettings();
		//GEngine->GameUserSettings->SetScreenResolution(GEngine->GameUserSettings->GetLastConfirmedScreenResolution());
		//GEngine->GameUserSettings->SetFullscreenMode(GEngine->GameUserSettings->GetLastConfirmedFullscreenMode());
		//GEngine->GameUserSettings->ApplySettings();
		GEngine->GameUserSettings->SaveSettings();
		

}