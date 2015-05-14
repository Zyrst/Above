// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Info.h"
#include "PlayerSetting.generated.h"

/**
 * 
 */
UCLASS(Config = GameUserSettings)
class ABOVE_API APlayerSetting : public AInfo
{
	GENERATED_BODY()
	
public:

	virtual void OnConstruction(const FTransform& Transform) override;
	/**Sets window size and which fullscreen mode , depending on variables Windowmode and resolution*/
	UFUNCTION(BlueprintCallable, Category = Window)
		void SetWindow();
	/**Switch between vsync modes*/
	UFUNCTION(BlueprintCallable, Category = VSync)
		void ToggleVSync(bool value);
	/**Set graphical quality , value between 0 - 3*/
	UFUNCTION(BlueprintCallable, Category = Graphic)
		void SetQuality(int32 value);
	/**Save FoV to Game user setting ini file*/
	UFUNCTION(BlueprintCallable, Category = FoV)
		void SaveFoV();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Screen)
		FVector2D Resolution;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Screen)
		int32 WindowMode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = VSync)
		bool VSYNC;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FOV)
		float StandardFoV;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FOV)
		float ZoomFoV = 40;
private:
	UGameUserSettings* mSettings;

};
