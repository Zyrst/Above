// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Info.h"
#include "PlayerSetting.generated.h"

/**
 * 
 */
UCLASS()
class ABOVE_API APlayerSetting : public AInfo
{
	GENERATED_BODY()
	
public:

	virtual void OnConstruction(const FTransform& Transform) override;

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
private:
	UGameUserSettings* mSettings;

	bool onceLoad = false;
};
