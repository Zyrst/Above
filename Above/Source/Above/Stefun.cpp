// Fill out your copyright notice in the Description page of Project Settings.

#include "Above.h"
#include "Stefun.h"
#include "AboveGameMode.h"
#include "Door.h"

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
	mHoldTrigger = nullptr;

	GetCharacterMovement()->MaxWalkSpeedCrouched = mCrouchSpeed;
	mIsPaused = false;

	mInteractButtonIsPressed = false;
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
	GetCharacterMovement()->ApplyAccumulatedForces(DeltaTime);
	HoverOverObject();
}

// Called to bind functionality to input
void AStefun::SetupPlayerInputComponent(class UInputComponent* InputComponent){
	InputComponent->BindAxis("MoveForward",this, &AStefun::MoveForward);
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
	InputComponent->BindAction("Interact", IE_Pressed, this, &AStefun::InteractButtonPressed);
	InputComponent->BindAction("Interact", IE_Released, this, &AStefun::InteractButtonRelesased);
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

		if (currentSpeed < mWalkSpeed){
			currentSpeed += 10;
			GetCharacterMovement()->MaxWalkSpeed = currentSpeed;
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("CurrentSpeed %f"), currentSpeed));
		}
		
		AddMovementInput(direction, val);
		if (val > 0)
			forward = true;
		else
			forward = false;
	}
	if (val == 0.0f){

		FRotator rotation = Controller->GetControlRotation();
		if (GetCharacterMovement()->IsMovingOnGround() || GetCharacterMovement()->IsFalling()){
			rotation.Pitch = 0.0f;
		}
		//Add movement in that direction
		const FVector direction = FRotationMatrix(rotation).GetScaledAxis(EAxis::X);

		if (currentSpeed > 0.0f){
			currentSpeed -= 10.0f;
			GetCharacterMovement()->MaxWalkSpeed = currentSpeed;
			float value = currentSpeed * 0.1;
			if (forward)
				AddMovementInput(direction, 1);
			else 
				AddMovementInput(direction, -1);
		}
		
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("CurrentSpeed %f"), currentSpeed));
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
	AAboveGameMode* mode;
	mode = (AAboveGameMode*)GetWorld()->GetAuthGameMode();
	float FoV = mode->getZoomFoV();
	mFaceCam->FieldOfView = FoV;
}

void AStefun::UnSetZoom(){
	AAboveGameMode* mode; 
	mode = (AAboveGameMode*)GetWorld()->GetAuthGameMode();
	float FoV = mode->getStandardFoV();
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("FoV value %f"),FoV));
	mFaceCam->FieldOfView = FoV;
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

void AStefun::Interact(){
	if (mTrigger != nullptr){
		mTrigger->SetPointerTarget(mTargetPos);
		mTrigger->Interact();
	}

	else{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("No trigger selected"));
	}
}

void AStefun::HoverOverObject() {
	// Setup trace
	FHitResult traceHitResult;
	TObjectIterator<AStefun> Player;
	FVector traceStart = mFaceCam->GetComponentLocation();
	FVector traceEnd = traceStart + mFaceCam->GetComponentRotation().Vector() * 128;
	ECollisionChannel collisionChannel = ECC_Pawn;
	FCollisionQueryParams traceParamaters(FName(TEXT("InteractionTrace")), true, this);

	// Trace
	Player->GetWorld()->LineTraceSingle(traceHitResult, traceStart, traceEnd, collisionChannel, traceParamaters);

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Trigger: %s"), *mTargetPos.ToString()));

	// Hit something
	if (traceHitResult.bBlockingHit == true) {
		mTargetPos = traceHitResult.ImpactPoint;

		AInteractionTrigger* tmpTrigger = Cast<AInteractionTrigger>(traceHitResult.GetActor());

		// Hit a trigger
		if (tmpTrigger != nullptr) {
			// No selected trigger
			if (mTrigger == nullptr) {
				mTrigger = tmpTrigger;
				mTrigger->StartHover();

				// Assign held trigger
				if (mHoldTrigger == nullptr) {
					mHoldTrigger = mTrigger;
				}

				// Interact if button was pressed before hovering over trigger
				if (mInteractButtonIsPressed == true) {
					Interact();
				}
			}

			// Selected trigger
			else {
				// New trigger is different
				if (mTrigger != tmpTrigger) {
					mTrigger->EndHover();
					mTrigger = tmpTrigger;
					mTrigger->StartHover();

					// Interact if button was pressed before hovering over trigger
					if (mInteractButtonIsPressed == true) {
						Interact();
					}
				}

				// Assign held trigger
				if (mHoldTrigger == nullptr) {
					mHoldTrigger = mTrigger;
				}
			}
		}

		// Hit something other than a trigger
		else {
			if (mTrigger != nullptr) {
				mTrigger->EndHover();
				mTrigger = nullptr;
			}
		}
	}

	// Hit nothing
	else {
		mTargetPos = traceEnd;

		if (mTrigger != nullptr) {
			mTrigger->EndHover();
			mTrigger = nullptr;
		}
	}
}

void AStefun::InteractButtonPressed() {
	mInteractButtonIsPressed = true;
	Interact();
}

void AStefun::InteractButtonRelesased() {
	mInteractButtonIsPressed = false;
	if (mHoldTrigger != nullptr) {
		mHoldTrigger->EndHold();
		mHoldTrigger = nullptr;
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