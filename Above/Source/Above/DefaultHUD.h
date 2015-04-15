// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "DefaultHUD.generated.h"

/**
 * 
 */
UCLASS()
class ABOVE_API ADefaultHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	ADefaultHUD(const class FPostConstructInitializeProperties& PCIP);

	virtual void DrawHUD() override;
	virtual void PostInitializeComponents() override;
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crosshair")
		UTexture2D* mCrosshairTexture;

};
