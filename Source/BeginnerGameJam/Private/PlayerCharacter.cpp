// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if ( PlayerController == Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(PlayerMappingContext, 0);
		}

	}
	
	CameraController = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);

	CameraController->ViewPitchMax = MaxPitch;
	CameraController->ViewPitchMin = MinPitch;

	JumpCount = 0;
	

}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void APlayerCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisValue = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisValue.X);
		AddControllerPitchInput(LookAxisValue.Y);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, TEXT("ControllerNotValid"));
	}
}

void APlayerCharacter::StartSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
}

void APlayerCharacter::StopSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = DefaultSpeed;
}


void APlayerCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	JumpCount = 0;
}

void APlayerCharacter::FlyUp()
{
	LaunchCharacter(FVector(0, 0, 300), false, true);
}

void APlayerCharacter::FlyDown()
{
	LaunchCharacter(FVector(0, 0, -300), false, true);
}

void APlayerCharacter::Stable(FVector StopMovement)
{
	GetCharacterMovement()->Velocity = StopMovement;
}




void APlayerCharacter::InteractTrace()
{
	FVector Loc;
	FRotator Rot;
	GetController()->GetPlayerViewPoint(Loc, Rot);

	FVector Start = Loc;
	FVector End = Start + (Rot.Vector() * TraceDistance);

	FHitResult HitResult;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);


	const bool DidHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_Visibility, Params);

	if (DidHit)
	{
		if (HitResult.GetActor()->Implements<UInteractInterface>())
		{
			IInteractInterface::Execute_Interact(HitResult.GetActor());
		}
	}
}

void APlayerCharacter::Expload()
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionVFX, GetActorLocation(), GetActorRotation());
	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), ExplosionSFX, GetActorLocation(), GetActorRotation(), 0.5, 1, 0.0f, SA_Explosion);
	

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);

	TArray<FHitResult> HitArray;

	const bool Hit = UKismetSystemLibrary::SphereTraceMulti(GetWorld(), GetActorLocation(), GetActorLocation(), 300,
	UEngineTypes::ConvertToTraceType(ECC_Camera), false, ActorsToIgnore, EDrawDebugTrace::None, HitArray, true);

	if (Hit)
	{
		for (const FHitResult HitResult : HitArray)
		{
			if (HitResult.GetActor()->ActorHasTag("Destroyable"))
			{
				HitResult.GetActor()->Destroy();
				
			}
		}
	}
	Destroy();

	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
		EnhancedInputComponent->BindAction(IA_Look, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);

		EnhancedInputComponent->BindAction(IA_Sprint, ETriggerEvent::Triggered, this, &APlayerCharacter::StartSprint);
		EnhancedInputComponent->BindAction(IA_Sprint, ETriggerEvent::Completed, this, &APlayerCharacter::StopSprint);

		EnhancedInputComponent->BindAction(IA_Interact, ETriggerEvent::Triggered, this, &APlayerCharacter::InteractTrace);

		// BasicCharacter

		EnhancedInputComponent->BindAction(IA_Expload, ETriggerEvent::Triggered, this, &APlayerCharacter::Expload);


		// All Characters


		//Drone

		EnhancedInputComponent->BindAction(IA_Drone_FlyUp, ETriggerEvent::Triggered, this, &APlayerCharacter::FlyUp);
		EnhancedInputComponent->BindAction(IA_Drone_FlyDown, ETriggerEvent::Triggered, this, &APlayerCharacter::FlyDown);

	}

}

