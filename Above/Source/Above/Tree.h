// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Tree.generated.h"

UCLASS()
class ABOVE_API ATree : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATree();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION(BlueprintCallable, Category = Update)
	void UpdateTree(int32 value);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Emmisive)
		TArray<UTexture2D*> EmissiveTex;
private:
	UMaterialInstanceDynamic* mTreeMatInst;
	UStaticMeshComponent* mTreeMesh;
};
