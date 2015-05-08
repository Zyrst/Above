// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "MenuMode.generated.h"

/**
 * 
 */
UCLASS()
class ABOVE_API AMenuMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	AMenuMode(const class FObjectInitializer& ObjectInitializer);
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default values")
		FName DefaultLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Screen)
		FVector2D Resolution;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Screen)
		int32 WindowMode;
	UFUNCTION(BlueprintCallable, Category = Screen)
		void SetWindow();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Screen)
		bool VSYNC;
private:
	UGameUserSettings* mSettings;
};
