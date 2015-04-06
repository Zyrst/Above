// Fill out your copyright notice in the Description page of Project Settings.

#include "Above.h"
#include "Stefun.h"
#include <time.h>
#include <stdio.h>


// Sets default values
AStefun::AStefun(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer){
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	mFaceCam = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>(this, TEXT("FaceCam"));
	mFaceCam->AttachParent = GetCapsuleComponent();
	mFaceCam->Activate();
	mFaceCam->bUsePawnControlRotation = true;

	mTrigger = nullptr;
}

// Called when the game starts or when spawned
void AStefun::BeginPlay()
{
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;
	DisableSprint();
	Super::BeginPlay();
}

// Called every frame
void AStefun::Tick( float DeltaTime ){
	Super::Tick( DeltaTime );

	HoverOverObject();
}

// Called to bind functionality to input
void AStefun::SetupPlayerInputComponent(class UInputComponent* InputComponent){
	InputComponent->BindAxis("MoveForward", this, &AStefun::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AStefun::MoveRight);
	InputComponent->BindAxis("Turn", this, &AStefun::AddControllerYawInput);
	InputComponent->BindAxis("LookUp", this, &AStefun::AddControllerPitchInput);
	InputComponent->BindAction("Jump", IE_Pressed, this, &AStefun::OnStartJump);
	InputComponent->BindAction("Jump", IE_Released, this, &AStefun::OnStopJump);
	InputComponent->BindAction("Zoom", IE_Pressed, this, &AStefun::SetZoom);
	InputComponent->BindAction("Zoom", IE_Released, this, &AStefun::UnSetZoom);
	InputComponent->BindAction("Sprint", IE_Pressed, this, &AStefun::EnableSprint);
	InputComponent->BindAction("Sprint", IE_Released, this, &AStefun::DisableSprint);
	InputComponent->BindAction("Crouch", IE_Pressed, this, &AStefun::ToggleCrouch);
	InputComponent->BindAction("Interact", IE_Pressed, this, &AStefun::Interact);

}

void AStefun::MoveForward(float val){
	if ((Controller != NULL) && (val != 0.0f)){
		//Find which way is forward
		FRotator rotation = Controller->GetControlRotation();
		if (GetCharacterMovement()->IsMovingOnGround() || GetCharacterMovement()->IsFalling()){
			rotation.Pitch = 0.0f;
		}
		//Add movement in that direction
		const FVector direction = FRotationMatrix(rotation).GetScaledAxis(EAxis::X);
		AddMovementInput(direction, val);
	}
}

void AStefun::MoveRight(float val){
	if ((Controller != NULL) && (val != 0.0f)){
		const FRotator rotation = Controller->GetControlRotation();
		const FVector direction = FRotationMatrix(rotation).GetScaledAxis(EAxis::Y);

		AddMovementInput(direction, val);
	}
}

void AStefun::OnStartJump(){
	if (GetCharacterMovement()->IsMovingOnGround()){ 
		bPressedJump = true; 
	}
	float time = GetWorld()->GetTimeSeconds();
	
}

void AStefun::OnStopJump(){
	bPressedJump = false;
}

void AStefun::SetZoom(){
	mFaceCam->FieldOfView = 40;
}

void AStefun::UnSetZoom(){
	mFaceCam->FieldOfView = 90;
}

void AStefun::EnableSprint(){
	CharacterMovement->MaxWalkSpeed = mSprintSpeed;
}

void AStefun::DisableSprint(){
	CharacterMovement->MaxWalkSpeed = mWalkSpeed;
}

void AStefun::ToggleCrouch(){
	if (CanCrouch() == true){
		Crouch();
		CharacterMovement->MaxWalkSpeedCrouched = mCrouchSpeed;
	}
	else{
		UnCrouch();
	}
}

void AStefun::Interact(){
	if (mTrigger != nullptr){
		mTrigger->Interact();
	}

	else{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("No trigger selected"));
	}
}

void AStefun::HoverOverObject(){
	// Setup trace
	FHitResult traceHitResult;
	TObjectIterator<AStefun> Player;
	FVector traceStart = mFaceCam->GetComponentLocation();
	FVector traceEnd = traceStart + mFaceCam->GetComponentRotation().Vector() * 128;
	ECollisionChannel collisionChannel = ECC_Pawn;
	FCollisionQueryParams traceParamaters(FName(TEXT("InteractionTrace")), true, this);

	// Trace
	Player->GetWorld()->LineTraceSingle(traceHitResult, traceStart, traceEnd, collisionChannel, traceParamaters);

	// Hit something
	if (traceHitResult.bBlockingHit == true){
		AInteractionTrigger* tmpTrigger = Cast<AInteractionTrigger>(traceHitResult.GetActor());

		if (tmpTrigger != nullptr) {
			if (mTrigger == nullptr) {
				mTrigger = tmpTrigger;
				mTrigger->StartHover();
			}

			else {
				if (mTrigger != tmpTrigger) {
					mTrigger->EndHover();
					mTrigger = tmpTrigger;
					mTrigger->StartHover();
				}
			}
		}
	}

	// Hit nothing
	else{
		if (mTrigger != nullptr) {
			mTrigger->EndHover();
			mTrigger = nullptr;
		}
	}
}