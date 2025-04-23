// Copyright (c) 2025, Balbjorn Bran. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "TfppDevSettings.h"

DECLARE_LOG_CATEGORY_EXTERN(TfppLog, Log, All);

void ApplyTfppLogVerbosityFromSettings();

/**
 * Logs and debugs for the system
 */

/**
 * Creates appropriate messages for the True First Person category.
 * 
 * @param Verbosity		Verbosity level of this message. See ELogVerbosity.
 * @param Message		Message string literal.
 */
#define DEV_LOG(Verbosity, Message) \
do \
{ \
	if (GEngine && WITH_EDITOR) \
	{ \
		if (const UTfppDevSettings* Settings = GetDefault<UTfppDevSettings>()) \
		{ \
			if (Settings->bShowDevelopmentLogMessages) \
			{ \
				UE_LOG(TfppLog, Verbosity, TEXT("%s: %s"), TEXT(__FUNCTION__), TEXT(Message)); \
			} \
		} \
	} \
} while (0)
		


/**
 * Creates appropriate messages for the True First Person category, with format arguments.
 * 
 * @param Verbosity		Verbosity level of this message. See ELogVerbosity.
 * @param Format		Format string literal in the style of printf.
 * @param Args			Comma-separated arguments used to format the message.
 */
#define DEV_LOG_ARGS(Verbosity, Format, ...) \
do \
{ \
	if (GEngine && WITH_EDITOR) \
	{ \
		if (const UTfppDevSettings* Settings = GetDefault<UTfppDevSettings>()) \
		{ \
			if (Settings->bShowDevelopmentLogMessages) \
			{ \
				UE_LOG(TfppLog, Verbosity, TEXT("%s: %s"), TEXT(__FUNCTION__), *FString::Printf(TEXT(Format), ##__VA_ARGS__)); \
			} \
		} \
	} \
} while (0)
		