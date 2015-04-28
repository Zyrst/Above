// Fill out your copyright notice in the Description page of Project Settings.

#include "Above.h"
#include "Stefun.h"
#include "AboveGameMode.h"
#include "Door.h"

// Sets default values
AStefun::AStefun(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer),
	mEdgeThreshold(20),
	mGapIgnoreSize(60),
	mLeaningOverEdge(false),
	mEdgeLeanAmount(50),
	mLookDownSpeed(0){

 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	mFaceCam = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>(this, TEXT("FaceCam"));
	mFaceCam->AttachParent = GetCapsuleComponent();
	mFaceCam->Activate();
	mFaceCam->bUsePawnControlRotation = true;

	mTrigger = nullptr;
	mHoldTrigger = nullptr;
	
	
	mIsPaused = false;

	mInteractButtonIsPressed = false;

	FallingTime = 200;
}

// Called when the game starts or when spawned
void AStefun::BeginPlay()
{
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;
	DisableSprint();
	Super::BeginPlay();

	GetCharacterMovement()->MaxWalkSpeedCrouched = mCrouchSpeed;
	mCamDefaultLocation = mCamCurrentLocation = mFaceCam->GetRelativeTransform().GetLocation();

	mController = GetWorld()->GetFirstPlayerController();

}

// Called every frame
void AStefun::Tick( float DeltaTime ){
	Super::Tick( DeltaTime );
	
GetCharacterMovement()->ApplyAccumulatedForces(DeltaTime);
	HoverOverObject();

	// Prevent jumping over edge
	// Uncomment this for only checking when in air. (Does not work with sliding)
	//if (!GetCharacterMovement()->IsMovingOnGround())
	if (currentSpeed > 0) { 
		// Only care about xy speed
		FVector vel = GetCharacterMovement()->Velocity;
		vel.Z = 1;

		vel.X /= mWalkSpeed;
		vel.Y /= mWalkSpeed;

		if (!FindGroundBelow(vel)) {
			GetCharacterMovement()->Velocity.X = 0;
			GetCharacterMovement()->Velocity.Y = 0;
			currentSpeed = 0;
		}
	}


	if (currentSpeed > 0) {
		if (mMoving == false) {
			SoundEventBeginMove();
			mMoving = true;
		}
		
		SoundEventMove();
	}
	else if (currentSpeed == 0 && mMoving) {
		mMoving = false;
		
		SoundEventEndMove();
	}
	
	if (GetCharacterMovement()->IsFalling()){
		mFallingTime++;
		//UE_LOG(LogTemp, Log, TEXT("Falling Count %d"), mFallingTime);
		if (mFallingTime > FallingTime){
			this->TeleportTo(mController->GetSpawnLocation(), FRotator(0, 0, 0), false, true);
			mFallingTime = 0;
		}
	}

	else if (!GetCharacterMovement()->IsFalling() && mFallingTime != 0){
		mFallingTime = 0;
	}


	// Calculate wind level
	if (mWindLevels.Num() > 0) {
		int windA = FMath::Floor(mWindBaseValue);
		int windB = FMath::Ceil(mWindBaseValue + 0.5f);

		if (windB > mWindLevels.Num() - 1) {
			windB = mWindLevels.Num() - 1;
			mCurrentWindValue = 0;
		}

		mCurrentWindValue = FMath::SmoothStep(mWindLevels[windA], mWindLevels[windB], GetTransform().GetLocation().Z);

		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Levels: %i, %i"), windA, windB));
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Step: %f"), mCurrentWindValue + mWindBaseValue + 1));

		if (GetTransform().GetLocation().Z < mWindLevels[windA] && mWindBaseValue >= 1.0f)
			mWindBaseValue--;
		else if (GetTransform().GetLocation().Z > mWindLevels[windB] && mWindBaseValue < mWindLevels.Num() - 2)
			mWindBaseValue++;
	}
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

	// If edge, tilt forward
	if (!FindGroundBelow(GetActorForwardVector() * mEdgeThreshold) && val > 0) {
		AddControllerPitchInput(mLookDownSpeed);

		// Pan camera forward
		mCamCurrentLocation = FMath::Lerp<FVector, float>(mCamCurrentLocation, mCamDefaultLocation + FVector(mEdgeLeanAmount, 0, 0), 0.5f);
		mLeaningOverEdge = true;
		mFaceCam->SetRelativeLocation(mCamCurrentLocation);

		return;
	}

	// If no edge or backing off, return to normal
	if (val > 0 || (mLeaningOverEdge && val < 0)) {
		if (FVector::Dist(mCamCurrentLocation, mCamDefaultLocation) > 0.5f)
			mCamCurrentLocation = FMath::Lerp<FVector, float>(mCamCurrentLocation, mCamDefaultLocation, 0.5f);
		else
			mLeaningOverEdge = false;

		mFaceCam->SetRelativeLocation(mCamCurrentLocation);
	}
	// If backing into an edge, do nothing
	else if (val < 0.0f && !FindGroundBelow(-(GetActorForwardVector() * mEdgeThreshold)))
		return;
	
	if ((Controller != NULL) && (val != 0.0f)){
		//Find which way is forward
		mMoveForward = true;
		FRotator rotation = Controller->GetControlRotation();
		if (GetCharacterMovement()->IsMovingOnGround() || GetCharacterMovement()->IsFalling()){
			rotation.Pitch = 0.0f;
		}
		//Add movement in that direction
		const FVector direction = FRotationMatrix(rotation).GetScaledAxis(EAxis::X);
		//Increase movementspeed
		if (currentSpeed < mWalkSpeed){
			currentSpeed += 10;
			GetCharacterMovement()->MaxWalkSpeed = currentSpeed;
		}
		
		AddMovementInput(direction, val);
		//Know which way we went (forward/back)
		if (val > 0)
			mForward = true;
		else
			mForward = false;
	}
	//We are strafing don't want to decrease speed yet
	if (val == 0 && mStrafing){
		mMoveForward = false;
	}

	//No movement in anyway time to slow down
	else if(val == 0 && !mStrafing){
		
		FRotator rotation = Controller->GetControlRotation();
		if (GetCharacterMovement()->IsMovingOnGround() || GetCharacterMovement()->IsFalling()){
			rotation.Pitch = 0.0f;
		}
		//Add movement in that direction
		const FVector direction = FRotationMatrix(rotation).GetScaledAxis(EAxis::X);
		
		if (currentSpeed > 0.0f && !mStrafing){
			currentSpeed -= 20.0f;
			GetCharacterMovement()->MaxWalkSpeed = currentSpeed;
			if (mForward)
				AddMovementInput(direction, 1);
			else 
				AddMovementInput(direction, -1);
		}
		if (currentSpeed == 0.0f){
			mMoveForward = false;
		}		
	}
	
}


