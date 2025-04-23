// Copyright (c) 2025, Balbjorn Bran. All rights reserved.


#include "TfppCharacterMovementComponent.h"
#include "TfppLog.h"

// Sets default values for this component's properties
UTfppCharacterMovementComponent::UTfppCharacterMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	bUseControllerDesiredRotation = true;
	RotationRate = FRotator(0.0f, -1.0f, 0.0f);
	PacesAngleRestriction.Empty();
	InitializeDefaultPacesSpeed();
}

void UTfppCharacterMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	InitializeTfppComponent();
}

void UTfppCharacterMovementComponent::InitializeTfppComponent()
{
	MaxWalkSpeed = PaceMaxSpeed[DefaultPace];
	MaxWalkSpeedCrouched = PaceMaxSpeed[DefaultPace] * StanceSpeedMultiplier[CrouchingStance];
	CurrentPace = DefaultPace;
	OnPaceChanged.Broadcast(DefaultPace, CurrentPace);
	OnStanceChanged.Broadcast(ECharacterStances::StanceType0, CurrentStance);
	DEV_LOG_ARGS(Verbose, "Initialized Pace to %s.", *UEnum::GetValueAsString(CurrentPace));
}

void UTfppCharacterMovementComponent::SetPace(EMovementPaces NewPace)
{

	if (NewPace != CurrentPace && PaceMaxSpeed.Contains(NewPace))
	{
		DEV_LOG_ARGS(Verbose, "Changing Pace to %s.", *UEnum::GetValueAsString(NewPace));
		MaxWalkSpeed = PaceMaxSpeed[NewPace];
		MaxWalkSpeedCrouched = PaceMaxSpeed[NewPace] * StanceSpeedMultiplier[CrouchingStance];
		const EMovementPaces OldPace = CurrentPace;
		CurrentPace = NewPace;
		OnPaceChanged.Broadcast(OldPace, CurrentPace);
	}
}

void UTfppCharacterMovementComponent::SetStance(ECharacterStances NewStance)
{
	if (NewStance == CurrentStance)
	{
		return;
	}
	const ECharacterStances OldStance = CurrentStance;
	CurrentStance = NewStance;
	OnStanceChanged.Broadcast(OldStance, NewStance);
}

void UTfppCharacterMovementComponent::InitializeDefaultPacesSpeed()
{
	PaceMaxSpeed.Add(EMovementPaces::PaceType0, 200.0f);
	PaceMaxSpeed.Add(EMovementPaces::PaceType1, 400.0f);
	PaceMaxSpeed.Add(EMovementPaces::PaceType2, 650.0f);
	StanceSpeedMultiplier.Add(ECharacterStances::StanceType0, 1.0f);
	StanceSpeedMultiplier.Add(ECharacterStances::StanceType1, 0.5f);
	MaxWalkSpeed = PaceMaxSpeed[DefaultPace];
	MaxWalkSpeedCrouched = PaceMaxSpeed[DefaultPace] * StanceSpeedMultiplier[ECharacterStances::StanceType1];
}

bool UTfppCharacterMovementComponent::IsPaceAllowedOnDirectionAngle(EMovementPaces MovementPace) const
{
	// Retrieve the forward direction of the controller and velocity direction
	FVector ControllerForward = PawnOwner->Controller->GetControlRotation().Vector().GetSafeNormal2D();
	FVector SafeVelocity = PawnOwner->GetVelocity().GetSafeNormal2D();

	// Calculate the angle between forward direction and velocity
	float DotProduct = FVector::DotProduct(ControllerForward, SafeVelocity);
	float AngleDegrees = FMath::RadiansToDegrees(FMath::Acos(DotProduct));
	
	// Check if there are restrictions defined for the current pace
	if (PacesAngleRestriction.Contains(MovementPace))
	{
		// Retrieve the allowed angle range for the current pace
		FFloatRange AllowedRange = PacesAngleRestriction[MovementPace];
        
		// Check if the angle falls within the allowed range
		if (AngleDegrees >= AllowedRange.GetLowerBoundValue() && AngleDegrees <= AllowedRange.GetUpperBoundValue())
		{
			return true; // Angle is within restriction
		}
		return false; // Angle is outside restriction
	}
	// If no restrictions are defined for the current pace, allow it by default
	return true;

}








