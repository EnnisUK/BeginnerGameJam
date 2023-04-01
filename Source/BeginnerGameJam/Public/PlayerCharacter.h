// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Interfaces/InteractInterface.h"
#include "PlayerCharacter.generated.h"




class UInputAction;

UCLASS()
class BEGINNERGAMEJAM_API APlayerCharacter : public ACharacter, public IInteractInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
		class UInputMappingContext* PlayerMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		UInputAction* IA_Move;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		UInputAction* IA_Look;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		UInputAction* IA_Jump;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		UInputAction* IA_Sprint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		UInputAction* IA_Interact;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		UInputAction* IA_Expload;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		UInputAction* IA_PossessMainCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		UInputAction* IA_SmallRobot_Grab;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		UInputAction* IA_Drone_FlyUp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		UInputAction* IA_Drone_FlyDown;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		UInputAction* IA_Drone_Laser;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		UInputAction* IA_Talk;

	APlayerCameraManager* CameraController;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Player Movement Functions

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void StartSprint();
	void StopSprint();

	UPROPERTY()
	bool Jumping;

	virtual void Landed(const FHitResult& Hit) override;

	UPROPERTY()
	int JumpCount;

	// Drone

	void FlyUp();
	void FlyDown();

	UFUNCTION(BlueprintCallable)
	void Stable(FVector StopMovement);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float LaserDistance;

	


	//Player Interact Function

	void InteractTrace();


	// Basic Character Functions

	void Expload();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	//Camera Variables

	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	float MaxPitch;

	UPROPERTY(EditDefaultsOnly, Category = "Camera")
		float MinPitch;

	// Character Variables

	UPROPERTY(EditDefaultsOnly, Category = "Player")
		float SprintSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "Player")
		float DefaultSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,Category = "Player")
		float TraceDistance;

	// Basic Character Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
		class UParticleSystem* ExplosionVFX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SFX")
		class USoundBase* ExplosionSFX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SFX")
		class USoundAttenuation* SA_Explosion;

	APlayerController* PlayerController;
};
