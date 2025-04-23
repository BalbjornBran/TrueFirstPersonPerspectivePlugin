// Copyright (c) 2025, Balbjorn Bran. All rights reserved.

#include "TfppLog.h"
#include "Logging/LogVerbosity.h"

DEFINE_LOG_CATEGORY(TfppLog)

void ApplyTfppLogVerbosityFromSettings()
{
	const UTfppDevSettings* Settings = GetDefault<UTfppDevSettings>();
	if (ensureMsgf(Settings, TEXT("Failed to get UTfppDevSettings!")))
	{
		ELogVerbosity::Type NewVerbosity;
		switch (Settings->LogVerbosity)
		{
		case ETfppLogVerbosity::Fatal: NewVerbosity = ELogVerbosity::Fatal; break;
		case ETfppLogVerbosity::Error: NewVerbosity = ELogVerbosity::Error; break;
		case ETfppLogVerbosity::Warning: NewVerbosity = ELogVerbosity::Warning; break;
		case ETfppLogVerbosity::Log: NewVerbosity = ELogVerbosity::Log; break;
		case ETfppLogVerbosity::Verbose: NewVerbosity = ELogVerbosity::Verbose; break;
		case ETfppLogVerbosity::VeryVerbose: NewVerbosity = ELogVerbosity::VeryVerbose; break;
		default: NewVerbosity = ELogVerbosity::Warning; break;
		}

		TfppLog.SetVerbosity(NewVerbosity);
	}
}