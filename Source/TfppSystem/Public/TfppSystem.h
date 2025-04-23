// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

/**
 * @brief The FTfppSystemModule is plugin for True First-Person Perspective games.
 *
 * This plugin implements a Humanoid Player character using Character class from unreal, with custom
 * character movement component to support different paces and stances. It can be expanded to more custom movements.
 */

class FTfppSystemModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
