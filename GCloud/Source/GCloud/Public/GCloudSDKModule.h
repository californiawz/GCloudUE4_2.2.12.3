// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"
#include "Containers/Ticker.h"

#if !defined(PLATFORM_PS4)
#define PLATFORM_PS4 0
#endif

#if !defined(PLATFORM_PS5)
#define PLATFORM_PS5 0
#endif
class FGCloudSDKModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
//
#if PLATFORM_PS4 || PLATFORM_PS5
//
private:
	int gcloudPSMod = -1;
#endif
};
