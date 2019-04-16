// Chris Nickerson -- TestingGrounds -- Unreal C++ Development

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Mannequin.generated.h"

class AGun;
class USkeletalMeshComponent;
class UCameraComponent;

UCLASS()
class TESTINGGROUNDS_API AMannequin : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMannequin();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    virtual void UnPossessed() override;

    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    TSubclassOf<AGun> GunBlueprint;

    UFUNCTION(BlueprintCallable, Category = "Weapon")
    void PullTrigger();    
private:
    // First Person Mesh
    UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
    USkeletalMeshComponent * Mesh1P;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
    UCameraComponent * FirstPersonCameraComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
    AGun * Gun;
};
