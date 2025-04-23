// Copyright (c) 2025, Balbjorn Bran. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "Misc/Build.h"
#include "TfppDevSettings.generated.h"

UENUM(BlueprintType)
enum class ETfppLogVerbosity : uint8
{
	Fatal UMETA(DisplayName = "Fatal"),
	Error UMETA(DisplayName = "Error"),
	Warning UMETA(DisplayName = "Warning"),
	Log UMETA(DisplayName = "Log"),
	Verbose UMETA(DisplayName = "Verbose"),
	VeryVerbose UMETA(DisplayName = "Very Verbose")
};

/**
 * Different variables of the True First Person Perspective plugin are configured in this section.
 */
UCLASS(Config = Game, defaultconfig, meta = (DisplayName = "True First Person Settings"))
class TFPPSYSTEM_API UTfppDevSettings : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Debug|Log")
	bool bShowDevelopmentLogMessages;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Debug|Log", meta = (EditCondition = "bShowDevelopmentLogMessages"))
	ETfppLogVerbosity LogVerbosity;
	
	UTfppDevSettings();

	UPROPERTY(Config, EditAnywhere, Category = "Movement")
	TArray<FName> Stances;

	UPROPERTY(Config, EditAnywhere, Category = "Movement")
	TArray<FName> Paces;
	
	UPROPERTY(Config, EditAnywhere, Category = "Movement")
	TArray<FName> Mobilities;

	static UTfppDevSettings* Get()
	{return CastChecked<UTfppDevSettings>(UTfppDevSettings::StaticClass()->GetDefaultObject());}

#if WITH_EDITOR

	virtual void PostInitProperties() override;
	virtual bool CanEditChange(const FProperty* InProperty) const override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
protected:
	static void SetDefaultSettings(UTfppDevSettings* InSettings);
private:
	static void UpdateEnums(const UEnum* Enum, const TArray<FName>& NewNames);
	
	static UTfppDevSettings* DefaultSettings;
	
#endif
	
};
