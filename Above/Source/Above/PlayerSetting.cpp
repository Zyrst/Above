// Fill out your copyright notice in the Description page of Project Settings.

#include "Above.h"
#include "PlayerSetting.h"

void APlayerSetting::OnConstruction(const FTransform& Transform){
	mSettings = GEngine->GameUserSettings;
	VSYNC = mSettings->IsVSyncEnabled();
	GConfig->GetFloat(TEXT("Above.PlayerSetting"), TEXT("StandardFoV"), StandardFoV, GGameUserSettingsIni);
	if (StandardFoV == 0){
		StandardFoV = 70;
	}
}

void APlayerSetting::SetWindow(){

	switch (WindowMode){
	case 0:
		if (!(mSettings->GetScreenResolution().X == Resolution.X) && !(mSettings->GetScreenResolution().Y == Resolution.Y))
			mSettings->SetScreenResolution(FIntPoint(Resolution.X, Resolution.Y));
		if (!(mSettings->GetFullscreenMode() == EWindowMode::Fullscreen))
			mSettings->SetFullscreenMode(EWindowMode::Fullscreen);
		break;
	case 1:
		if (!(mSettings->GetScreenResolution().X == Resolution.X) && !(mSettings->GetScreenResolution().Y == Resolution.Y))
			mSettings->SetScreenResolution(FIntPoint(Resolution.X, Resolution.Y));
		if (!(mSettings->GetFullscreenMode() == EWindowMode::Windowed))
			mSettings->SetFullscreenMode(EWindowMode::Windowed);
		break;
	case 2:
		if (!(mSettings->GetScreenResolution().X == Resolution.X) && !(mSettings->GetScreenResolution().Y == Resolution.Y))
			mSettings->SetScreenResolution(FIntPoint(Resolution.X, Resolution.Y));
		if (!(mSettings->GetFullscreenMode() == EWindowMode::WindowedFullscreen))
			mSettings->SetFullscreenMode(EWindowMode::WindowedFullscreen);
		break;
	}

	mSettings->ConfirmVideoMode();
	mSettings->ApplyResolutionSettings(true);
	mSettings->ApplyNonResolutionSettings();
	mSettings->ApplySettings(true);
	mSettings->SaveSettings();
	
}

void APlayerSetting::ToggleVSync(bool value){
	mSettings->SetVSyncEnabled(value);
	VSYNC = value;
	//mSettings->ApplyNonResolutionSettings();

	mSettings->ApplySettings(true);
	mSettings->SaveSettings();
}

void APlayerSetting::SetQuality(int32 value){
	
	mSettings->ScalabilityQuality.TextureQuality = value;
	mSettings->ScalabilityQuality.EffectsQuality = value;
	mSettings->ScalabilityQuality.ShadowQuality = value;
	mSettings->ScalabilityQuality.PostProcessQuality = value;
	mSettings->ScalabilityQuality.ViewDistanceQuality = value;
	mSettings->ScalabilityQuality.AntiAliasingQuality = value;

	switch (value){
	case 0:
		mSettings->ScalabilityQuality.ResolutionQuality = 50;
		break;
	case 1:
		mSettings->ScalabilityQuality.ResolutionQuality = 71;
		break;
	case 2:
		mSettings->ScalabilityQuality.ResolutionQuality = 87;
		break;
	case 3:
		mSettings->ScalabilityQuality.ResolutionQuality = 100;
		break;
	}

	mSettings->ApplySettings(true);
	mSettings->SaveSettings();
	
}

void APlayerSetting::SaveFoV(){
	GConfig->SetFloat(TEXT("Above.PlayerSetting"), TEXT("StandardFoV"), StandardFoV, GGameUserSettingsIni);
}