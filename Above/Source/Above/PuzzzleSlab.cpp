// Fill out your copyright notice in the Description page of Project Settings.

#include "Above.h"
#include "PuzzzleSlab.h"


// Sets default values
APuzzzleSlab::APuzzzleSlab(const FObjectInitializer& ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mRootComponent = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("RootCompenent"));
	RootComponent = mRootComponent;

	mOverlapBox = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("CollisionBox"));
	mOverlapBox->AttachParent = mRootComponent;
	
	//mSlabMesh = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Slab"));
	//mSlabMesh->AttachParent = mRootComponent;
	
	mOverlapBox->OnComponentBeginOverlap.AddDynamic(this, &APuzzzleSlab::BeginOverlapOnBox);
	//mSlabMat = ObjectInitializer.CreateDefaultSubobject <UMaterialInstance>(this, TEXT("MaterialInstanceConstant'/Game/Materials/TextureChange_Inst.TextureChange_Inst'"));
	ConstructorHelpers::FObjectFinder<UMaterial> Material(TEXT("Material'/Game/Materials/TextureChange.TextureChange'"));
	if (Material.Object != NULL) {
		mSlabMat = (UMaterial*)Material.Object;
	}
}

// Called when the game starts or when spawned
void APuzzzleSlab::BeginPlay()
{
	Super::BeginPlay();
	UMaterialInstanceDynamic* mSlabMatInst = UMaterialInstanceDynamic::Create(mSlabMat, this);
	//mSlabMesh->SetMaterial(0, mSlabMatInst);

	mSlabMaterial = mSlabMesh->CreateAndSetMaterialInstanceDynamic(0);

	if (mSlabTextures.Num() == 2) {
		mSlabMaterial->SetTextureParameterValue("BaseTexture", mSlabTextures[0]);
	}
	//Make stream with random numbers depedning on their location as a seed
	FRandomStream rng = FRandomStream(GetTransform().GetLocation().X + GetTransform().GetLocation().Y);
	int32 rand = rng.RandHelper(3);
	//Choose which slab it will take one
	if (!(rand > mSlabMeshes.Num()) && mSlabMesh != nullptr){
		mSlabMesh->SetStaticMesh(mSlabMeshes[rand]);
	}
	rand = rng.RandHelper(4);
	//Random rotation
	if (rand != 0){
		mSlabMesh->AddLocalRotation(FRotator(0, (90 * rand), 0));
	}
}

// Called every frame
void APuzzzleSlab::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

void APuzzzleSlab::BeginOverlapOnBox(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	SteppedOnSlab();
}

void APuzzzleSlab::LightUpSlab() {
	if (mSlabTextures.Num() > 0) {
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, TEXT("Slab is lit, trust me brah"));
		mSlabMaterial->SetTextureParameterValue("BaseTexture", mSlabTextures[1]);
	}
}

void APuzzzleSlab::ResetSlab() {
	if (mSlabTextures.Num() == 2) {
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, TEXT("Slab reset"));
		mSlabMaterial->SetTextureParameterValue("BaseTexture", mSlabTextures[0]);
	}
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, TEXT("Slab reset"));
}

int32 APuzzzleSlab::GetIndex(){
	return mIndex;
}

void APuzzzleSlab::SetIndex(int32 index){
	mIndex = index;
}