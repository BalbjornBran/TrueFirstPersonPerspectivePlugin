// Copyright (c) 2025, Balbjorn Bran. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TfppCharacterMovementComponent.h"
#include "TfppCharacter.generated.h"

class UTfppCharacterMovementComponent;
/** 
 * WIP
 * ATfppCharacter
 * 
 * This class inherits from ACharacter and is used to implement a True First Person Perspective (TFPP) system.
 * In this system, the camera is attached to the player's Mesh, simulating a realistic first-person view.
 * 
 * Currently, this class is a Work In Progress, but it will be responsible for handling all the logic
 * required to make the TFPP system function for the character.
 */
UCLASS(ClassGroup=("True First Person Perspective | Character"))
class TFPPSYSTEM_API ATfppCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Constructor
	explicit ATfppCharacter(const FObjectInitializer& ObjectInitializer);
	
	// ----------------------------------------------------------------------------------------------------------------
	// Begin Overriden Parent Functions
	// ----------------------------------------------------------------------------------------------------------------
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// ----------------------------------------------------------------------------------------------------------------
	// End Overriden Parent Functions
	// ----------------------------------------------------------------------------------------------------------------

	/**
	 * Retrieves the custom character movement component for this True First Person Perspective (TFPP) character.
	 *
	 * This function casts and returns the parent class character movement component as a `UTfppCharacterMovementComponent`.
	 * It provides specialized movement logic for the TFPP system.
	 *
	 * @return A pointer to the `UTfppCharacterMovementComponent` associated with this character.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "TFPP|Movement")
	UTfppCharacterMovementComponent* GetTfppCharacterMovement() const
	{
		return Cast<UTfppCharacterMovementComponent>(Super::GetCharacterMovement());	
	}

	/**
	 * Retrieves the adjusted view rotation of the True First Person Perspective (TFPP) character.
	 *
	 * This function provides the character's calculated adjusted view rotation, which is typically used
	 * to maintain a consistent and realistic perspective in the TFPP system.
	 *
	 * @return The adjusted view rotation as an `FRotator`.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "TFPP|Rotation")
	FRotator GetAdjustedViewRotation()
	{
		return AdjustedViewRotation;
	}

	/**
	 * Sets the current movement pace of the character in the True First Person Perspective (TFPP) system.
	 *
	 * This function updates the character's movement state according to the supplied pace.
	 * If the new pace is "Sprinting," the character must be moving forward for the change to occur.
	 *
	 * @param NewPace The desired movement pace for the character, defined as an `EMovementPaces` enumeration value.
	 */
	UFUNCTION(BlueprintCallable, Category = "TFPP|Paces")
	void SetPace(EMovementPaces NewPace);

	/**
	 * Retrieves the current movement pace of the True First Person Perspective (TFPP) character.
	 *
	 * This function checks the movement state using the associated `UTfppCharacterMovementComponent`
	 * and returns the current pace of the character.
	 *
	 * @return The current movement pace of the character as an `EMovementPaces` enumeration value.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "TFPP|Pace")
	EMovementPaces GetCurrentPace()
	{
		return GetTfppCharacterMovement()->GetCurrentPace();
	}

	/**
	 * Updates the stance of the True First Person Perspective (TFPP) character.
	 *
	 * This function changes the character's stance based on the provided `NewStance` value.
	 * It handles the transition between standing and crouching stances and calls the
	 * respective functions to apply the new stance behavior. If the character is already
	 * in the desired stance, no action is taken.
	 *
	 * @param NewStance The desired stance for the character, represented as an `ECharacterStances` enumeration value.
	 */
	UFUNCTION(BlueprintCallable, Category = "TFPP|Stances")
	void SetStance(ECharacterStances NewStance);

	/**
	 * Retrieves the current stance of the True First Person Perspective (TFPP) character.
	 *
	 * This function accesses the associated `UTfppCharacterMovementComponent` to determine and return
	 * the current stance of the character. Possible stances include Standing, Crouching, and Crawling.
	 *
	 * @return The current stance of the character as an `ECharacterStances` enumeration value.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "TFPP|Stances")
	ECharacterStances GetCurrentStance()
	{
		return GetTfppCharacterMovement()->GetCurrentStance();
	}
	

	/**
	 * AllowedSprintingForwardAngleRange
	 *
	 * Defines the range of angles (in degrees) within which the character is allowed to sprint forward.
	 *
	 * The range is represented as a FVector2D, where the X value specifies the minimum allowed angle and the Y value specifies the maximum allowed angle.
	 * This property can be modified in the editor and accessed via Blueprint for fine-tuning gameplay behavior.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup|Movement")
	FVector2D AllowedSprintingForwardAngleRange = FVector2D(-75.0f, 75.0f);

	/**
	 * Calculates and returns the normalized movement direction of the character in local space.
	 *
	 * This method determines the character's velocity relative to its local orientation
	 * and maps it to a 2D vector representing the movement direction. The resulting vector
	 * is normalized and adjusted to discrete values (-1, 0, 1) for each axis to represent
	 * movement intentions similar to player input.
	 *
	 * @return A 2D normalized vector representing the movement direction in local space,
	 *         with discrete values (-1, 0, 1) for each axis indicating the direction.
	 */
	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "TFPP|Movement")
	FVector2D GetMovingDirection() const;
	
