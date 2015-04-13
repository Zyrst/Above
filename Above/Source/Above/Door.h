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

	/**Activate the door rotation*/
	UFUNCTION(BlueprintCallable, Category = Activation)
		void Activate();

	void Reset();

	/**The degree which it shall be rotated, normal is 90*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Rotation)
		float RotationDegree;
//private:
	//Enables and disables rotation
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Animation)
	bool mShouldRotate = false;
	//Arc lenght that gets calculated
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Animation)
	float mTarget; 
	//Calculate the "base" which is used to calculate the arc lenght
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Animation)
	float mBase;
	//Current arc lenght
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Animation)
	float mCurrent = 0;
	//Door mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Animation)
	UStaticMesh* mDoorMesh;
	//Door mesh component
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Animation)
	UStaticMeshComponent* mDoor;
};
