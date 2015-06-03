// Fill out your copyright notice in the Description page of Project Settings.

#include "Above.h"
#include "MainMenuHUD.h"


AMainMenuHUD::AMainMenuHUD(const class FObjectInitializer& FOB) :
Super(FOB){

}

void AMainMenuHUD::DrawHUD() {
	DrawText(TEXT("pööp"), FVector2D(0, 0), mFont, FVector2D(1, 1), FColor::White);
}

void AMainMenuHUD::PostInitializeComponents() {
	Super::PostInitializeComponents();
}


