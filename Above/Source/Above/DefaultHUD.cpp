// Fill out your copyright notice in the Description page of Project Settings.

#include "Above.h"
#include "DefaultHUD.h"


ADefaultHUD::ADefaultHUD(const class FPostConstructInitializeProperties& PCIP):
Super(PCIP){
	
}

void ADefaultHUD::DrawHUD() {
	// Draw crosshair
	DrawTextureSimple(mCrosshairTexture, 
		Canvas->SizeX / 2 - mCrosshairTexture->GetSizeX() / 2, 
		Canvas->SizeY / 2 - mCrosshairTexture->GetSizeY() / 2, 
		1, false);
}

void ADefaultHUD::PostInitializeComponents() {
	Super::PostInitializeComponents();

}

