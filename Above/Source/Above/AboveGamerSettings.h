// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameUserSettings.h"
#include "AboveGamerSettings.generated.h"

/**
 * 
 */
UCLASS()
class ABOVE_API UAboveGamerSettings : public UGameUserSettings
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = Window)
		void SetWindow();
	UFUNCTION(BlueprintCallable, Category = VSync)
		void ToggleVSync(bool value);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Screen)
		FVector2D Resolution;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Screen)
		int32 WindowMode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = VSync)
		bool VSYNC;
};
