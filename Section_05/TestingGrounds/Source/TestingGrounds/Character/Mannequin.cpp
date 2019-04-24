// Chris Nickerson -- TestingGrounds -- Unreal C++ Development


#include "Mannequin.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "../Weapons/Gun.h"

// Sets default values
AMannequin::AMannequin()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // Create a CameraComponent
    FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
    FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
    FirstPersonCameraComponent->RelativeLocation = FVector(-39.56f, 1.75f, 64.0f); //Position the camera
    FirstPersonCameraComponent->bUsePawnControlRotation = true;

    // Create a mesh component that will be used when being viewed from a '1st person" view (when controlling this pawn)
    Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
    Mesh1P->SetOnlyOwnerSee(true);
    Mesh1P->SetupAttachment(FirstPersonCameraComponent);
    Mesh1P->bCastDynamicShadow = false;
    Mesh1P->CastShadow = false;
    Mesh1P->RelativeRotation = FRotator(1.9f, -19.19f, 5.2f);
    Mesh1P->RelativeLocation = FVector(-0.5f, -4.4f, -155.7f);

}

// Called when the game starts or when spawned
void AMannequin::BeginPlay()
{
	Super::BeginPlay();
	if(!ensure(GunBlueprint))
    {
        UE_LOG(LogTemp, Error, TEXT("Gun Blueprint missing from Mannequin: %s"),*GetName());
        return;
    }
    Gun = GetWorld()->SpawnActor<AGun>(GunBlueprint);
    if(IsPlayerControlled())
    {
        Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint")); // Attach gun mesh component to the GripPoint of the Mesh1P
    }
    else
    {
        Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint")); // Attach gun mesh component to the GripPoint of the 3rd person Mesh
        
    }
    Gun->AnimInstance3P = GetMesh()->GetAnimInstance();
    Gun->AnimInstance1P = Mesh1P->GetAnimInstance();

    if(InputComponent != nullptr)
    {
        InputComponent->BindAction("Fire", IE_Pressed, this, &AMannequin::PullTrigger);
    }
}

// Called every frame
void AMannequin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMannequin::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMannequin::PullTrigger()
{
    Gun->OnFire();
}

void AMannequin::UnPossessed()
{
    Super::UnPossessed();
    if(Gun != nullptr)
    {
        Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint")); // Attach gun mesh component to the GripPoint of the 3rd person Mesh
    }
}