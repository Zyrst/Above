// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "StoryBoard.generated.h"

UCLASS()
class ABOVE_API AStoryBoard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStoryBoard();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	void UpdateBoard();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Textures)
		TArray<UTexture2D*> mTexArray;
	
private:
	UMaterialInstanceDynamic* mMat; 
	UStaticMeshComponent* mBoardMesh;
	int32 mProgress;
};
