// Copyright (c) 2025, Balbjorn Bran. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TfppTypes.h"
#include "TfppCharacterMovementComponent.generated.h"
  
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPaceChanged, EMovementPaces, OldPace, EMovementPaces, NewPace);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnStanceChanged, ECharacterStances, OldStance, ECharacterStances, NewStance);

/**
 * A specialized character movement component for the True First Person System.
 *
 * The UTfppCharacterMovementComponent enhances the base character movement component by introducing
 * customizable paces and stances. It allows for dynamic adjustment of character speed and movement style
 * based on game-specific requirements, such as walking, jogging, sprinting, or adjusting speed
 * when crouching, crawling, etc.
 *
 * This component provides functionality for initializing, setting, and getting the character's pace and stance,
 * along with events to handle and respond to changes in these properties.
 *
 * Functionalities such as maximum movement speed and stance speed multipliers can be configured
 * through blueprints or the editor for added flexibility.
 */
UCLASS(ClassGroup=("True First Person System | Components"), meta=(BlueprintSpawnableComponent))
class TFPPSYSTEM_API UTfppCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTfppCharacterMovementComponent();

	// ----------------------------------------------------------------------------------------------------------------
	// Begin Overriden Parent Functions
	// ----------------------------------------------------------------------------------------------------------------
	virtual void BeginPlay() override;
	// ----------------------------------------------------------------------------------------------------------------
	// End Overriden Parent Functions
	// ----------------------------------------------------------------------------------------------------------------

	/**
	 * Default pace of the character movement component.
	 * Specifies the starting pace for the character when the component is initialized.
	 *
	 * Can be set in the editor or via blueprint.
	 *
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup|Paces")
	EMovementPaces DefaultPace = EMovementPaces::PaceType0;

	/**
	 * Mapping of paces to their respective maximum movement speeds.
	 * Defines the speed limit for each pace in the game.
	 *
	 * Can be configured in the editor or via blueprint.
	 *
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup|Paces")
	TMap<EMovementPaces, float> PaceMaxSpeed;

	/**
	 * Sets the current pace of the character movement component.
	 * Updates the character's maximum walk speed and maximum crouched walk speed
	 * based on the new pace, and triggers the OnPaceChanged event if the pace is successfully changed.
	 *
	 * @param NewPace The desired new pace to be set for the character movement.
	 *                Must be a valid key in the PaceMaxSpeed map for the change to take effect.
	 */
	UFUNCTION(BlueprintCallable, Category = "TFPP|Paces")
	void SetPace(EMovementPaces NewPace);

	/**
	 * Retrieves the current pace of the character movement component.
	 * Indicates the current movement pace (e.g., Walking, Jogging, Sprinting)
	 * being used by the character.
	 *
	 * @return The current pace of the character as an EPaces enumeration value.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "TFPP|Paces")
	EMovementPaces GetCurrentPace() const
	{
		return CurrentPace;
	}

	/**
	 * Event triggered whenever the character's pace is changed.
	 * Broadcasts the old pace and the new pace as parameters.
	 *
	 * Can be used in blueprints or code to respond to pace changes, such as updating UI or triggering animations.
	 *
	 * Old pace and new pace are represented as EPaces enumeration values.
	 */
	UPROPERTY(BlueprintAssignable, Category = "TFPP|Paces")
	FOnPaceChanged OnPaceChanged;

	/**
	 * Default stance of the character movement component.
	 * Specifies the initial stance for the character when the component is initialized (e.g., Standing, Crouching, Crawling).
	 *
	 * Can be configured in the editor or via blueprint.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup|Stances")
	ECharacterStances StandingStance = ECharacterStances::StanceType0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup|Stances")
	ECharacterStances CrouchingStance = ECharacterStances::StanceType1;

	/**
	 * Multipliers for movement speed based on character stance.
	 * This map associates each stance (e.g., Standing, Crouching, Crawling) with a corresponding speed multiplier.
	 *
	 * Used to adjust the character's maximum movement speed dynamically based on their current stance in combination
	 * with the current movement pace.
	 *
	 * Can be configured in the editor or via blueprint.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup|Stances")
	TMap<ECharacterStances, float> StanceSpeedMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup|Paces")
	TMap<EMovementPaces, FFloatRange> PacesAngleRestriction;
	
	/**
	 * Updates the stance of the character movement component.
	 * Changes the character's current stance (e.g., Standing, Crouching, Crawling)
	 * and triggers the OnStanceChanged event if the stance is successfully updated.
	 *
	 * @param NewStance The desired new stance to be set for the character.
	 *                  Must be one of the predefined EStances values such as Standing, Crouching, or Crawling.
	 */
	UFUNCTION(BlueprintCallable, Category = "TFPP|Stances")
	void SetStance(ECharacterStances NewStance);

	/**
	 * Retrieves the current stance of the character movement component.
	 * Represents the character's posture or movement mode (e.g., Standing, Crouching, Crawling).
	 *
	 * This function is both callable and pure in blueprints
	 * to facilitate querying the character's current stance state without side effects.
	 *
	 * @return The current stance of the character as an EStances enumeration value.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "TFPP|Stances")
	ECharacterStances GetCurrentStance() const
	{
		return CurrentStance;
	}

	/**
	 * Delegate that broadcasts when the character's stance changes.
	 * Triggered when the stance of the character is updated through the movement component.
	 *
	 * Can be bound to in blueprints for custom responses to stance changes.
	 *
	 */
	UPROPERTY(BlueprintAssignable, Category = "TFPP|Paces")
	FOnStanceChanged OnStanceChanged;

	/**
	 * Initializes the Tfpp character movement component.
	 *
	 * Sets up the component's initial configuration, including default pace settings,
	 * maximum walking speeds, and broadcasting default values for pace and stance events.
	 */
	void InitializeTfppComponent();

private:
	// This is the current Pace of the character
	EMovementPaces CurrentPace;
	// The Movement component is always assuming that the player is Standing on begin play.
	ECharacterStances CurrentStance = ECharacterStances::StanceType0;

	/**
	 * Initializes the default speeds for various movement paces and stances.
	 * Populates the maximum speed values for predefined paces (e.g., Walking, Jogging, Sprinting)
	 * and sets multipliers for specific stances (e.g., Standing, Crouching).
	 *
	 * Determines the initial maximum walking speed and crouched speed based
	 * on the default movement pace and stance multiplier.
	 */
	void InitializeDefaultPacesSpeed();

	//FTransform OnProcessRootMotionPostConvertToWorld(const FTransform& InRootMotion, UCharacterMovementComponent* MovementComponent, float DeltaTime);

	bool IsPaceAllowedOnDirectionAngle(EMovementPaces MovementPace) const;
	
};
