// Fill out your copyright notice in the Description page of Project Settings.

#include "Above.h"
#include "PlayerSetting.h"

void APlayerSetting::OnConstruction(const FTransform& Transform){
	mSettings = GEngine->GameUserSettings;
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
	mSettings->ApplyNonResolutionSettings();

	mSettings->ApplySettings(true);
	mSettings->SaveSettings();
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("VSYNC value %s"), VSYNC ? TEXT("true") : TEXT("false")));
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("VSYNC Gamesettings %s"), mSettings->IsVSyncEnabled() ? TEXT("true") : TEXT("false")));
}