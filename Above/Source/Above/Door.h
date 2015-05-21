// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Door.generated.h"

UCLASS()
class ABOVE_API ADoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	//Enables and disables rotation
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Defaults)
		float mCollisionRadius = 40;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
		UStaticMeshComponent* mDoorMesh;

	TArray<UMaterialInstanceDynamic*> mMaterialArray;

	UFUNCTION(BlueprintImplementableEvent, Category = Material)
		void LightMaterial(int32 index);

	UFUNCTION(BlueprintImplementableEvent, Category = Material)
		void UnLightMaterial(int32 index);
};
