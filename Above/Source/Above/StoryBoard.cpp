// Fill out your copyright notice in the Description page of Project Settings.

#include "Above.h"
#include "StoryBoard.h"
#include "AboveSettings.h"


// Sets default values
AStoryBoard::AStoryBoard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	mProgress = 0;
}

// Called when the game starts or when spawned
void AStoryBoard::BeginPlay()
{
	Super::BeginPlay();
	TArray<UStaticMeshComponent*> Components;
	this->GetComponents<UStaticMeshComponent>(Components);
	for (int32 i = 0; i < Components.Num(); i++){
		UStaticMeshComponent* mesh = Components[i];
		if (mesh->GetName() == "Board"){
			mBoardMesh = Components[i];
			//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Found Board Mesh"));
		}
	}

	if (mBoardMesh != nullptr){
		mMat = mBoardMesh->CreateAndSetMaterialInstanceDynamic(0);
		mMat->SetTextureParameterValue("Texture1", mBlackTex);
		mMat->SetTextureParameterValue("Texture2", mBlackTex);
		mMat->SetTextureParameterValue("Texture3", mBlackTex);
	}
		

	AAboveSettings* settings = (AAboveSettings*)GetWorld()->GetWorldSettings();
	settings->SetStoryBoard(this);
}

// Called every frame
void AStoryBoard::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AStoryBoard::UpdateBoard(){

	if (mBoardMesh == nullptr)
		return;

	switch(mProgress){
		case 0:
			mMat->SetTextureParameterValue("Texture1", mTexArray[0]);
			break;
		case 1:
			mMat->SetTextureParameterValue("Texture2", mTexArray[1]);
			break;
		case 2:
			mMat->SetTextureParameterValue("Texture3", mTexArray[2]);
			break;
	}
	mProgress++;
}

