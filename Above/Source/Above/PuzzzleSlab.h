// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "PuzzzleSlab.generated.h"

UCLASS()
class ABOVE_API APuzzzleSlab : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APuzzzleSlab(const FObjectInitializer& ObjectInitializer);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	/** Root component with no other function */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Interaction)
		UBoxComponent* mRootComponent;

	/** Overlapping-trigger */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Trigger)
		UBoxComponent* mOverlapBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
		UStaticMeshComponent* mSlabMesh;

	/** Trigger on begin overlap */
	UFUNCTION()
		void BeginOverlapOnBox(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	/** Called when stepped on */
	UFUNCTION(BlueprintNativeEvent, Category = Overlap)
		void SteppedOnSlab();

	/** Turns on light effects */
	UFUNCTION(BlueprintCallable, Category = Effect)
		void LightUpSlab();

	/** Resets light effects */
	UFUNCTION(BlueprintCallable, Category = Effect)
		void ResetSlab();

	/** Is correct slab open variable */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Path)
		bool mIsCorrectSlab;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Path)
		bool mStartSlab;


	UMaterialInstanceDynamic* mSlabMaterial;

	/** Populate this with materials corresponding to numbers */
	UPROPERTY(EditAnywhere, Category = Material)
		TArray<UTexture2D*> mSlabTextures;

	UPROPERTY(EditAnywhere, Category = Slabs)
		TArray<UStaticMesh*> mSlabMeshes;

	UFUNCTION(BlueprintCallable, Category = Index)
		int32 GetIndex();

	UFUNCTION(BlueprintCallable, Category = Index)
		void SetIndex(int32 index);

private:
	int32 mIndex;
};
