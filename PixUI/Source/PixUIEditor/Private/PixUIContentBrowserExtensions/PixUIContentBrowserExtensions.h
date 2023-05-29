// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

// Integrate PixUI actions associated with existing engine types into the content browser
class FPixUIContentBrowserExtensions
{
public:
	static void InstallHooks();
	static void RemoveHooks();
};