void AStefun::MoveRight(float val){
	// Do now allow strafe when looking over edge or strafing into edge
	if (!FindGroundBelow(GetActorRightVector() * val * mEdgeThreshold) || mLeaningOverEdge)
		return;

	if ((Controller != NULL) && (val != 0.0f)){
		mStrafing = true;
		FRotator rotation = Controller->GetControlRotation();
		if (GetCharacterMovement()->IsMovingOnGround() || GetCharacterMovement()->IsFalling()){
			rotation.Pitch = 0.0f;
		}

		const FVector direction = FRotationMatrix(rotation).GetScaledAxis(EAxis::Y);
		//Movement intesifies
		if (currentSpeed < mWalkSpeed){
			currentSpeed += 10;
			GetCharacterMovement()->MaxWalkSpeed = currentSpeed;
		}

		AddMovementInput(direction, val);
		if (val > 0)
			mRight = true;
		else
			mRight = false;
	}
	//No more strafe but stilling moving forward
	if (val == 0 && mMoveForward){
		mStrafing = false;
	}
	//No movement
	else if (val == 0 && !mMoveForward){

		FRotator rotation = Controller->GetControlRotation();
		const FVector direction = FRotationMatrix(rotation).GetScaledAxis(EAxis::Y);

		if (currentSpeed > 0.0f && !mMoveForward){
			currentSpeed -= 20.0f;
			GetCharacterMovement()->MaxWalkSpeed = currentSpeed;

			if (mRight)
				AddMovementInput(direction, 1);
			else
				AddMovementInput(direction, -1);
				
		}
		//Not moving at all
		if (currentSpeed == 0){
			mStrafing = false;
		}
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

bool AStefun::FindGroundBelow(FVector offset) {
	// Setup trace
	FHitResult traceHitResult;
	TObjectIterator<AStefun> Player;
	FVector traceStart = GetTransform().GetLocation() + offset;
	FVector traceEnd = traceStart + (-GetActorUpVector() * 1000) + offset;
	ECollisionChannel collisionChannel = ECC_WorldStatic;
	FCollisionQueryParams traceParamaters(FName(TEXT("GroundTrace")), true, this);

	// Return trace
	return Player->GetWorld()->LineTraceSingle(traceHitResult, traceStart, traceEnd, collisionChannel, traceParamaters) || FindGroundAround(offset);
}


bool AStefun::FindGroundAround(FVector offset) {
	// Setup trace
	FHitResult traceHitResult;
	TObjectIterator<AStefun> Player;
	FVector traceStart = GetTransform().GetLocation() + offset;
	FVector traceEnd = traceStart + (-GetActorUpVector() * 1000) + offset;
	ECollisionChannel collisionChannel = ECC_WorldStatic;
	FCollisionQueryParams traceParamaters(FName(TEXT("GroundTrace")), true, this);

	bool ret = false;

	float a = (1.22) - offset.HeadingAngle();
	FVector begin = traceStart + FVector(FMath::Sin(a), FMath::Cos(a), 0) * mGapIgnoreSize;
	FVector end = traceEnd + FVector(FMath::Sin(a), FMath::Cos(a), 0) * mGapIgnoreSize;
	ret |= Player->GetWorld()->LineTraceSingle(traceHitResult, begin, end, collisionChannel, traceParamaters);

	a = (1.57) - offset.HeadingAngle();
	begin = traceStart + FVector(FMath::Sin(a), FMath::Cos(a), 0) * mGapIgnoreSize;
	end = traceEnd + FVector(FMath::Sin(a), FMath::Cos(a), 0) * mGapIgnoreSize;
	ret |= Player->GetWorld()->LineTraceSingle(traceHitResult, begin, end, collisionChannel, traceParamaters);

	a = (1.92) - offset.HeadingAngle();
	begin = traceStart + FVector(FMath::Sin(a), FMath::Cos(a), 0) * mGapIgnoreSize;
	end = traceEnd + FVector(FMath::Sin(a), FMath::Cos(a), 0) * mGapIgnoreSize;
	ret |= Player->GetWorld()->LineTraceSingle(traceHitResult, begin, end, collisionChannel, traceParamaters);

	// Return trace
	return	ret;
}



float AStefun::GetMoveSpeed() {
	return currentSpeed / mWalkSpeed * 5;
}

float AStefun::GetCurrentWindValue() {
	return mCurrentWindValue + mWindBaseValue + 1;
}


void AStefun::ChangeParameter(FName parameterName, float parameterValue) {
	mParameterChangeName = parameterName;
	mParameterChangeValue = parameterValue;

	SoundEventParameterChange();
}