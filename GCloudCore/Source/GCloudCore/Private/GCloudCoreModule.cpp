// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "GCloudCoreModule.h"
#include "GCloudCoreAppDelegate.h"

#define LOCTEXT_NAMESPACE "FGCloudCoreModule"

void FGCloudCoreModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
    GCloudCoreAppDelegate::GetInstance().Initialize();
}

void FGCloudCoreModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FGCloudCoreModule, GCloudCore)
