// Fill out your copyright notice in the Description page of Project Settings.

#include "Above.h"
#include "AboveGamerSettings.h"


void UAboveGamerSettings::SetWindow(){
	switch (WindowMode){
	case 0:
		if (!(GetScreenResolution().X == Resolution.X) && !(GetScreenResolution().Y == Resolution.Y))
			SetScreenResolution(FIntPoint(Resolution.X, Resolution.Y));
		if (!(GetFullscreenMode() == EWindowMode::Fullscreen))
			SetFullscreenMode(EWindowMode::Fullscreen);
		break;
	case 1:
		if (!(GetScreenResolution().X == Resolution.X) && !(GetScreenResolution().Y == Resolution.Y))
			SetScreenResolution(FIntPoint(Resolution.X, Resolution.Y));
		if (!(GetFullscreenMode() == EWindowMode::Windowed))
			SetFullscreenMode(EWindowMode::Windowed);
		break;
	case 2:
		if (!(GetScreenResolution().X == Resolution.X) && !(GetScreenResolution().Y == Resolution.Y))
			SetScreenResolution(FIntPoint(Resolution.X, Resolution.Y));
		if (!(GetFullscreenMode() == EWindowMode::WindowedFullscreen))
			SetFullscreenMode(EWindowMode::WindowedFullscreen);
		break;
	}

	ConfirmVideoMode();
	ApplyResolutionSettings(true);
	ApplyNonResolutionSettings();
	ApplySettings(true);
	SaveSettings();
}

void UAboveGamerSettings::ToggleVSync(bool value){
	SetVSyncEnabled(value);

	VSYNC = value;
	ApplyNonResolutionSettings();

	ApplySettings(true);
	SaveSettings();
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("VSYNC value %s"), VSYNC ? TEXT("true") : TEXT("false")));
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("VSYNC Gamesettings %s"), IsVSyncEnabled() ? TEXT("true") : TEXT("false")));

}