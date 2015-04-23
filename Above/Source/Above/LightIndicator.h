// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "LightIndicator.generated.h"

class APuzzleSlabIndicatorLight;

UCLASS()
class ABOVE_API ALightIndicator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALightIndicator();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION(BlueprintCallable, Category = Reduce)
		void Reduce();

	UFUNCTION(BlueprintCallable, Category = Reset)
		void Reset();

	/** Populate this with materials corresponding to numbers */
	UPROPERTY(EditAnywhere, Category = Material)
		TArray<UTexture2D*> mShellTexture;
	UPROPERTY(EditAnywhere, Category = Material)
		TArray<UTexture2D*> mEmmisiveTexture;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Lamps)
		int32 LampsOn;

	/** Event called when lights are lit */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "fmod")
		void SoundEventLightLit();

	/** Event called when puzzle is activated */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "fmod")
		void SoundEventActivate();

private:	
	TArray<APuzzleSlabIndicatorLight*> mLights;
	UStaticMeshComponent* mLightIndMesh;
	UMaterialInstanceDynamic* mLightMaterial;
};
