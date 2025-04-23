// Copyright (c) 2025, Balbjorn Bran. All rights reserved.


#include "TfppSystem/Public/TfppCharacter.h"

#include "TfppCharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Math/UnrealMathUtility.h"
#include "GameFramework/PlayerController.h"

// Sets default values
ATfppCharacter::ATfppCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UTfppCharacterMovementComponent>(
		  ATfppCharacter::CharacterMovementComponentName)), PlayerController(nullptr), AdjustedViewRotation()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TfppCharacterMovement = Cast<UTfppCharacterMovementComponent>(ACharacter::GetMovementComponent());
}

void ATfppCharacter::SetPace(EMovementPaces NewPace)
{
	if (TfppCharacterMovement)
	{
		TfppCharacterMovement->SetPace(NewPace);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Something is wrong, TfppCharacterMovement is not valid."));
	}
}

void ATfppCharacter::SetStance(ECharacterStances NewStance)
{
	if (!TfppCharacterMovement)
	{
		return;
	}
	
	ECharacterStances CrouchStance = TfppCharacterMovement->CrouchingStance;
	ECharacterStances StandStance = TfppCharacterMovement->StandingStance;
	
	if (NewStance == CrouchStance && CanCrouch() && TfppCharacterMovement->GetCurrentStance() != CrouchStance)
	{
		Crouch();
	}

	if (NewStance != GetCurrentStance() && TfppCharacterMovement->GetCurrentStance() == CrouchStance && NewStance == StandStance)
	{
		UnCrouch();
	}
	
	TfppCharacterMovement->SetStance(NewStance);
}

FVector2D ATfppCharacter::GetMovingDirection() const
{
	FVector Velocity = GetCharacterMovement()->Velocity;
	FVector Local = GetActorRotation().UnrotateVector(Velocity);
	FVector2D Dir2D = FVector2D(Local.X, Local.Y).GetSafeNormal();

	int32 X = FMath::IsNearlyZero(Dir2D.X, 0.1f) ? 0 : (Dir2D.X > 0 ? 1 : -1);
	int32 Y = FMath::IsNearlyZero(Dir2D.Y, 0.1f) ? 0 : (Dir2D.Y > 0 ? 1 : -1);
	FVector2D InputLikeDir = FVector2D(X, Y);
	return InputLikeDir;
}

void ATfppCharacter::CalculateViewRotation()
{
	AdjustedViewRotation = FRotator(ProcessPitch(), ProcessYaw(), 0.f);
}

float ATfppCharacter::ProcessPitch() const
{
	return FMath::ClampAngle(GetControlRotation().Pitch, PitchRange.X, PitchRange.Y);
}

float ATfppCharacter::ProcessYaw() const
{
	return FMath::Fmod(GetControlRotation().Yaw - GetActorRotation().Yaw + 180.f, 360.f) - 180.f;
}

// Called when the game starts or when spawned
void ATfppCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Get a reference to the player controller
	PlayerController = Cast<APlayerController>(GetController());
	
}


// Called every frame
void ATfppCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerController)
	{
		CalculateViewRotation();
	}
	
}

// Called to bind functionality to input
void ATfppCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

