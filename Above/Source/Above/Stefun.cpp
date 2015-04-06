// Fill out your copyright notice in the Description page of Project Settings.

#include "Above.h"
#include "Stefun.h"
#include "AboveGameMode.h"

// Sets default values
AStefun::AStefun(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer){
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	mFaceCam = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>(this, TEXT("FaceCam"));
	mFaceCam->AttachParent = GetCapsuleComponent();
	mFaceCam->Activate();
	mFaceCam->bUsePawnControlRotation = true;
	GetCharacterMovement()->MaxWalkSpeedCrouched = mCrouchSpeed;
	mIsPaused = false;
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
	/*if (GetCharacterMovement()->IsFalling()){
		if (mTestFall == 0){
			float time = GetWorld()->TimeSeconds;
			auto sumthing = WhileFalling(time);
			mTestFall =  sumthing.Run();
			//fall->Run();
				//WhileFalling(GetWorld()->TimeSeconds);
			
		}
		else
			mTestFall++;
	}*/
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
	//Be able to unpause
	InputComponent->BindAction("Pause", IE_Pressed, this, &AStefun::TogglePause).bExecuteWhenPaused = true;

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
	GetCharacterMovement()->MaxWalkSpeed = mSprintSpeed;
}

void AStefun::DisableSprint(){
	GetCharacterMovement()->MaxWalkSpeed = mWalkSpeed;
	
}

void AStefun::ToggleCrouch(){
	if (CanCrouch() == true){
		Crouch();
	}
	else{
		UnCrouch();
	}
}

void AStefun::TogglePause(){
	
	if (mIsPaused == false){
		UGameplayStatics::SetGamePaused(GetWorld(), true);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Paused!"));
		mIsPaused = true;
	}
	else if (mIsPaused == true){
		UGameplayStatics::SetGamePaused(GetWorld(), false);
		mIsPaused = false;
	}
}