protected:


	//TArray<ECharacterStances> GetPoints();
	
	/**
	 * CameraLocalRotation
	 *
	 * Represents the local rotation of the camera relative to the character.
	 *
	 * This variable is initialized to FRotator::ZeroRotator, ensuring that the camera starts with no
	 * additional local rotation applied. It is likely intended to control or store the current camera
	 * rotation within the True First Person Perspective (TFPP) system.
	 *
	 * Modifying this value affects the orientation of the camera relative to the character's local space.
	 */
	FRotator CameraLocalRotation = FRotator::ZeroRotator;

	/**
	 * CalculateViewRotation
	 *
	 * This method calculates and updates the character's adjusted view rotation based on
	 * processed pitch and yaw values. The resulting rotation is stored in the AdjustedViewRotation.
	 * The roll component is set to zero, as it is not utilized in this calculation.
	 *
	 * This method is crucial for implementing a responsive and accurate camera system in the
	 * True First Person Perspective (TFPP) system.
	 */
	void CalculateViewRotation();

	/**
	 * Processes and returns the clamped pitch value for the character's control rotation.
	 *
	 * The pitch value is clamped within a predefined range to maintain realistic control and avoid
	 * excessive movement beyond specified limits.
	 *
	 * @return The clamped pitch value in degrees, constrained by the defined pitch range.
	 */
	float ProcessPitch() const;

	/**
	 * Calculates the relative yaw difference between the actor's current rotation and the control rotation.
	 *
	 * This method determines the angular difference in yaw, normalizing it within the range of -180 to 180 degrees.
	 *
	 * @return The normalized relative yaw difference in degrees.
	 */
	float ProcessYaw() const;

	/**
	 * YawRange
	 *
	 * This FVector2D variable defines the allowable range of yaw rotation for the character.
	 * The first value represents the minimum yaw limit, while the second value represents the maximum yaw limit.
	 *
	 * Initialized to a full 360-degree rotational range (-180.f to 180.f).
	 */
	FVector2D YawRange = FVector2D(-180.f, 180.f);

	/**
	 * PitchRange
	 *
	 * A FVector2D variable that defines the allowable pitch range for the character's camera movement.
	 * It specifies the minimum and maximum pitch angles, ensuring the camera remains within these limits.
	 */
	FVector2D PitchRange = FVector2D(-90.f, 90.f);

	/**
	 * PlayerController
	 *
	 * A reference to APlayerController which manages input and player-specific functionality.
	 * This variable is associated with the "Controller" category. It is visible in the editor, read-only in blueprints, and has private access specified.
	 *
	 * Primarily used to facilitate interaction and control mechanisms for the character within the game.
	 */
	UPROPERTY(Category = "Controller", VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	APlayerController* PlayerController;

	/**
	 * Represents the adjusted view rotation for the character.
	 *
	 * This variable is used to store the modified orientation of the character's view,
	 * typically after processing any necessary adjustments based on game logic,
	 * such as aiming offsets or camera alignment corrections.
	 */
	FRotator AdjustedViewRotation;

	/**
	 * @brief Reference to the custom character movement component for True First Person Perspective (TFPP).
	 *
	 * This member stores a pointer to the UTfppCharacterMovementComponent, which extends the movement logic
	 * for a TFPP system. It ensures the character's movement behavior aligns with the TFPP mechanics.
	 *
	 * Marked as VisibleAnywhere to allow inspection in the editor and BlueprintReadOnly to prevent modification
	 * in Blueprints while providing read access.
	 */
	UPROPERTY(Category="Components", VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UTfppCharacterMovementComponent> TfppCharacterMovement;

private:


};

