// Copyright (c) 2025, Balbjorn Bran. All rights reserved.

#pragma once

#include "CoreMinimal.h"

/**
 *  Useful enums for the module
 */


/**
 * Enum for Stances of the player.
 * This determines if the player is in a specific stance where all the locomotion mode
 * could change. In this case, we can force to have different paces while in different stance.
 * That's why this is a potential part where can be expanded, to have a combat stance, or what ever.
 * Still WIP
 */

UENUM(BlueprintType)
enum class ECharacterStances : uint8
{
	StanceType0 UMETA(DisplayName = "Standing"),
	StanceType1 UMETA(Hidden),
	StanceType2 UMETA(Hidden),
	StanceType3 UMETA(Hidden),
	StanceType4 UMETA(Hidden),
	StanceType5 UMETA(Hidden),
	StanceType6 UMETA(Hidden),
	StanceType7 UMETA(Hidden),
	StanceType8 UMETA(Hidden),
	StanceType9 UMETA(Hidden)
};


UENUM(BlueprintType)
enum class EMovementPaces : uint8
{
	PaceType0 UMETA(DisplayName = "Walking"),
	PaceType1 UMETA(Hidden),
	PaceType2 UMETA(Hidden),
	PaceType3 UMETA(Hidden),
	PaceType4 UMETA(Hidden),
	PaceType5 UMETA(Hidden),
	PaceType6 UMETA(Hidden),
	PaceType7 UMETA(Hidden),
	PaceType8 UMETA(Hidden),
	PaceType9 UMETA(Hidden)
};

/*
 * Enum for stablishing the Mobility type of the character. It's my way of expanding the "Custom" movement mode that's
 * built in unreal's character movement component.
 * My intention is, as soon as CustomMovementMode is activated, this Enum should be check in order to see
 * how the player should move. Base on the specified enum, we activate the specific mobility type.
 * Another potentially expansion in the future could be this enum. Stil WIP
 */
UENUM(BlueprintType)
enum class EMobilities : uint8
{
	MobilityType0 UMETA(DisplayName = "Base"), //Means that we are using a normal mobility mode, which means one of the EMovementMode.
	MobilityType1 UMETA(Hidden),
	MobilityType2 UMETA(Hidden),
	MobilityType3 UMETA(Hidden),
	MobilityType4 UMETA(Hidden),
	MobilityType5 UMETA(Hidden),
	MobilityType6 UMETA(Hidden),
	MobilityType7 UMETA(Hidden),
	MobilityType8 UMETA(Hidden),
	MobilityType9 UMETA(Hidden),
	MobilityType10 UMETA(Hidden),
	MobilityType11 UMETA(Hidden),
	MobilityType12 UMETA(Hidden),
	MobilityType13 UMETA(Hidden),
	MobilityType14 UMETA(Hidden),
	MobilityType15 UMETA(Hidden),
	MobilityType16 UMETA(Hidden),
	MobilityType17 UMETA(Hidden),
	MobilityType18 UMETA(Hidden),
	MobilityType19 UMETA(Hidden),
};
