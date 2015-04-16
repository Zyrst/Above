// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "PuzzleSlabIndicatorLight.generated.h"

UCLASS()
class ABOVE_API APuzzleSlabIndicatorLight : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APuzzleSlabIndicatorLight(const FObjectInitializer& ObjectInitializer);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	/** Turn light effects off */
	UFUNCTION(BlueprintCallable, Category = Effect)
		void LightOff();

	/** Reset light effects */
	UFUNCTION(BlueprintCallable, Category = Effect)
		void Reset();

	/** Root component with no other function */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Interaction)
		UBoxComponent* mRootComponent;

	/** Light mesh */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh)
		USkeletalMeshComponent* mLightMesh;

	UMaterialInstanceDynamic* mLightMaterial;

	/** Populate this with materials corresponding to numbers */
	UPROPERTY(EditAnywhere, Category = Material)
		TArray<UTexture2D*> mLightTextures;
};
