// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "StairPlatform.generated.h"

UCLASS()
class ABOVE_API AStairPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStairPlatform();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	virtual void OnConstruction(const FTransform& transform) override;

	/** Position to translate to */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "movement")
		FVector ActivePosition;

	/** Position when not active */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "movement")
		FVector IdlePosition;

	/** Movement speed curve */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "movement")
		UCurveFloat* MovementSpeedCurve;
	
	/** How fast the platform should move */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "movement")
		float MoveSpeed;

	/** Scene component for motion */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "movement")
		USceneComponent* MovementRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "movement")
		AActor* NextPlatform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "movement")
		AActor* PreviousPlatform;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "movement")
		UBoxComponent* NextCollisionBox;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "movement")
		UBoxComponent* PreviousCollisionBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "movement")
		UBoxComponent* MiddleCollisionBox;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "movement")
		FVector NextCollisionBoxPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "movement")
		FVector PreviousCollisionBoxPosition;


	UFUNCTION(BlueprintCallable, Category = "movement")
		void MoveToTarget();

	UFUNCTION(BlueprintCallable, Category = "movement")
		void MoveToIdle();


	UFUNCTION()
		void BeginOverlapNext(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void BeginOverlapPrevious(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void BeginOverlapMiddle(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintImplementableEvent, Category = "movement")
		void OnTargetReached();

	UFUNCTION(BlueprintImplementableEvent, Category = "movement")
		void OnIdleReached();


	UFUNCTION(BlueprintImplementableEvent, Category = "movement")
		void OnHeadingForTarget();

	UFUNCTION(BlueprintImplementableEvent, Category = "movement")
		void OnHeadingForIdle();


private:
	UENUM()
	enum class MoveDirection : uint8 {
		Undef,
		Target, 
		Idle
	};
	MoveDirection mMoveDirection = MoveDirection::Undef;

	bool mMove = false;
	float mMovementTracker = 0;

	FVector mLerpFrom;
};
