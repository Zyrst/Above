// Fill out your copyright notice in the Description page of Project Settings.

#include "Above.h"
#include "Tree.h"


// Sets default values
ATree::ATree()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATree::BeginPlay()
{
	Super::BeginPlay();
	TArray<UStaticMeshComponent*> Components;
	this->GetComponents<UStaticMeshComponent>(Components);
	for (int32 i = 0; i < Components.Num(); i++){
		UStaticMeshComponent* mesh = Components[i];
		if (mesh->GetName() == "Island_Testrun_polySurface2"){
			mTreeMesh = Components[i];
		}
	}
	if (mTreeMesh != nullptr){
		mTreeMatInst = mTreeMesh->CreateAndSetMaterialInstanceDynamic(0);
	}
}

// Called every frame
void ATree::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ATree::UpdateTree(int32 value){
	switch (value){
	case 0:
		mTreeMatInst->SetTextureParameterValue("Emmisive_0", EmmisiveTex[value]);
		break;
	case 1:
		mTreeMatInst->SetTextureParameterValue("Emmisive_1", EmmisiveTex[value]);
		break;
	case 2:
		mTreeMatInst->SetTextureParameterValue("Emmisive_2", EmmisiveTex[value]);
		break;
	}
}