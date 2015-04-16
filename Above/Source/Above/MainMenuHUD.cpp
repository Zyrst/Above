// Fill out your copyright notice in the Description page of Project Settings.

#include "Above.h"
#include "MainMenuHUD.h"


AMainMenuHUD::AMainMenuHUD(const class FPostConstructInitializeProperties& PCIP) :
Super(PCIP){

}

void AMainMenuHUD::DrawHUD() {
	DrawText(TEXT("pööp"), FVector2D(0, 0), mFont, FVector2D(1, 1), FColor::White);
}

void AMainMenuHUD::PostInitializeComponents() {
	Super::PostInitializeComponents();
}


