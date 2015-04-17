// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "SoundParameterTrigger.generated.h"

UCLASS()
class ABOVE_API ASoundParameterTrigger : public AActor
{
	GENERATED_BODY()
	
public:	

	UENUM(BlueprintType)
	enum class ColliderType : uint8{
		Box,
		Spehere,
	};

	// Sets default values for this actor's properties
	ASoundParameterTrigger(const FObjectInitializer& ObjectInitializer);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	/** Name of parameter to set value on when entering trigger */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters")
		FName mEnterParameterName;
	
	/** Value of parameter when entering trigger */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters")
		float mEnterParameterValue;

	/** Name of parameter to set value on when exitting trigger */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters")
		FName mExitParameterName;

	/** Value of parameter when exitting trigger */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters")
		float mExitParameterValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collider")
		ColliderType mColliderType;
};
