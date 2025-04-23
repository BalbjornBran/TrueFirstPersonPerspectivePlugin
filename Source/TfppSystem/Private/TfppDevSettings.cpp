// Copyright (c) 2025, Balbjorn Bran. All rights reserved.


#include "TfppDevSettings.h"
#include "TfppTypes.h"
#include "Framework/Notifications/NotificationManager.h"
#include "Widgets/Notifications/SNotificationList.h"
#include "TfppLog.h"

UTfppDevSettings* UTfppDevSettings::DefaultSettings = nullptr;

UTfppDevSettings::UTfppDevSettings()
{
	bShowDevelopmentLogMessages = false;
	Paces = {"Jog","Sprint"};
	Mobilities = {};
	Stances = {"Crouch"};
	LogVerbosity = ETfppLogVerbosity::Warning;
}

ELogVerbosity::Type ToUnrealVerbosity(ETfppLogVerbosity InVerbosity)
{
	switch (InVerbosity)
	{
	case ETfppLogVerbosity::Fatal: return ELogVerbosity::Fatal;
	case ETfppLogVerbosity::Error: return ELogVerbosity::Error;
	case ETfppLogVerbosity::Warning: return ELogVerbosity::Warning;
	case ETfppLogVerbosity::Log: return ELogVerbosity::Log;
	case ETfppLogVerbosity::Verbose: return ELogVerbosity::Verbose;
	case ETfppLogVerbosity::VeryVerbose: return ELogVerbosity::VeryVerbose;
	default: return ELogVerbosity::Warning;
	}
}

void UTfppDevSettings::PostInitProperties()
{
	Super::PostInitProperties();
	
#if WITH_EDITOR
	UEnum* StancesEnum = StaticEnum<ECharacterStances>();
	UpdateEnums(StancesEnum, Stances);
	UEnum* PacesEnum = StaticEnum<EMovementPaces>();
	UpdateEnums(PacesEnum, Paces);
	UEnum* MobilityEnum = StaticEnum<EMobilities>();
	UpdateEnums(MobilityEnum, Mobilities);
#endif
	
}

#if WITH_EDITOR
bool UTfppDevSettings::CanEditChange(const FProperty* InProperty) const
{
	return Super::CanEditChange(InProperty);
}

void UTfppDevSettings::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	UEnum* StancesEnum = StaticEnum<ECharacterStances>();
	UpdateEnums(StancesEnum, Stances);
	UEnum* PacesEnum = StaticEnum<EMovementPaces>();
	UpdateEnums(PacesEnum, Paces);
	UEnum* MobilityEnum = StaticEnum<EMobilities>();
	UpdateEnums(MobilityEnum, Mobilities);

	FName PropertyName = (PropertyChangedEvent.Property != nullptr)
	? PropertyChangedEvent.Property->GetFName()
	: NAME_None;

	if (PropertyName == GET_MEMBER_NAME_CHECKED(UTfppDevSettings, LogVerbosity))
	{
		ApplyTfppLogVerbosityFromSettings();

		FNotificationInfo Info(FText::FromString(FString::Printf(TEXT("RpgInput: Log verbosity updated to %s"), *StaticEnum<ETfppLogVerbosity>()->GetValueAsString(LogVerbosity))));
		Info.FadeInDuration = 0.1f;
		Info.FadeOutDuration = 0.5f;
		Info.ExpireDuration = 2.0f;
		Info.bUseThrobber = false;
		Info.bUseSuccessFailIcons = true;
		Info.bUseLargeFont = false;
		Info.bFireAndForget = true;

		FSlateNotificationManager::Get().AddNotification(Info);
	}
}

void UTfppDevSettings::SetDefaultSettings(UTfppDevSettings* InSettings)
{
	DefaultSettings = InSettings;
}

void UTfppDevSettings::UpdateEnums(const UEnum* Enum, const TArray<FName>& NewNames)
{
	check(Enum);

	const FString KeyName = TEXT("DisplayName");
	const FString HiddenMeta = TEXT("Hidden");
	const FString UnusedDisplayName = TEXT("Unused");

	if (NewNames.Num() > (Enum->NumEnums() - 1))
	{
		UE_LOG(LogTemp, Error, TEXT("NewNames array is too big!"));
		FNotificationInfo Info(FText::FromString(FString::Printf(TEXT("The array with names is too big!"))));
		Info.FadeInDuration = 0.1f;
		Info.FadeOutDuration = 0.5f;
		Info.ExpireDuration = 2.0f;
		Info.bUseThrobber = false;
		Info.bUseSuccessFailIcons = true;
		Info.bUseLargeFont = false;
		Info.bFireAndForget = true;

		FSlateNotificationManager::Get().AddNotification(Info);
		return;
	}
	
	
	//First Restart Metadata
	for (int32 EnumIndex = 1; EnumIndex < Enum->NumEnums(); ++EnumIndex)
	{
		if (!Enum->HasMetaData(*HiddenMeta, EnumIndex))
		{
			Enum->SetMetaData(*HiddenMeta, TEXT(""), EnumIndex);
			Enum->SetMetaData(*KeyName, *UnusedDisplayName, EnumIndex);
		}
	}

	//Then, Assign new values
	for (int32 EnumIndex = 1; EnumIndex < Enum->NumEnums(); ++EnumIndex)
	{
		// Updating the enum with valid stances in the array
		if (NewNames.IsValidIndex(EnumIndex - 1))
		{
			Enum->RemoveMetaData(*HiddenMeta, EnumIndex); // Removing Hidden Flag
			Enum->SetMetaData(*KeyName, *NewNames[EnumIndex - 1].ToString(), EnumIndex); // assigning the name
		}
	}
}
#endif

