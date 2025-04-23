// Copyright (c) 2025, Balbjorn Bran. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"

/**
 * This are tags created for managing the states of the player, and letting GAS base Character the state
 * of its movement
 */

UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_TFPP_Actions_Movement_WantsToJump);

UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_TFPP_States_Movement_IsSprinting);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_TFPP_States_Movement_IsWalking);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_TFPP_States_Movement_IsJogging);

UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_TFPP_States_Stances_IsCrouching);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_TFPP_States_Stances_IsStanding);

UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_TFPP_States_Mobility_IsInAir);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_TFPP_States_Mobility_IsSwimming);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_TFPP_States_Mobility_IsGrounded);