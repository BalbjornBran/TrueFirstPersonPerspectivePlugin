// Copyright (c) 2025, Balbjorn Bran. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TfppPlayerController.generated.h"

/**
 * @class ATfppPlayerController
 * @brief A specialized player controller class designed to enhance the True First Person Perspective system in Unreal Engine.
 *
 * This class inherits from APlayerController and is meant to be used within the True First Person Perspective framework.
 * It serves as the player controller for managing player input and interaction within the TFPP system.
 *
 * @ingroup TrueFirstPersonPerspective
 * @ingroup Controller
 */
UCLASS(ClassGroup=("True First Person Perspective | Controller"))
class TFPPSYSTEM_API ATfppPlayerController : public APlayerController
{
	GENERATED_BODY()
	
};
